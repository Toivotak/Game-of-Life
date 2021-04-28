#pragma once

#include <iostream>

namespace support {

#if defined (_WIN32)

#include <windows.h>

inline void clearScreen()                                               
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

inline bool keyIsPressed()                                              // Setup for termination using 'E'
{
    std::cout << "\nPress 'E' to terminate";
    if (GetAsyncKeyState(0x45))
    {
        return true;
    }
    return false;
}

#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)

#include <cstdlib>

inline void clearScreen()
{
    std::system("clear");
}

inline bool keyIsPressed()                                              //This needs work, mayby separed thread?
{
    std::cout << "\Termination not working sorry. Kill terminal manually";
    return false;
}

#endif

inline int isInteger(int start, int end) { 	                                    // cheking input
    int x;
    while (true) {
        if (std::cin >> x)                                                      // is number
        {	                                                
            if (start <= x && x <= end)                                         // if a valid number
            {	                                    
                break; 	                                                        // valid number
            }
            else 
            {
                std::cout << "Incorrect selection. Range is from " << start << " to " << end << "\n-> ";
                std::cin.clear();
                while (std::cin.get() != '\n');                                 // empty loop					

            }
        }
        else 
        { 						                                                // not a number
            std::cout << "Invalid Input! Please input a numerical value.\n-> ";
            std::cin.clear();
            while (std::cin.get() != '\n');                                     // empty loop
        }
    }
    return x;
}

} //end of namespace