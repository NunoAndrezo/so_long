# 🎮 so_long – 42 Lisboa

> First graphical project of the 42 cursus: build a simple 2D game using **MiniLibX (mlx_linux)**. The player navigates a map, collects items, and reaches the exit — all while following strict coding norms and managing resources carefully.

---

## 🧠 Overview

**so_long** introduces basic graphics programming and event handling using **MiniLibX**, a lightweight graphical library provided by 42.  
The game consists of:

- Parsing a 2D map file (`.ber`) that defines the game world.
- Rendering a graphical representation of walls, player, collectibles, and exit.
- Managing player input (WASD/Arrow keys) to move through the map.
- Collecting all items before exiting the level.
- Ensuring all edge cases, errors, and memory are cleanly handled.

---

## 🔁 Game Mechanics

- The map is defined by a `.ber` file composed of:
  - `1` → Wall
  - `0` → Floor
  - `P` → Player (must be exactly one)
  - `C` → Collectible (at least one required)
  - `E` → Exit (must be exactly one)
- The map must be:
  - **Rectangular**
  - **Surrounded entirely by walls**
  - **Contain valid characters only**
- The player can move **up, down, left, right**.
- The player **must collect all collectibles (`C`) before reaching the exit (`E`)**.
- Invalid maps or inputs should output:  
  ```bash
  Error
  <descriptive message>
  ```
  and exit cleanly.

---

## ⚙️ Installation & Setup

### ✅ Dependencies

Ensure you're on **Linux** and have required packages:

```bash
sudo apt-get install xorg libxext-dev libbsd-dev zlib1g-dev
```

### 📦 Getting Started

1. **Clone your repo**:
   ```bash
   git clone https://github.com/NunoAndrezo/so_long.git
   cd so_long
   ```

2. **Download and configure MiniLibX**:
   - Download the [official Linux version of MiniLibX](https://github.com/42Paris/minilibx-linux)
   - Rename the folder to `mlx_linux` and place it in your project root.

3. **Build the project**:
   ```bash
   make
   ```

---

## 🎮 How to Play

```bash
./so_long path/to/map.ber
```

### Controls

| Key       | Action     |
|-----------|------------|
| W / ↑     | Move up    |
| A / ←     | Move left  |
| S / ↓     | Move down  |
| D / →     | Move right |
| ESC       | Quit game  |

---

## 🏛️ Project Structure (Typical)

```text
so_long/
├── assets/               # .xpm image files
├── maps/                 # .ber test maps
├── mlx_linux/            # MiniLibX library
├── src/                  # Source files
├── includes/             # Header files
├── Makefile
└── README.md
```

---

## 🧩 Mandatory Features

- Map file parser and validator  
- Rendering via MiniLibX  
- Player movement and input handling  
- Step counter displayed in terminal  
- Win/lose detection  
- Clean error messages and memory deallocation  

---

## 🔍 Map Validation

The map parser must validate:

- File has a `.ber` extension  
- Map is rectangular  
- Surrounded by walls  
- Exactly **1 player**, **1 exit**, **≥ 1 collectible**  
- All tiles are reachable from the player (use BFS/DFS)  

Example error:

```bash
Error
Map is not rectangular
```

---

## 🖼️ Graphics

- Graphics are rendered using MiniLibX.  
- Each tile is typically **32×32 pixels**.  
- Images (`.xpm` format) represent:
  - Walls  
  - Floors  
  - Player  
  - Collectibles  
  - Exit (locked/unlocked)  

Example tile rendering logic:

```c
mlx_put_image_to_window(mlx, win, img_wall, x * 32, y * 32);
```

---

## 🔄 Game Loop

- **Initialization**  
  - Parse and validate the map.  
  - Open the game window.  
  - Draw the initial frame.  
- **Runtime**  
  - Listen for key events.  
  - Update player position, collectible count, and step counter.  
  - Refresh the window after each move.  
- **Termination**  
  - On win, exit, or ESC: destroy window, free memory, exit cleanly.

---

## 💥 Error Handling

- All errors must output:
  ```bash
  Error
  <message>
  ```
  to `stderr`.  
- Free all allocated memory on exit or failure.  
- Common error scenarios:
  - Invalid characters in the map  
  - Unreachable exit  
  - No collectibles  
  - File does not exist or wrong extension  

---

## 🧪 Testing & Edge Cases

✅ Recommended `.ber` tests:

- Valid rectangular map  
- Map with unreachable exit  
- No collectibles  
- Multiple players  
- Exit not surrounded by walls  
- Extra newlines or empty lines  
- Long corridors and dead ends  
- Trick maps for flood fill  

Check for memory leaks with Valgrind:

```bash
valgrind ./so_long maps/test.ber
```

---

## 🚀 Bonus (If Implemented)

- Animate sprites (player walking, collectibles spinning)  
- Display step count in the game window  
- Add enemies that patrol  
- Integrate sound effects (SDL, libao, etc.)  
- Implement scrolling or camera follow  

---

## 📚 Resources

- 📘 [MiniLibX Docs](https://harm-smits.github.io/42docs/libs/minilibx/)  
- 🖥️ [42 Norminette](https://github.com/42School/norminette)  
- 🧭 [BFS/DFS Pathfinding](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)  
- 🛠️ [Valgrind Manual](https://valgrind.org/docs/manual/quick-start.html)  

---

## 👤 Author

**Nuno Andrezo**  
42 Lisboa Student  
🔗 GitHub: [@NunoAndrezo](https://github.com/NunoAndrezo)

---
```  
