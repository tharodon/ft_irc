//
// Created by Tiffiny Harodon on 6/26/22.
//

#ifndef UNTITLED_USER_HPP
#define UNTITLED_USER_HPP

#pragma once
#include <string>

class User {
private:
    int fd;
    std::string nickname;
    std::string username;

public:
    User(int fd, const std::string &username, const std::string &nickname) : fd(fd), nickname(nickname), username(username){};
    User(){};

    int getFd() const {
        return fd;
    }

    User& setFd(int fd) {
        User::fd = fd;
        return *this;
    }

    const std::string &getUsername() const {
        return username;
    }

    User& setUsername(const std::string &username) {
        User::username = username;
        return *this;
    }

    const std::string &getNickname() const {
        return nickname;
    }

    User& setNickname(const std::string &nickname) {
        User::nickname = nickname;
        return *this;
    }
};


#endif //UNTITLED_USER_HPP
