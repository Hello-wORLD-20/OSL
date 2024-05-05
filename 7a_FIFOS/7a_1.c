#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    char input[100];
    int fd1, fd2, chars = 0, words = 0, lines = 0;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    fd1 = open(FIFO1, O_RDONLY);
    fd2 = open(FIFO2, O_WRONLY);

    while (1) {
        read(fd1, input, 100);

        if (strcmp(input, "exit\n") == 0) {
            break;
        }

        lines++;

        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == ' ' || input[i] == '\n') {
                words++;
            }
            chars++;
        }

        FILE *fp = fopen("output.txt", "w");
        fprintf(fp, "Number of characters: %d\n", chars - 1);
        fprintf(fp, "Number of words: %d\n", words);
        fprintf(fp, "Number of lines: %d\n", lines);
        fclose(fp);

        char output[100];
        fp = fopen("output.txt", "r");
        fgets(output, 100, fp);
        fclose(fp);

        write(fd2, output, strlen(output) + 1);
    }

    close(fd1);
    close(fd2);
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
