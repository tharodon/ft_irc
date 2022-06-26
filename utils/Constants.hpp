//
// Created by Tiffiny Harodon on 6/20/22.
//
#ifndef UNTITLED_CONSTANTS_HPP
#define UNTITLED_CONSTANTS_HPP

#pragma once
#include <string>

class Constants {
public:
    const std::string register_message;
    const std::string ping;
    const std::string pong;
    Constants() : register_message(":IRC 375 123:-127.0.0.1 Message of the day -\n:IRC 372 123:-Hello peer\n:IRC 376 123 :End of /MOTD command\n"),
                  ping("PING ircserv\n"),
                  pong("PONG "){
    };
};


#endif //UNTITLED_CONSTANTS_HPP
