# IPC Short Message Service
* [About](#about)
* [Files](#files)
* [How to run](#how-to-run)
* [Warning](#warning)
* [Technologies](#technologies)
## About
Simple server-client application using IPC. Chatrooms a'la discord and private messages :wink:
## Files
- s.c- sever program
- c.c- client program
- structs_s.h- header file with structures for server
- structs_c.h- header file with structure for client
- dane.txt- data to create users accounts and topics
## How to run
I'm using OpenSuse terminal
1. By Makefile
```
$ make
```
... and in two (or more if you want) seperate terminals:
```
$ ./s
```
```
$./c
```
2. By hand
```
$ gcc -w -Wall s.c -o s
$ gcc -w -Wall c.c -o c
```
```
$ ./s
```
```
$./c
```
## Warning
IPC mechanics don't work the same on every dystribution of Linux. This project was tested on Ubuntu, Mint and OpenSuse (VM). It worked correctly on only last one. I asked about this problem my teacher, but she didn't know how to fix it, so do i.

I suggest to run server **first**, just in case.
## Technologies
- C
- Kate
