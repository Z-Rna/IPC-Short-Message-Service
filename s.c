#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include "structs_s.h"

void load(); 

void write_logged_in_users();

void logging();

void logout();

void list_of_groups();

void sub_group(int g);

void write_users_in_group(int g);

void message_in_group(int g);

void send();

void get();

void is_in_USERS();

int main()
{
    int kolejka = msgget(127,0644 | IPC_CREAT);
    int kolejka_u;
    load();
    int n;
    while(1)
    {
        msgrcv(kolejka,&msg,sizeof(msg)+1,0,0);
        kolejka_u = msgget(msg.pid,0644);
        switch(msg.order)
        {
            case 100:
                logging();
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            case 111:
                logout();
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            case 222:
                write_logged_in_users();
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            case 333:
                write_users_in_group(msg.nr_of_group);
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            case 444:
                list_of_groups(msg.nr_of_group);
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            case 555:
                sub_group(msg.nr_of_group);
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            case 666:
                sub_group(msg.nr_of_group);
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            case 777:
                message_in_group(msg.nr_of_group);
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            case 880:
                is_in_USERS();
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            case 888:
                send();
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            case 999:
                get();
                msgsnd(kolejka_u,&msg,sizeof(msg)+1,0);
                break;
            default:
                    break;
        }
    }
    return 0;
}

void load() 
{
    FILE *file = fopen("dane.txt","r");
    if(file==NULL)
    {
        printf("server: i can't read data from this file, sorry");
    }
    else
    {
        for(int i=0; !feof(file); i++)
        {
            if(i<9)
            {
                fscanf(file, "%s %s", USERS[i].log, USERS[i].pass);
            }
            else if(i<12)
            {
                fscanf(file, "%s", GROUPS[i-9].GN);
            }
        }
        printf("Data loaded\n");
    }
}

void write_logged_in_users() //G
{
    printf("List of logged users:\n");
    strcpy(msg.message,"");
    for(int i=0; i < 9; i++)
    {
        if(USERS[i].logged==1)
        {
            strcat(msg.message,USERS[i].log);
            strcat(msg.message," ");
        }
    }
    printf("%s\n",msg.message);
}

void logging() //G
{
    for(int i=0;i<9;i++)
    {
        if(strcmp(msg.log,USERS[i].log)==0 && strcmp(msg.pass,USERS[i].pass)==0)
        {
            msg.logged=1;
            USERS[i].logged=1;
            printf("User: %s login\n", msg.log);
            break;
        }
    }
}

void logout() //G
{
    for(int i=0;i<9;i++)
    {
        if(strcmp(msg.log,USERS[i].log)==0 && strcmp(msg.pass,USERS[i].pass)==0)
        {
            msg.logged=0;
            USERS[i].logged=0;
            printf("User: %s logout\n", msg.log);
            break;
        }
        else
        {
            //printf("%s %s\n", msg.log, USERS[i].log);
        }
    }
}

void list_of_groups() //G
{
    printf("List of groups:\n");
    strcpy(msg.message,"");
    for(int i=0; i < 3; i++)
    {
        strcat(msg.message,GROUPS[i].GN);
        strcat(msg.message," ");
    }
    printf("%s\n",msg.message);
}

void sub_group(int g) //G
{
    for(int i=0; i<9; i++)
    {
        if(strcmp(msg.log,USERS[i].log)==0)
        {
            if(msg.order==555) //zapisanie sie 
            {
                msg.sg[g - 1] = 1;
                //printf("%d\n",msg.sg[g-1]);
                USERS[i].sg[g - 1]=1;
                printf("User: %s sub group: %s\n",USERS[i].log,GROUPS[g-1].GN);
                break;
            }
            else
            {
                msg.sg[g - 1] = 0;
                USERS[i].sg[g - 1]=0;
                printf("User: %s usub group: %s\n",USERS[i].log,GROUPS[g-1].GN);
                break;
            }
        }
    }
}

void write_users_in_group(int g) //??
{
    strcpy(msg.message,"");
    for(int i=0; i<9; i++)
    {
        if(USERS[i].sg[g-1]==1)
        {
            strcat(msg.message,USERS[i].log);
            strcat(msg.message," ");
        }
    }
}

void message_in_group(int g) //G
{
    strcat(GROUPS[g-1].message,msg.log);
    strcat(GROUPS[g-1].message,": ");
    strcat(GROUPS[g-1].message,msg.message);
    strcat(GROUPS[g-1].message,"\n");
    printf("User: %s write on topic %s: %s\n",msg.log,GROUPS[g-1].GN,msg.message);
    strcpy(msg.message,GROUPS[g-1].message);
}

void send()
{
    for(int i=0;i<9;i++)
    {
        if(strcmp(USERS[i].log,msg.send_to)==0)
        {
            strcat(USERS[i].message,msg.log);
            strcat(USERS[i].message,": ");
            strcat(USERS[i].message,msg.message);
            strcat(USERS[i].message,"\n");
            printf("User: %s to user: %s: %s\n", msg.log, msg.send_to, msg.message);
            break;
        }
    }
}
void get()
{
    printf("get to: %s\n",msg.log);
    for(int i=0;i<9;i++)
    {
        if(strcmp(USERS[i].log,msg.log)==0)
        {
            strcpy(msg.message,USERS[i].message);
            break;
        }
    }
}

void is_in_USERS()
{
    msg.exist=0;
    for(int i=0;i<9;i++)
    {
        if(strcmp(USERS[i].log,msg.send_to)==0)
        {
            msg.exist=1;
            break;
        }
    } 
}
