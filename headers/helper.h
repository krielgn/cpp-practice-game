#pragma once

#include <chrono>
#include <thread>
#include <string>
#include <iostream>

const int DELAY = 55;
const int C_DELAY = 25;

inline void delay_msg(std::string msg, int delay = DELAY, bool no_newline = false){
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

    for (auto &i : msg){
        std::cout << i << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(C_DELAY));
    }
    
    if (!no_newline){
        std::cout << "\n";
    } else {
        std::cout << std::flush;
    }
}

inline void delay_msg_nn(std::string msg, int delay = DELAY) {
    delay_msg(msg, delay, true);
}