//
// Created by Tiffiny Harodon on 6/20/22.
//
#ifndef UNTITLED_CONSTANTS_HPP
#define UNTITLED_CONSTANTS_HPP

#pragma once
#include <string>

class Constants {
public:
    static std::string register_message;

    Constants(){
        register_message = ":IRC 375 123:-127.0.0.1 Message of the day -\n:IRC 372 123:-Hello peer\n:IRC 376 123 :End of /MOTD command\n";
    }

    static char* toCharArray(std::string str){
        char *array = new char [str.length()];
        for (int i = 0; i < str.length(); i++){
            array[i] = str[i];
        }
        return array;
    }
};


#endif //UNTITLED_CONSTANTS_HPP
