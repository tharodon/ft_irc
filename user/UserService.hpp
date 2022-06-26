//
// Created by Tiffiny Harodon on 6/26/22.
//

#ifndef UNTITLED_USERSERVICE_HPP
#define UNTITLED_USERSERVICE_HPP


#pragma once
#include "User.hpp"
#include "../repository/UserRepository.hpp"
#include "UserMapper.hpp"

#define BUFFER_SIZE 1024

class UserService {
private:
    UserRepository userRepository;
    UserMapper userMapper;

public:
    UserService(){}

    int* getAllDescriptors(){
        return userRepository.getAllFd();
    }

    int countOfUsers(){
        return userRepository.countOfUsers();
    }

    void addUser(int fd){
        char *buff = read(fd);
        std::cout << buff << std::endl;
        User *user = userMapper.charArrToUser(buff, fd);
        userRepository.save(*user);
        sendRegisterMessage(userRepository.findByNickname(user->getNickname()));
    }

    void answerToMessage(int fd){
        char *buff = read(fd);
        recv(fd, buff, BUFFER_SIZE, 0);
        std::cout << buff << std::endl;
        if (!strncmp("PING", buff, 4)){
            buff[1] = 'O';
            send(fd, buff, strlen(buff), 0);
        }
        else if (!strncmp("ISON", buff, 4)){
            send(fd, buff, strlen(buff), 0);
        }
        else if (!strncmp("PRIVMSG", buff, 7)){
            User user = userRepository.findByNickname(getNicknameFromPrivMsg(buff + 8));
            send(fd, buff, strlen(buff), 0);
        }
    }

    char* getNicknameFromPrivMsg(char *buff){
        int i = -1;
        while (buff[++i] && buff[i] != ' '){
        }
        char *nickname = (char *)malloc(sizeof (char) * (i + 1));
        nickname[i] = '\0';
        for (int j = 0; j < i; j++){
            nickname[j] = buff[j];
        }
        return nickname;
    }

    void sendRegisterMessage(User &user){
        send(user.getFd(), Constants().register_message.c_str(), Constants().register_message.length(), 0);
    }

    char* read(int fd){
        char *buff = new char [BUFFER_SIZE];
        bzero(buff, BUFFER_SIZE);
        recv(fd, buff, BUFFER_SIZE, 0);
        return buff;
    }

};


#endif //UNTITLED_USERSERVICE_HPP
