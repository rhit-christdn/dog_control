#include "ralph.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>


int main(){
    gpioInit();

    while (true) {
        std::string command;
        std::cout << "Enter command (walk_forward, run_forward, walk_backward, run_backward, stop): ";
        std::cin >> command;

        enum CommandType { WALK_FORWARD, RUN_FORWARD, WALK_BACKWARD, RUN_BACKWARD, STOP, UNKNOWN };
        CommandType cmdType;
        if (command == "walk_forward") cmdType = WALK_FORWARD;
        else if (command == "run_forward") cmdType = RUN_FORWARD;
        else if (command == "walk_backward") cmdType = WALK_BACKWARD;
        else if (command == "run_backward") cmdType = RUN_BACKWARD;
        else if (command == "stop") cmdType = STOP;
        else cmdType = UNKNOWN;

        switch (cmdType) {
            case WALK_FORWARD:
            walkForward();
            std::cout << "Walking forward..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            stop();
            break;

            case RUN_FORWARD:
            runForward();
            std::cout << "Running forward..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            stop();
            break;

            case WALK_BACKWARD:
            walkBackward();
            std::cout << "Walking backward..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            stop();
            break;

            case RUN_BACKWARD:
            runBackward();
            std::cout << "Running backward..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            stop();
            break;

            case STOP:
            stop();
            std::cout << "Stopping..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
            
            default:
            std::cerr << "Unknown command: " << command << std::endl;
            stop();
            break;
        }
    }
}

//g++ -std=c++11 -o ralph ralph.cpp gpio.cpp -lpigpio -lrt -lpthread
// Run with: sudo ./ralph