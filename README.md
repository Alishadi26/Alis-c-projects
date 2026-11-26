# C & C++ Projects

Terminal programs I've written while learning C and C++ at the Arab Academy for Science, Technology & Maritime Transport (AASTMT).

| Project | Language | What it does |
|---|---|---|
| [Currency Calculator](currency-calculator/) | C | Menu-driven tool for EGP / EUR / USD conversion plus a four-operation calculator |
| [Snake](snake-game/) | C++ | Real-time Snake game in the terminal: colors, wrap-around walls, and non-blocking keyboard input |

## Run them

```bash
git clone https://github.com/Alishadi26/Alis-c-projects.git
cd Alis-c-projects
make            # builds ./calculator and ./snake
./calculator
./snake         # W A S D to move, Q to quit
```

> Snake uses `termios`/`unistd`, so it runs on macOS and Linux (or WSL on Windows).

---

### Currency Calculator (`currency-calculator/main.c`)

- Main menu loop built with `do … while` and `switch`
- Exchange rates stored as `#define` constants
- Input validation: rejects non-numbers and negative amounts, and blocks division by zero
- Each menu is split into its own function

### Snake (`snake-game/snake.cpp`)

- Puts the terminal in **raw, non-blocking mode** (`termios`, `fcntl`) so the snake keeps moving without waiting for Enter
- Draws with **ANSI escape codes** for color and to redraw the screen
- Stores the snake body in a `std::vector<Point>`, with self-collision detection and wrap-around edges
- The game loop runs at about 10 FPS (`usleep(100000)`)

## What I practiced
Control flow, functions, input validation, structs and enums, the STL `vector`, terminal I/O, and Makefiles.
