#include <ncurses.h>
#include <string>
#include <ctime>
#include <string>
#include <vector>
#include <bitset>


std::string getFormattedCurrentTime();
std::vector<std::string> split(const std::string& s, char delimiter);
std::vector<std::string> splitAllCharacters(const std::string& s);
std::string join(const std::vector<std::string>& strings, const std::string& delimiter);

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

        std::string time = getFormattedCurrentTime();
        std::vector<std::string> timeSplitted = split(time, ':');
        std::vector<std::string> withoutDelimSplitted = splitAllCharacters(timeSplitted.at(0) + timeSplitted.at(1) + timeSplitted.at(2));

        std::bitset<4> h0_bit(std::stoi(withoutDelimSplitted.at(0)));
        std::bitset<4> h1_bit(std::stoi(withoutDelimSplitted.at(1)));

        std::bitset<4> m0_bit(std::stoi(withoutDelimSplitted.at(2)));
        std::bitset<4> m1_bit(std::stoi(withoutDelimSplitted.at(3)));

        std::bitset<4> s0_bit(std::stoi(withoutDelimSplitted.at(4)));
        std::bitset<4> s1_bit(std::stoi(withoutDelimSplitted.at(5)));

        std::vector<std::string> h0_bitSplitted = splitAllCharacters(h0_bit.to_string());
        std::vector<std::string> h1_bitSplitted = splitAllCharacters(h1_bit.to_string());

        std::vector<std::string> m0_bitSplitted = splitAllCharacters(m0_bit.to_string());
        std::vector<std::string> m1_bitSplitted = splitAllCharacters(m1_bit.to_string());

        std::vector<std::string> s0_bitSplitted = splitAllCharacters(s0_bit.to_string());
        std::vector<std::string> s1_bitSplitted = splitAllCharacters(s1_bit.to_string());

        std::vector<std::vector<std::string>> lines = {
            { h0_bitSplitted.at(0), h1_bitSplitted.at(0), m0_bitSplitted.at(0), m1_bitSplitted.at(0), s0_bitSplitted.at(0), s1_bitSplitted.at(0) },
            { h0_bitSplitted.at(1), h1_bitSplitted.at(1), m0_bitSplitted.at(1), m1_bitSplitted.at(1), s0_bitSplitted.at(1), s1_bitSplitted.at(1) },
            { h0_bitSplitted.at(2), h1_bitSplitted.at(2), m0_bitSplitted.at(2), m1_bitSplitted.at(2), s0_bitSplitted.at(2), s1_bitSplitted.at(2) },
            { h0_bitSplitted.at(3), h1_bitSplitted.at(3), m0_bitSplitted.at(3), m1_bitSplitted.at(3), s0_bitSplitted.at(3), s1_bitSplitted.at(3) }
        };

        if (sv != 0)
            mvprintw(0, 0, "BINARY CLOCK");

        mvprintw(sv + 0, 0, "%s", join(lines.at(0), " ").c_str());
        mvprintw(sv + 1, 0, "%s", join(lines.at(1), " ").c_str());
        mvprintw(sv + 2, 0, "%s", join(lines.at(2), " ").c_str());
        mvprintw(sv + 3, 0, "%s", join(lines.at(3), " ").c_str());

        int ch = getch();
        if (tolower(ch) == 'q') {
            running = false;
        }
    }

    endwin();

    return 0;
}

std::string getFormattedCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm* ptm = std::localtime(&now);

    size_t bufferSize = 64;
    std::vector<char> buffer(bufferSize);

    size_t charsWritten = std::strftime(buffer.data(), buffer.size(), "%H:%M:%S", ptm);

    while (charsWritten == 0 && bufferSize < 1024) {
        bufferSize *= 2;
        buffer.resize(bufferSize);
        charsWritten = std::strftime(buffer.data(), buffer.size(), "%H:%M:%S", ptm);
    }

    return std::string(buffer.data());
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::string::size_type start = 0;
    std::string::size_type end = s.find(delimiter);

    while (end != std::string::npos) {
        token = s.substr(start, end - start);
        tokens.push_back(token);
        start = end + 1;
        end = s.find(delimiter, start);
    }

    token = s.substr(start);
    tokens.push_back(token);

    return tokens;
}

std::vector<std::string> splitAllCharacters(const std::string& s) {
    std::vector<std::string> characters;

    if (s.empty()) {
        return characters;
    }

    for (char c : s) {
        characters.push_back(std::string(1, c));
    }

    return characters;
}

std::string join(const std::vector<std::string>& strings, const std::string& delimiter) {
    if (strings.empty()) {
        return "";
    }

    std::string result = strings[0];

    for (size_t i = 1; i < strings.size(); ++i) {
        result += delimiter;
        result += strings[i];
    }

    return result;
}
