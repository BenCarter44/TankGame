#ifndef INPUT_HANDLE_H
#define INPUT_HANDLE_H

#include "PrettyConsole/console.h"

#ifdef LINUX
#include <unistd.h>
#include <termios.h>
#else
#include <conio.h>
#endif

#include <queue>
#include <chrono>
#include <thread>


// IN Mesc
#define KEYBOARD_DELAY 10 

char InputHandler_getch();
void InputHandler_close();

class InputHandler
{
public:
    InputHandler();

    void startListening();
    void stopListening();
    bool isListening();

    int isAvailable();
    char peek();
    char read();
    void clear();
    void simPress(char c);
    
private:   
    bool listen;
    queue<char> inputBuffer;
    std::thread* listenThread;

    void listeningThread();
};


#endif