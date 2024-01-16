//
// Created by ylu on 24-1-16.
//

#include <stdio.h>
#include "pretty.h"

void printHexDump(const char *data, size_t len) {
    for (size_t i = 0; i < len; i += 16) {
        printf("%08x: ", (unsigned int)i);
        for (size_t j = 0; j < 16; j++) {
            if (i + j < len) {
                printf("%02x ", (unsigned char)data[i + j]);
            } else {
                printf("   ");
            }
        }
        printf(" ");
        for (size_t j = 0; j < 16; j++) {
            if (i + j < len) {
                char c = data[i + j];
                printf("%c", (c >= 32 && c < 127) ? c : '.');
            }
        }
        printf("\n");
    }
}
