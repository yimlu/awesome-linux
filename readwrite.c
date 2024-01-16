//
// Created by ylu on 24-1-16.
//
#include "readwrite.h"
#include "pretty.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void read_file(char *file_path) {
    int fd;
    fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        perror("read");
    }

    char buff[256];
    int len = 256;

    ssize_t nr;

    while (1) {
        nr = read(fd, buff, len);

        if (nr == -1) {
            perror("read");
            break;
        } else if (nr == 0) {
            //printf("\n\nEND");
            break;
        } else if (nr > 0 && nr < len) {
            printf("LESS THAN LEN:\n");
            printHexDump(buff, nr);
        } else {
            printf("NORMAL:\n");

            printHexDump(buff, len);
        }
    }
}