#ifndef RALPH_H
#define RALPH_H

int gpioInit();
void setDutyCycle(int percent);

void walkForward();
void runForward();
void walkBackward();
void runBackward();
void stop();

#endif // RALPH_H