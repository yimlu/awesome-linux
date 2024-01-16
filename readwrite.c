//
// Created by ylu on 24-1-16.
//
#include "readwrite.h"
#include "pretty.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

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
            printHexDump(buff, nr);
        } else {
            printHexDump(buff, len);
        }
    }
}


void write_to_file(char *file_path, char *content) {
    int fd;
    fd = open(file_path, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open file");
    }

    int len = 0;

    while (content[len] != '\0') {
        len++;
    }

    write(fd, content, len);
}

#define TIMEOUT 5
#define BUF_LEN 1024

void select_read() {
    struct timeval tv;
    fd_set readfds;
    int ret;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;

    ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

    if (ret == -1) {
        perror("select");
    } else if (!ret) {
        printf("%d seconds elapsed.\n", TIMEOUT);
    }

    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        char buf[BUF_LEN + 1];
        int len;

        len = read(STDIN_FILENO, buf, BUF_LEN);

        if (len == -1) {
            perror("read");
        }

        if (len) {
            buf[len] = '\0';
            printf("read:%s\n", buf);
        }
    }
}