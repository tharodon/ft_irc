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

#include "../utils/Constants.hpp"

#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H

#include "../utils/Constants.hpp"
#include "../repository/UserRepository.hpp"
#include "../user/User.hpp"
#include "../user/UserService.hpp"

class Server {
private :
    struct sockaddr_in server_address;
    int server;
    socklen_t socklen;
    fd_set fd_read;
    fd_set fd_write;
    int max_fd;
    UserService userService;

public:
    Server(){
        server = socket(AF_INET, SOCK_STREAM, 0);
        server_address.sin_port = htons(1543);
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htons(INADDR_ANY);
        bind(server, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address));
        listen(server, 1);
        socklen = sizeof (server_address);
        max_fd = server;
        userService = UserService();
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
        int *client = userService.getAllDescriptors();
        int count = userService.countOfUsers();
        for (int i = 0; i < count; i++){
            FD_SET(client[i], &fd_read);
            FD_SET(client[i], &fd_write);
        }
    }

    void add_client(){
        if (FD_ISSET(server, &fd_read)){
            int fd = accept(server, reinterpret_cast<sockaddr*>(&server_address), &socklen);
            maxFdRefresh(fd);
            userService.addUser(fd);
        }
    }

    void check_updates(){
        int *descriptors = userService.getAllDescriptors();
        int size = userService.countOfUsers();
        for (int i = 0; i < size; i++){
            if (FD_ISSET(descriptors[i], &fd_read)){
                userService.answerToMessage(descriptors[i]);
            }
        }
    }

    void maxFdRefresh(int fd){
        if (fd > max_fd){
            max_fd = fd;
        }
    }
};

#endif //UNTITLED_SERVER_H
