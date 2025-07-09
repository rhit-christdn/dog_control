#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "ralph.h"

static double STOP_DUTYCYCLE = 45;          // Duty cycle for stop (0-100 percentage)
static double WALK_FORWARD_DUTYCYCLE = 60;  // Duty cycle for walking forward (0-100 percentage)
static double RUN_FORWARD_DUTYCYCLE = 90;   // Duty cycle for running forward (0-100 percentage)
static double WALK_BACKWARD_DUTYCYCLE = 30; // Duty cycle for walking backward (0-100 percentage)
static double RUN_BACKWARD_DUTYCYCLE = 10;  // Duty cycle for running backward (0-100 percentage)

int gpioInit(int pin)
{

    if (gpioInitialise() < 0)
    {
        std::cerr << "pigpio initialization failed." << std::endl;
        return 1;
    }
    std::cout << "pigpio initialized successfully." << std::endl;

    // Set frequency if desired (default is ~800Hz)
    int frequency = gpioSetPWMfrequency(pin, 1000);
    std::cout << "PWM frequency set to: " << frequency << " Hz" << std::endl;

    // Set initial duty cycle
    setDutyCycle(STOP_DUTYCYCLE);

    return 0;
}

void setDutyCycle(int pin, double percent)
{
    if (percent < 0 || percent > 100)
    {
        std::cerr << "Duty cycle must be between 0 and 100." << std::endl;
        return;
    }
    double dutyCycle = (percent / 100.0) * 255; // Convert percentage to 0-255 range
    gpioPWM(pin, dutyCycle);
}

void forward(){
    walkForward();
}

void walkForward()
{
    setDutyCycle(FORWARD_MOVEMENT_PIN, WALK_FORWARD_DUTYCYCLE);
    std::cout << "Walking forward..." << std::endl;
}

void runForward()
{
    setDutyCycle(FORWARD_MOVEMENT_PIN, RUN_FORWARD_DUTYCYCLE);
    std::cout << "Running forward..." << std::endl;
}

void walkBackward()
{
    setDutyCycle(FORWARD_MOVEMENT_PIN, WALK_BACKWARD_DUTYCYCLE);
    std::cout << "Walking backward..." << std::endl;
}

void runBackward()
{
    setDutyCycle(FORWARD_MOVEMENT_PIN, RUN_BACKWARD_DUTYCYCLE);
    std::cout << "Running backward..." << std::endl;
}

void walkDistance(double distance)
{
    if (distance < 0)
    {
        std::cerr << "Distance cannot be negative." << std::endl;
        return;
    }
    double time = (distance * 12) / walkForwardVelo; // Calculate time in seconds
    walkForward();
    std::cout << "Walking for " << distance << " feet..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(time * 1000)));
    stop();
}

void runDistance(double distance)
{
    if (distance < 0)
    {
        std::cerr << "Distance cannot be negative." << std::endl;
        return;
    }
    double time = (distance * 12) / runForwardVelo; // Calculate time in seconds
    runForward();
    std::cout << "Running for " << distance << " feet..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(time * 1000)));
    stop();
}

void stop()
{
    setDutyCycle(FORWARD_MOVEMENT_PIN, STOP_DUTYCYCLE);
    std::cout << "Stopping..." << std::endl;
}
