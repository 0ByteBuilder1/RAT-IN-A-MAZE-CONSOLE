🐀 Rat in a Maze – Console Puzzle Solver (C Language)

A visually enhanced backtracking-based maze solver implemented in C for the Windows terminal.
This project finds all possible paths from the start (0,0) to the destination (N−1,N−1), identifies the shortest path, and animates the solution using console colors and cursor movement.

🚀 Features
✔ Backtracking Algorithm

4-directional movement: Up, Down, Left, Right

Recursive path exploration

Discovers all valid paths

Tracks visited cells

Prevents loops and backtracking errors

✔ Terminal Visualization

Uses Windows console colors

Unicode characters for walls, path, and rat:

🐀 Rat

● Path

▓ Wall

S / E (Start / End)

Animated traversal of the shortest path

✔ Multiple Maze Options

Predefined difficulty levels:

🟢 Easy (5×5)

🟡 Medium (6×6)

🔴 Hard (8×8)

User-defined custom maze input

Load-from-file support

Save-to-file support

✔ Statistics Output

After solving, program displays:

Total paths found

Shortest path length

Average path length

Longest path length

Maze size

📂 Folder Structure
RAT-IN-A-MAZE-CONSOLE/
│
├── main.c            # Complete project source code
├── README.md         # Project documentation
└── maze.txt          # Optional saved maze file

🛠 Technologies Used
Component	Technology
Language	C
OS	Windows
Compiler	MinGW / GCC
Libraries	stdio.h, stdlib.h, string.h, windows.h
🧠 How the Algorithm Works (Backtracking)

Start at (0,0).

Check if current cell is valid (inside maze, unvisited, and open).

Mark cell as visited and add to current path.

Explore all 4 directions:

Right

Down

Left

Up

If destination is reached → store the full path.

Backtrack: unmark the cell and return.

This continues until all possibilities are explored.

📸 Console Preview (Example)
╔════════════════════════════════════════════════════════════╗
║         RAT IN A MAZE PUZZLE SOLVER - ENHANCED            ║
╚════════════════════════════════════════════════════════════╝

🐀 Features:
 ✓ 4-Directional Movement (UP, DOWN, LEFT, RIGHT)
 ✓ Find ALL possible paths
 ✓ Identify SHORTEST path
 ✓ Animated visualization
 ✓ Colorful display
 ✓ Save/Load maze from file

▶️ How to Compile & Run
1️⃣ Compile the program

Using GCC (MinGW):

gcc main.c -o maze.exe

2️⃣ Run the program
./maze.exe

3️⃣ Enable Unicode (for box lines + emojis)

If you see weird characters, run this before running the program:

chcp 65001


Or add this to your code:

SetConsoleOutputCP(65001);

📁 File I/O Options
Save maze to file

The program creates a file named maze.txt containing:

Maze size N

N×N grid (0 = blocked, 1 = open)

Load maze from file

Select the appropriate menu option to read back the saved maze.

📊 Example Statistics Output
📊 Total paths found: 5
⭐ Shortest path length: 9 steps
📏 Average path length: 11.20 steps
📈 Longest path length: 15 steps
🎯 Maze size: 5 x 5

🧩 Future Enhancements

Add diagonal movement (8-directional solver)

Add BFS/A* algorithm for comparison

Port to Linux/Mac (remove Windows dependencies)

Create GUI version (Qt / SFML / HTML Canvas)

🙌 Author

YES CHANDRA
0ByteBuilder1
Developer • Programmer • Learner

GitHub: https://github.com/0ByteBuilder1