#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "student.h"

void print_special(FILE *in) {
    Student s;

    while (student_read_bin(&s, in)) {
        if ((s.videoController != EMBEDDED && s.videoMemory >= 512) || (s.hddCount == 0)) {
            student_print(&s);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }

    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    print_special(in);

    fclose(in);

    return 0;
}
