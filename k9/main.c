#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINE_LENGTH 16

void insertionSort(char keys[][5], char values[][100], int n) {
    int i, j;
    char key[5];
    char value[100];
    for (i = 1; i < n; i++) {
        strcpy(key, keys[i]);
        strcpy(value, values[i]);
        j = i - 1;

        int keyInt = atoi(key);
        int arrInt;

        while (j >= 0 && (arrInt = atoi(keys[j])) > keyInt) {
            strcpy(keys[j + 1], keys[j]);
            strcpy(values[j + 1], values[j]);
            j = j - 1;
        }
        strcpy(keys[j + 1], key);
        strcpy(values[j + 1], value);
    }
}

int binarySearch(char arr[][5], int l, int r, char* x) {
    int xInt = atoi(x);

    while (l <= r) {
        int mid = l + (r - l) / 2;
        int midInt = atoi(arr[mid]);

        if (midInt == xInt)
            return mid;

        if (midInt < xInt)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return -1;
}

int countLinesInFile(char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("error opening %s\n", filename);
        return -1;
    }

    int count = 0;
    char c;
    for (c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n') {
            count = count + 1;
        }
    }

    fclose(file);
    return count;
}

void readAsciiArtFromFile(char* filename, char** asciiArt, int size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("error opening %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        if (fgets(asciiArt[i], LINE_LENGTH, file) == NULL) {
            break;
        }

        asciiArt[i][strcspn(asciiArt[i], "\n")] = 0;
    }

    fclose(file);
}

void printTable(char keys[][5], char values[][100], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s, value: %s\n", keys[i], values[i]);
    }
}

int main() {
    srand(time(0));
    char filename[100];
    printf("file: ");
    scanf("%s", filename);

    int size = countLinesInFile(filename);
    if (size == -1) {
        return 1;
    }

    char** asciiArt = malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        asciiArt[i] = malloc(LINE_LENGTH * sizeof(char));
    }

    readAsciiArtFromFile(filename, asciiArt, size);

    char keys[size][5];
    char values[size][100];

    int choice;
    printf("1. order\n2. reverse\n3. random\n");
    scanf("%d", &choice);

        switch(choice) {
        case 1:
            for (int i = 0; i < size; i++) {
                sprintf(keys[i], "%d", i);
                strncpy(values[i], asciiArt[i % size], 100);
            }
            break;
        case 2:
            for (int i = 0; i < size; i++) {
                sprintf(keys[i], "%d", size - i);
                strncpy(values[i], asciiArt[i % size], 100);
            }
            break;
        case 3:
            for (int i = 0; i < size; ) {
                int unique = 1;
                char tempKey[5];
                sprintf(tempKey, "%d", rand() % 91 + 10);

                for (int j = 0; j < i; j++) {
                    if (strcmp(keys[j], tempKey) == 0) {
                        unique = 0;
                        break;
                    }
                }

                if (unique) {
                    strcpy(keys[i], tempKey);
                    strncpy(values[i], asciiArt[i % size], 100);
                    i++;
                }
            }
            break;
        default:
            printf("bad choice\n");
            return 0;
    }

    printf("before:\n");
    printTable(keys, values, size);

    insertionSort(keys, values, size);

    printf("after:\n");
    printTable(keys, values, size);

    char* searchKey = malloc(8 * sizeof(char));
    printf("search by key: ");
    scanf("%s", searchKey);
    int result = binarySearch(keys, 0, size - 1, searchKey);

    if (result != -1) {
        printf("found, index: %d\n", result);
        printf("value: %s\n", values[result]);
    } else {
        printf("not found\n");
    }

    for (int i = 0; i < size; i++) {
        free(asciiArt[i]);
    }
    free(asciiArt);

    free(searchKey);
    return 0;
}