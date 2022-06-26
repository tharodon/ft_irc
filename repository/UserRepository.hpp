//
// Created by Tiffiny Harodon on 6/26/22.
//

#pragma once
#ifndef UNTITLED_USERREPOSITORY_HPP
#define UNTITLED_USERREPOSITORY_HPP

#include "../user/User.hpp"
#include "map"

class UserRepository {
private:
    std::map<std::string, User> pair_nickname_user;
public:
    UserRepository() {};

    void save(User &user) {
        pair_nickname_user.insert(std::pair<std::string, User>(user.getNickname(), user));
    }

    void deleteByNickname(const std::string &nickname) {
        pair_nickname_user.erase(nickname);
    }

    User &findByNickname(const std::string &nickname) {
        return pair_nickname_user.at(nickname);
    }

    User *getAllUsers() {
        User *users = new User[pair_nickname_user.size()];
        std::map<std::string, User>::iterator it = pair_nickname_user.begin();
        for (int i = 0; it != pair_nickname_user.end(); i++, it++) {
            users[i] = it->second;
        }
        return users;
    }

    int *getAllFd() {
        int *descriptors = new int[pair_nickname_user.size()];
        std::map<std::string, User>::iterator it = pair_nickname_user.begin();
        for (int i = 0; it != pair_nickname_user.end(); i++, it++) {
            descriptors[i] = it->second.getFd();
        }
        return descriptors;
    }

    int countOfUsers() {
        return (int) pair_nickname_user.size();
    }
};


#endif //UNTITLED_USERREPOSITORY_HPP
