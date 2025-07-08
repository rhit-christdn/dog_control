#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "ralph.h"

static const int LED_PIN = 17; // BCM GPIO 17

static double STOP_DUTYCYCLE = 45; // Duty cycle for stop (0-100 percentage)
static double WALK_FORWARD_DUTYCYCLE = 60; // Duty cycle for walking forward (0-100 percentage)
static double RUN_FORWARD_DUTYCYCLE = 90; // Duty cycle for running forward (0-100 percentage)
static double WALK_BACKWARD_DUTYCYCLE = 30; // Duty cycle for walking backward (0-100 percentage)
static double RUN_BACKWARD_DUTYCYCLE = 10; // Duty cycle for running backward (0-100 percentage)

int gpioInit() {

    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed." << std::endl;
        return 1;
    }
    std::cout << "pigpio initialized successfully." << std::endl;

    // Set frequency if desired (default is ~800Hz)
    int frequency = gpioSetPWMfrequency(LED_PIN, 1000);
    std::cout << "PWM frequency set to: " << frequency << " Hz" << std::endl;

    // Set initial duty cycle
    setDutyCycle(STOP_DUTYCYCLE);

    return 0;
}

void setDutyCycle(double percent) {
    if (percent < 0 || percent > 100) {
        std::cerr << "Duty cycle must be between 0 and 100." << std::endl;
        return;
    }
    double dutyCycle = (percent / 100.0) * 255; // Convert percentage to 0-255 range
    gpioPWM(LED_PIN, dutyCycle);
}

void walkForward() {
    setDutyCycle(WALK_FORWARD_DUTYCYCLE);
}

void runForward() {
    setDutyCycle(RUN_FORWARD_DUTYCYCLE);
}

void walkBackward() {
    setDutyCycle(WALK_BACKWARD_DUTYCYCLE);
}

void runBackward() {
    setDutyCycle(RUN_BACKWARD_DUTYCYCLE);
}

void stop() {
    setDutyCycle(STOP_DUTYCYCLE);
}
