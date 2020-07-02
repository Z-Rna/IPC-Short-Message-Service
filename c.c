#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "structs_c.h"

void login(int kolejka, int kolejka_u);

void menu();

int main()
{
    int kolejka = msgget( 127, 0644 );
    int kolejka_u = msgget( getpid(), 0644 | IPC_CREAT);
    int dec;
    printf("Welcome on our Chat®!\nPlease, enter your login and password:\n");
    login(kolejka, kolejka_u);
    while(msg_u.logged==1)
    {
        menu();
        scanf("%d",&dec);
        switch(dec)
        {
            case 1:
                msg_u.order=111;
                msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
                msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
                if(msg_u.logged==0)
                {
                    printf("Logged out successfully.\n");
                }
                else
                {
                    printf("Logged out unsuccessfully.\n");
                }
                break;
            case 2:
                msg_u.order=222;
                msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
                msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
                printf("%s\n",msg_u.message);
                break;
            case 3:
                msg_u.order=333;
                printf("Choose number of group 1-3\n");
                scanf("%d",&msg_u.nr_of_group);
                if(msg_u.nr_of_group<4 && msg_u.nr_of_group>0)
                {
                    msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
                    msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
                    printf("List users in this group: %s\n", msg_u.message);
                }
                else
                {
                    printf("Wrong number!\n");
                }
                break;
            case 4:
                msg_u.order=444;
                msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
                msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
                printf("%s\n",msg_u.message);
                break;
            case 5:
                msg_u.order=555;
                printf("Choose nr of group 1-3\n");
                scanf("%d",&msg_u.nr_of_group);
                if(msg_u.nr_of_group<4 && msg_u.nr_of_group>0)
                {
                    msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
                    msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
                    printf("Done!\n");
                }
                else
                {
                    printf("Wrong number!\n");
                }
                break;
            case 6:
                msg_u.order=666;
                printf("Choose nr of group 1-3\n");
                scanf("%d",&msg_u.nr_of_group);
                if(msg_u.nr_of_group<4 && msg_u.nr_of_group>0)
                {
                    msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
                    msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
                    printf("Done!\n");
                }
                else
                {
                    printf("Wrong number!\n");
                }
                
                break;
            case 7:
                msg_u.order=777;
                printf("Choose nr of group 1-3\n");
                scanf("%d",&msg_u.nr_of_group);
                if(msg_u.nr_of_group<4 && msg_u.nr_of_group>0)
                {
                    if(msg_u.sg[msg_u.nr_of_group-1]==1)
                    {
                        printf("Type message:\n");
                        scanf("%s", msg_u.message);
                        msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
                        msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
                        printf("%s",msg_u.message);
                    }
                    else
                    {
                        printf("To chatting on this group, first subscribe\n");
                    }
                }
                else
                {
                    printf("Wrong number!\n");
                }
                
                break;
            case 8:
                msg_u.order=880;
                printf("Type message:\n");
                scanf("%s", &msg_u.message);
                printf("Type user:\n");
                scanf("%s",&msg_u.send_to);
                msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
                msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
                if(msg_u.exist==1)
                {
                    msg_u.order=888;
                    msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
                    msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
                }
                else
                {
                    printf("User: %s doesn't exist!\n",msg_u.send_to);
                }
                break;
            case 9:
                msg_u.order=999;
                msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
                msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
                printf("Your messages:\n%s",msg_u.message);
                break;
            default:
                printf("The wrong number! Choose ringt one\n");
                break;
        }
    }
    return 0;
}

void login(int kolejka, int kolejka_u)
{
    while(1)
    {
        printf("Login:\n");
        scanf("%s",&msg_u.log);
        printf("Password:\n");
        scanf("%s",&msg_u.pass);
        msg_u.pid = getpid();
        msg_u.order=100;
        msgsnd(kolejka,&msg_u,sizeof(msg_u)+1,0);
        msgrcv(kolejka_u,&msg_u,sizeof(msg_u)+1,0,0);
        if(msg_u.logged==1)
        {
            printf("Login and password correct!\n");
            break;
        }
        printf("Login and password incorrect!\n");
            
    }
}

void menu()
{
    printf("1. Logout\n");
    printf("Show list of:\n\t2. Logged in users\n\t3. Users in every group\n");
    printf("Groups:\n\t4. Show list of groups\n\t5. Subscribe to the group\n\t6. Unsubscribe to the group\n");
    printf("Messages:\n\t7. Send a message to the group\n\t8. Send a message to the user\n\t9. Check your message box\n");
}
