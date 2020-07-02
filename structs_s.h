#ifndef STRUCTS_H
#define STRUCTS_H

struct mes{
    char log[1024];
    char pass[1024];
    int pid;
    int logged;
    int order;
    int nr_of_group;
    char send_to[1024];
    char message[10240];
    int exist;
    int sg[3];
}msg, msg_u;

struct G{
    char GN[1024];
    char message[10240];
}GROUPS[3];

struct U{
    char log[1024]; 
    char pass[1024]; 
    int logged;     
    int sg[3];        
    char message[10240];
}USERS[9];

#endif
