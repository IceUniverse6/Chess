#include <iostream>
#include <string>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include "Game.h"

HANDLE COLOR = GetStdHandle(STD_OUTPUT_HANDLE);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    Game game;
    SetConsoleTextAttribute(COLOR, 10);
    std::wcout << L"Game Started!" << std::endl;
    SetConsoleTextAttribute(COLOR, 6);
    std::wcout << L"Type";
    SetConsoleTextAttribute(COLOR, 4);
    std::wcout << L" exit ";
    SetConsoleTextAttribute(COLOR, 6);
    std::wcout << L"to leave, or enter move(e.g. e2 e4)" << std::endl;
    SetConsoleTextAttribute(COLOR, 7);

    while (!game.isGameOver()) {
        game.printBoard();
        std::wcout << (game.isWhiteTurn() ? L"White Turn: " : L"Black Turn: ");

        std::wstring input;
        std::getline(std::wcin, input);

        if (input == L"exit") {
            SetConsoleTextAttribute(COLOR, 10);
            std::wcout << L"Game Finished!" << std::endl;
            SetConsoleTextAttribute(COLOR, 7);
            break;
        }

        if (input.length() < 5) {
            SetConsoleTextAttribute(COLOR, 4);
            std::wcout << L"Invalid Input!" << std::endl;
            SetConsoleTextAttribute(COLOR, 7);
            continue;
        }

        std::wstring fromStr = input.substr(0, 2);
        std::wstring toStr = input.substr(3, 2);

        int fromCol = std::tolower(fromStr[0]) - L'a';
        int fromRow = 8 - (fromStr[1] - L'0');
        int toCol = std::tolower(toStr[0]) - L'a';
        int toRow = 8 - (toStr[1] - L'0');

        Position from(fromRow, fromCol);
        Position to(toRow, toCol);

        if (!from.isValid() || !to.isValid()) {
            SetConsoleTextAttribute(COLOR, 4);
            std::wcout << L"Invalid Input!" << std::endl;
            SetConsoleTextAttribute(COLOR, 7);
            continue;
        }

        if (!game.move(from, to)) {
            SetConsoleTextAttribute(COLOR, 4);
            std::wcout << L"Invalid Move!" << std::endl;
            SetConsoleTextAttribute(COLOR, 7);
        }
    }

    game.printBoard();
    SetConsoleTextAttribute(COLOR, 10);
    std::wcout << L"Game Finished!" << std::endl;
    SetConsoleTextAttribute(COLOR, 7);

    return 0;
}