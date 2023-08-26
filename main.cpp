#include <iostream>
#include <windows.h>

const int MIN_DELAY {20};
const int START_KEY {VK_LMENU};
const int EXIT_KEY {VK_ESCAPE};

bool isAltKeyPressed()
{
    return GetAsyncKeyState(START_KEY) & 0x8000;
}

bool isExitKeyPressed()
{
    return GetAsyncKeyState(EXIT_KEY);
}

int main()
{
    SetConsoleTitleA("Auto Clicker");
    std::cout << "| Welcome to my 'Auto Clicker'!" << std::endl;
    std::cout << "\n| L Alt  --> Toggle clicking\n| Escape --> Exit the program" << std::endl;

    int clickDelay;
    do
    {
        std::cout << "Enter a click delay (ms, >=" << MIN_DELAY << ")\n-> ";
        std::cin >> clickDelay;
    } while (clickDelay < MIN_DELAY || std::cin.fail() || clickDelay > INT_MAX);

    bool clicking {false};
    bool prevAltState {false};
    DWORD lastClickTime {};

    while (true)
    {
        bool currAltState = isAltKeyPressed();

        if (currAltState && !prevAltState)
        {
            clicking = !clicking;
        }

        if (isExitKeyPressed())
        {
            return 0;
        }

        prevAltState = currAltState;

        if (clicking && GetTickCount() - lastClickTime >= clickDelay)
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            lastClickTime = GetTickCount();
        }
    }

    return 0;
}
