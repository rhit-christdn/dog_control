#ifndef RALPH_H
#define RALPH_H

int gpioInit();
void setDutyCycle(double percent);

void walkForward();
void runForward();
void walkBackward();
void runBackward();
void stop();

static const double walkForwardVelo = 22.18; // ft/s
static const double runForwardVelo = 46.77; // ft/s

#endif // RALPH_H