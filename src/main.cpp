#include <ncurses.h>
#include <string>
#include <ctime>
#include <vector>
#include <bitset>


std::bitset<8> toBCD(unsigned int m);

int main(int argc, char* argv[]) {
    int sv = 1;
    if (argc > 1) {
        if ((std::string)argv[1] == "--no-header") {
            sv = 0;
        }
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    bool running = true;

    while (running) {
        erase();

        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        std::vector<std::bitset<8>> timeBCD = {
            toBCD(t->tm_hour),
            toBCD(t->tm_min),
            toBCD(t->tm_sec)
        };
        std::vector<std::bitset<4>> digits;

        for (auto& bcd : timeBCD) {
            unsigned val = bcd.to_ulong();
            digits.push_back(std::bitset<4>((val >> 4) & 0xF));
            digits.push_back(std::bitset<4>(val & 0xF));
        }

        if (sv != 0)
            mvprintw(0, 0, "BINARY CLOCK");

        for (int bit = 3; bit >= 0; --bit) {
            for (size_t i = 0; i < digits.size(); ++i) {
                mvprintw(sv + (3 - bit), i * 2, "%c", (digits.at(i)[bit] ? '1' : '0'));
            }
        }

        int ch = getch();
        if (tolower(ch) == 'q') {
            running = false;
        }

        napms(1000);
    }

    endwin();
    return 0;
}

std::bitset<8> toBCD(unsigned int m) {
    return std::bitset<8>((((m / 10) & 0xF) << 4) | ((m % 10) & 0xF));
}
