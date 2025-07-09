#include "ralph.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

int main()
{
    gpioInit(FORWARD_MOVEMENT_PIN);

    while (true)
    {
        std::string command;
        std::cout << "Enter command (walk_forward, run_forward, walk_backward, run_backward, walk_distance, run_distance, stop): ";
        std::cin >> command;

        enum CommandType
        {
            WALK_FORWARD,
            RUN_FORWARD,
            WALK_BACKWARD,
            RUN_BACKWARD,
            RUN_DISTANCE,
            WALK_DISTANCE,
            STOP,
            UNKNOWN
        };
        CommandType cmdType;
        if (command == "walk_forward")
            cmdType = WALK_FORWARD;
        else if (command == "run_forward")
            cmdType = RUN_FORWARD;
        else if (command == "forward")
            cmdType = WALK_FORWARD; // Alias for walk_forward
        else if (command == "walk_backward")
            cmdType = WALK_BACKWARD;
        else if (command == "run_backward")
            cmdType = RUN_BACKWARD;
        else if (command == "backward")
            cmdType = WALK_BACKWARD; // Alias for walk_backward
        else if (command == "run_distance")
            cmdType = RUN_DISTANCE;
        else if (command == "walk_distance")
            cmdType = WALK_DISTANCE;
        else if (command == "stop")
            cmdType = STOP;
        else
            cmdType = UNKNOWN;

        switch (cmdType)
        {
        case WALK_FORWARD:
        {
            walkForward();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            stop();
            break;
        }
        case RUN_FORWARD:
        {
            runForward();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            stop();
            break;
        }
        case WALK_BACKWARD:
        {
            walkBackward();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            stop();
            break;
        }
        case RUN_BACKWARD:
        {
            runBackward();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            stop();
            break;
        }
        case WALK_DISTANCE:
        {
            double distance;
            std::cout << "\n\tEnter distance in feet: ";
            std::cin >> distance;

            walkDistance(distance);
            break;
        }
        case RUN_DISTANCE:
        {
            double distance;
            std::cout << "\n\tEnter distance in feet: ";
            std::cin >> distance;

            runDistance(distance);
            break;
        }
        case STOP:
        {
            stop();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }
        default:
        {
            std::cerr << "Unknown command: " << command << std::endl;
            stop();
            break;
        }
        }
    }
}

// g++ -std=c++11 -o ralph ralph.cpp gpio.cpp -lpigpio -lrt -lpthread
//  Run with: sudo ./ralph