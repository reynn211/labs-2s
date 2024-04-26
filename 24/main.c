#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct _node {
    struct _node* left;
    struct _node* right;
    char* value;
} Node;

Node* parseExpression(char** expression);
Node* parseTerm(char** expression);
Node* parseFactor(char** expression);

Node* newNode(char* value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->value = (char*)malloc((strlen(value) + 1) * sizeof(char));
    strcpy(node->value, value);
    return node;
}

char* nextToken(char** expression) {
    while (isspace(**expression)) (*expression)++;
    if (**expression == '\0') return NULL;

    int length = 0;
    if (isdigit(**expression)) {
        while (isdigit((*expression)[length])) length++;
    } else {
        length = 1;
    }

    char* token = (char*)malloc((length + 1) * sizeof(char));
    strncpy(token, *expression, length);
    token[length] = '\0';
    (*expression) += length;

    return token;
}

Node* parseFactor(char** expression) {
    char* token = nextToken(expression);
    if (token == NULL) return NULL;
    Node* node;
    if (strcmp(token, "(") == 0) {
        node = parseExpression(expression);
        free(token);
        token = nextToken(expression);
        if (token == NULL || strcmp(token, ")") != 0) {
            exit(1);
        }
    } else if (strcmp(token, "-") == 0) {
        node = newNode(token);
        node->right = parseFactor(expression);
    } else {
        node = newNode(token);
    }
    free(token);
    return node;
}

Node* parsePower(char** expression) {
    Node* node = parseFactor(expression);
    char* token;
    while ((token = nextToken(expression)) != NULL) {
        if (strcmp(token, "^") == 0) {
            Node* right = parseFactor(expression);
            Node* parent = newNode(token);
            parent->left = node;
            parent->right = right;
            node = parent;
        } else {
            (*expression)--;
            free(token);
            break;
        }
        free(token);
    }
    return node;
}

Node* parseTerm(char** expression) {
    Node* node = parsePower(expression);
    char* token;
    while ((token = nextToken(expression)) != NULL) {
        if (strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            Node* right = parsePower(expression);
            Node* parent = newNode(token);
            parent->left = node;
            parent->right = right;
            node = parent;
        } else {
            (*expression)--;
            free(token);
            break;
        }
        free(token);
    }
    return node;
}

Node* parseExpression(char** expression) {
    Node* node = parseTerm(expression);
    char* token;
    while ((token = nextToken(expression)) != NULL) {
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
            Node* right = parseTerm(expression);
            Node* parent = newNode(token);
            parent->left = node;
            parent->right = right;
            node = parent;
        } else {
            (*expression)--;
            free(token);
            break;
        }
        free(token);
    }
    return node;
}

int takeOutMinus(Node** node) {
    if (*node == NULL) return 0;

    int changed = 0;

    if (strcmp((*node)->value, "-") == 0) {
        if ((*node)->right != NULL && strcmp((*node)->right->value, "-") == 0) {
            Node* rightOfMinus = (*node)->right->right;
            free((*node)->right->value);
            free((*node)->right);
            (*node)->right = rightOfMinus;
            free((*node)->value);
            (*node)->value = (char*)malloc(2 * sizeof(char));
            strcpy((*node)->value, "+");
            changed = 1;
        }
    }

    if (strcmp((*node)->value, "*") == 0 && (*node)->right != NULL && (*node)->left != NULL) {
        if (strcmp((*node)->right->value, "-") == 0 && strcmp((*node)->left->value, "-") == 0) {
            Node* rightOfMinus = (*node)->right->right;
            Node* leftOfMinus = (*node)->left->right;
            free((*node)->right->value);
            free((*node)->left->value);
            free((*node)->right);
            free((*node)->left);
            (*node)->right = rightOfMinus;
            (*node)->left = leftOfMinus;
            changed = 1;
        } else if (strcmp((*node)->right->value, "-") == 0 || strcmp((*node)->left->value, "-") == 0) {
            Node* newMinusNode = newNode("-");
            newMinusNode->right = *node;
            if (strcmp((*node)->right->value, "-") == 0) {
                Node* rightOfMinus = (*node)->right->right;
                free((*node)->right->value);
                free((*node)->right);
                (*node)->right = rightOfMinus;
            } else {
                Node* leftOfMinus = (*node)->left->right;
                free((*node)->left->value);
                free((*node)->left);
                (*node)->left = leftOfMinus;
            }
            *node = newMinusNode;
            changed = 1;
        }
    }

    changed |= takeOutMinus(&(*node)->left);
    changed |= takeOutMinus(&(*node)->right);
    return changed;
}

void printTree(Node* node, int space) {
    if (node == NULL) return;

    space += 3;

    printTree(node->right, space);

    if (strcmp(node->value, "+") != 0 || (node->left != NULL && node->right != NULL)) {
        printf("\n");
        for (int i = 3; i < space; i++)
            printf(" ");
        printf("%s\n", node->value);
    }

    printTree(node->left, space);
}

void printExpressionHelper(Node* node, int isRoot, char* parentValue, int parentIsEmptyPlus) {
    if (node == NULL) return;
    int isUnaryMinus = (strcmp(node->value, "-") == 0 && node->right != NULL && node->left == NULL);
    int isEmptyPlus = (strcmp(node->value, "+") == 0 && node->left == NULL && node->right != NULL);
    int needParentheses = (!isRoot && !parentIsEmptyPlus && (isUnaryMinus || 
                      ((strcmp(node->value, "*") == 0 || strcmp(node->value, "/") == 0) && 
                      (strcmp(parentValue, "+") == 0 || strcmp(parentValue, "-") == 0))));
    if (needParentheses) printf("(");
    printExpressionHelper(node->left, 0, node->value, isEmptyPlus);
    if (!isEmptyPlus) printf("%s", node->value);
    printExpressionHelper(node->right, 0, node->value, isEmptyPlus);
    if (needParentheses) printf(")");
}

void printExpression(Node* node) {
    printExpressionHelper(node, 1, NULL, 0);
}

void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node->value);
    free(node);
}

int main() {
    char expression[100];
    printf("> ");
    fgets(expression, 100, stdin);
    char* p = expression;
    Node* root = parseExpression(&p);
    printExpression(root);
    while (takeOutMinus(&root));
    printf("\n");
    printExpression(root);
    printTree(root, 0);
    printf("\n");
    freeTree(root);
    return 0;
}