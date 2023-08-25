#include <iostream>
#include <windows.h>

const int CLICK_DELAY {20};
const int ALT_KEY {VK_LMENU};
const int EXIT_KEY {VK_ESCAPE};

int main()
{
    SetConsoleTitleA("Auto Clicker");
    std::cout << "| Welcome to my 'Auto Clicker'!" << std::endl;
    std::cout << "\n| L Alt  --> Toggle clicking\n| Escape --> Exit the program" << std::endl;

    bool clicking {false};
    bool prevAltState {false};

    while (true)
    {
        bool currAltState = GetAsyncKeyState(ALT_KEY) & 0x8000;

        if (currAltState && !prevAltState)
        {
            clicking = !clicking;
        }

        else if (GetAsyncKeyState(EXIT_KEY))
        {
            return 0;
        }

        prevAltState = currAltState;

        if (clicking)
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(CLICK_DELAY);
        }
    }

    return 0;
}
