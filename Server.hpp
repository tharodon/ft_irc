//
// Created by Tiffiny Harodon on 6/20/22.
//
#pragma once
#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>
#include <map>
#include <vector>

#include "Constants.hpp"

#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H

#define BUFFER_SIZE 1024

class Server {
private :
    struct sockaddr_in server_address;
    int server;
    socklen_t socklen;
    fd_set fd_read;
    fd_set fd_write;
    int size;
    int max_fd;
    int client[100];

public:
    Server(){
        size = 0;
        server = socket(AF_INET, SOCK_STREAM, 0);
        server_address.sin_port = htons(8081);
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htons(INADDR_ANY);
        bind(server, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address));
        listen(server, 1);
        socklen = sizeof (server_address);
        max_fd = server;
    }

    void start(){
        while (true){
            init_fd_set();
            select(max_fd + 100, &fd_read, &fd_write, NULL, NULL);
            add_client();
            check_updates();
        }
    }

    void init_fd_set(){
        FD_ZERO(&fd_read);
        FD_SET(server, &fd_read);
        FD_SET(server, &fd_write);
        for (int i = 0; i < size; i++){
            FD_SET(client[i], &fd_read);
            FD_SET(client[i], &fd_write);
        }
    }

    void add_client(){
        if (FD_ISSET(server, &fd_read)){
            client[size] = accept(server, reinterpret_cast<sockaddr*>(&server_address), &socklen);
            send(client[size], "Connected\n", 10, 0);
            max_fd = client[size];
            size++;
        }
    }

    void check_updates(){
        for (int i = 0; i < size; i++){
            char buff[BUFFER_SIZE];
            if (FD_ISSET(client[i], &fd_read)){
                recv(client[i], buff, BUFFER_SIZE, 0);
                std::cout << "Request: " << buff << std::endl;
                send(client[i], Constants().toCharArray(Constants().register_message), Constants().register_message.length(), 0);
            }
        }
    }
};

//:IRC 375 123:-127.0.0.1 Message of the day -
//:IRC 372 123:-Hello peer
//:IRC 376 123 :End of /MOTD command

#endif //UNTITLED_SERVER_H
