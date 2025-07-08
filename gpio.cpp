#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "ralph.h"

static const int LED_PIN = 17; // BCM GPIO 17
static int dutyCycle = 0; // Global variable to hold the duty cycle

static double STOP_DUTYCYCLE = (45 * 255) / 100; // Convert percentage to duty cycle (0-255)
static double WALK_FORWARD_DUTYCYCLE = (60 * 255) / 100; // Convert percentage to duty cycle (0-255)
static double RUN_FORWARD_DUTYCYCLE = (90 * 255) / 100; // Convert percentage to duty cycle (0-255)
static double WALK_BACKWARD_DUTYCYCLE = (30 * 255) / 100; // Convert percentage to duty cycle (0-255)
static double RUN_BACKWARD_DUTYCYCLE = (10 * 255) / 100; // Convert percentage to duty cycle (0-255)

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
    double percent = 50.0;
    dutyCycle = (percent * 255) / 100; // Convert percentage to duty cycle (0-255)

    gpioPWM(LED_PIN, dutyCycle); // Set PWM duty cycle

    return 0;
}

void setDutyCycle(int percent) {
    if (dutyCycle < 0 || dutyCycle > 100) {
        std::cerr << "Duty cycle must be between 0 and 100." << std::endl;
        return;
    }
    dutyCycle = (percent * 255) / 100; // Convert percentage to duty cycle (0-255)
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
