
# Turn-Based Strategy Game 👾

This project is a turn-based strategy game inspired by **"Tactical Monsters"**, developed as an academic project using **C++** and the **Qt framework**. The game features tactical combat on a hexagonal grid, diverse agents with unique abilities, and a simple, intuitive user interface.

## 🚀 Key Features

### 🎮 Gameplay Mechanics

  * **Turn-Based Combat**: Players take turns moving their agents and attacking enemies.
  * **Dynamic Hexagonal Grid**: The game board is dynamically loaded from a text file, supporting various map layouts with different terrain types (ground, water, and rock).
  * **Diverse Agents**: A total of 26 unique agents are implemented, categorized into four classes:
      * **Grounded**: Can only move and stand on the ground.
      * **Water Walking**: Can move and stand on both ground and water.
      * **Flying**: Can move over any terrain but can only stand on the ground.
      * **Floating**: Can move and stand on any terrain type.
  * **Attack & Counter-Attack System**: When an agent attacks, the enemy counter-attacks with half its damage. The attacking agent then randomly moves to an adjacent, valid cell.
  * **Pathfinding with BFS**: The Breadth-First Search (BFS) algorithm is used to determine reachable cells for movement and attack range, ensuring optimal pathfinding.

### 🖼️ User Interface

  * **Multi-Screen UI**: The game features a splash screen, a main menu, a player name input dialog, and the main game board.
  * **Drag-and-Drop Deployment**: Players can deploy their agents onto the starting zones using a seamless drag-and-drop mechanism.
  * **Visual Feedback**: The game board provides clear visual feedback:
      * Yellow highlights for the selected agent.
      * Green highlights for reachable cells.
      * Red highlights for attackable enemy agents.
      * **HP Bars** for each agent, showing their health status.

## ✅ Project Status

The project is fully functional and meets all core requirements of both phases. All major features, including the game logic, UI, and memory management, are complete.

**Bonus features implemented:**

  * **Hover effect on selectable cells**: Highlights cells that an agent can move to or attack.
  * **Health bars**: Visual display of each agent's health.
  * **Memory Management**: The project is robust and free from critical memory-related bugs like segmentation faults.

## ⚙️ How to Build and Run

### Prerequisites

  * C++ compiler (supporting C++17)
  * CMake (version 3.16 or higher)
  * Qt (version 5 or 6 with `Widgets` component)

### Build Instructions

1.  Clone the repository:

    ```bash
    git clone https://github.com/YOUR_USERNAME/TurnBased_StrategyGame.git
    cd TurnBased_StrategyGame
    ```

2.  Create a build directory and run CMake:

    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3.  Build the project:

    ```bash
    cmake --build .
    ```

4.  Run the executable from the build directory:

    ```bash
    ./TurnBased_StrategyGame
    ```

## ✒️ Author

 [Pedram Arianmanesh](https://www.google.com/search?q=https://github.com/Pedram-Arianmanesh)

## License

This project is licensed under the [GPL3 License](https://www.gnu.org/licenses/gpl-3.0.html).
