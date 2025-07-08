#ifndef RALPH_H
#define RALPH_H

int gpioInit();
void setDutyCycle(double percent);

void walkForward();
void runForward();
void walkBackward();
void runBackward();
void stop();

#endif // RALPH_H