# Football 2D

A turn-based 2D football (soccer) strategy game built in C using the **raylib** graphics library. Play head-to-head against a friend, pick your tactical formations, set your target score, and strategize your shots to score goals!

Developed by **Sakib** (Roll: 2505036) and **Ishaque** (Roll: 2505058).

---

## Features

* **Turn-Based Strategy Mechanics:** Drag and release players to aim and shoot them across the field.
* **Tactical Formations:** Choose from 5 different unique starting formations for both teams.
* **Customizable Match Settings:** Enter custom player names and configure a target score before starting.
* **Physics Simulation:** Realistic circle-to-circle collision handling between players, walls, and the ball.
* **Sound Effects & UI:** Immersive kick, collision, and goal sounds with a sleek, modern menu design.

---

## Prerequisites

To compile and run this game, you need to have **raylib** installed on your system.

* **raylib** (v4.0 or higher recommended)
* A C compiler (such as **GCC**, **Clang**, or **MinGW**)

---

## Project Structure

Ensure your project directory contains the source code and a `resources/` folder structured like this:


├── main.c
├── README.md
└── resources/
    ├── sounds/
    │   ├── kick.wav
    │   ├── collision.wav
    │   └── goal-sound.mp3
    ├── Football_field.png
    ├── Start1.png
    ├── Tutorial.png
    ├── Sakib_36.png
    ├── Ishaque_58.png
    ├── blue-formation1.png to blue-formation5.png
    └── red-formation1.png to red-formation5.png
``



## Installation & Compilation

### 1. Clone the Repository
```bash
git clone https://github.com/your-username/football-2d.git
cd football-2d
```

### 2. Compile and Run

#### **On Linux / macOS (using GCC)**
```bash
gcc main.c -o football_game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./football_game
```

#### **On Windows (using MinGW)**
```bash
gcc main.c -o football_game.exe -lraylib -lgdi32 -lwinmm
./football_game.exe
```

---

## How to Play

1. **Main Menu:** Navigate through the menu using your mouse to start a new game, view the tutorial, check credits, or read about the developers.
2. **Setup:** Enter custom player names and set your desired target score. Select your preferred tactical formation.
3. **Gameplay:** 
   * Each turn, the active team can drag and release one of their players to strike the ball.
   * Collide with opponents or pass to your own players strategically.
4. **Winning:** The first player to reach the target score wins the match!

---

## Credits

* **Graphics & Engine:** Built using [raylib](https://www.raylib.com/).
* **Audio & Assets:** FreeSound & custom image assets.