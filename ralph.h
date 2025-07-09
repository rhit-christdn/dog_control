#ifndef RALPH_H
#define RALPH_H

int gpioInit(int pin);
void setDutyCycle(int pin, double percent);

void walkForward();
void forward();
void runForward();
void walkBackward();
void runBackward();
void walkDistance(double distance);
void runDistance(double distance);
void stop();

static const double walkForwardVelo = 22.18; // ft/s
static const double runForwardVelo = 46.77; // ft/s

static const int FORWARD_MOVEMENT_PIN = 17; // BCM GPIO 17

#endif // RALPH_H