
# Binary Clock

This project is a terminal-based **binary clock** that displays the current time (hours, minutes, seconds) in binary format. It updates in real-time using the `ncurses` library.

## Features

- Runs in the terminal.
- Displays time in binary format (HH:MM:SS).
- Real-time updates.
- Press `q` to quit.
- Optional `--no-header` flag to hide the header.

## Screenshot

Example output:

```bash
BINARY CLOCK
0 0 0 0 0 0
0 0 0 0 0 1
1 0 1 1 1 0
0 1 0 0 1 1
```

## Requirements

- CMake (version 3.10 or higher recommended)
- `ncurses` library
- C++ compiler (e.g., g++)

## Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Run

```bash
./binary_clock           # Runs with header
./binary_clock --no-header  # Runs without header
```

## Usage

- The clock shows each digit (HHMMSS) in 4-bit binary.
- Each line corresponds to one binary bit (from MSB to LSB).
- Press `q` to exit the program.

## License

This project is licensed under the [GNU General Public License v3.0](https://github.com/fsb3rke/binary-clock/blob/main/LICENSE).

You are free to use, modify, and distribute this software under the terms of the GPL-3.0 license.


## Contributing

Feel free to fork the repository and submit pull requests for improvements.
