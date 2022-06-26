//
// Created by Tiffiny Harodon on 6/26/22.
//

#ifndef UNTITLED_USERMAPPER_HPP
#define UNTITLED_USERMAPPER_HPP
#pragma once
#include "User.hpp"

class UserMapper {
public:
    User* charArrToUser(char *arr, int fd){
        User *user = new User();
        char **info = splitByRN(arr);
        user->setFd(fd).setUsername(info[1] + 5).setNickname(info[2] + 5);
//        std::string nickname = user->getNickname();
//        for (int i = 0; i < nickname.length(); i++){
//            nickname[i] = tolower(nickname[i]);
//        }
//        user->setNickname(nickname);
        return user;
    }

private:
    char** splitByRN(char *arr){
        int len = strlen(arr);
        int count = 0;
        for (int i = 0; i < len; i++){
            if (arr[i] == '\r' && arr[i + 1] == '\n'){
                count++;
            }
        }
        char** userInfo = (char **)malloc(sizeof (char *) * (count + 1));
        userInfo[count] = nullptr;
        for (int str = 0, pos = 0, i = 0; arr[i]; i++){
            if (pos == 0) {
                userInfo[str] = (char *) malloc(sizeof(char) * (lenOfString(arr, i) + 1));
            }
            if (arr[i] == '\r' && arr[i + 1] == '\n'){
                userInfo[str][pos] = '\0';
                pos = 0;
                str++;
                i++;
                continue;
            }
            userInfo[str][pos++] = arr[i];
        }
        return userInfo;
    }

    int lenOfString(char *arr, int pos){
        int i = 0;

        while (arr[pos]){
            if (arr[pos] == '\r' && arr[pos + 1] == '\n'){
                break;
            }
            i++;
            pos++;
        }
        return i;
    }
};


#endif //UNTITLED_USERMAPPER_HPP
