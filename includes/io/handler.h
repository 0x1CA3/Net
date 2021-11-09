#include <stdio.h>
#include <stdlib.h>
#pragma once


/*
    *    includes/io/handler.h
    *    Date: 11/09/21
    *    Author: 0x1CA3
*/


struct function {
    const char *buffer;
    int (*function)(fd_user);
};

void handler(char buffer[1024], int fd_user);