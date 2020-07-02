#ifndef STRUCTSC_H
#define STRUCTSC_H

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
}msg_u;

#endif
