#include "../../includes/io/handler.h"
#include "io.c"
#pragma once


/*
    *    util/io/handler.c
    *    Date: 11/09/21
    *    Author: 0x1CA3
*/


struct function botnet_commands[] = {
    {"?", help_menu},
    {"help", help_menu},
    {"server", cnc_details},
    {"banner", display_banner},
    {"clear", clear_screen},
    {"cls", clear_screen},
};

enum {commands_amount = sizeof(botnet_commands) / sizeof(botnet_commands[0])};

void handler(char buffer[1024], int fd_user) {
    for (int i = 0; i < commands_amount; i++) {
        if (strstr(buffer, botnet_commands[i].buffer) != NULL) {
            return (*botnet_commands[i].function)(fd_user);
        }
    }
}