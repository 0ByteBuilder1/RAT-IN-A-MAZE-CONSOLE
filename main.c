/*
================================================================================
    RAT IN A MAZE PUZZLE SOLVER - ENHANCED VISUAL VERSION
    Algorithm: Backtracking (4-Directional Movement + Multiple Solutions)
    Features: Animation, All Paths, Shortest Path, File I/O
    Author: YES CHANDRA
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>  
#define MAX_SIZE 20
#define MAX_PATHS 100


#define COLOR_RESET 7
#define COLOR_RAT 14      
#define COLOR_PATH 10     
#define COLOR_WALL 12     
#define COLOR_START 11    
#define COLOR_END 13      
#define COLOR_VISITED 8   


int N;
int allPaths[MAX_PATHS][MAX_SIZE * MAX_SIZE][2];  
int pathLengths[MAX_PATHS];
int pathCount = 0;
int shortestPathIndex = -1;


typedef struct {
    int x, y;
} Position;


void setColor(int color);
void clearScreen();
void gotoxy(int x, int y);
void printMazeVisual(int maze[MAX_SIZE][MAX_SIZE], int solution[MAX_SIZE][MAX_SIZE], int ratX, int ratY);
void animateSolution(int maze[MAX_SIZE][MAX_SIZE], int pathIndex);
bool isSafe(int maze[MAX_SIZE][MAX_SIZE], int x, int y, bool visited[MAX_SIZE][MAX_SIZE]);
void findAllPaths(int maze[MAX_SIZE][MAX_SIZE], int x, int y, bool visited[MAX_SIZE][MAX_SIZE], 
                  Position path[], int pathLen);
void displayAllPaths(int maze[MAX_SIZE][MAX_SIZE]);
void findShortestPath();
void displayMenu();
void loadPredefinedMaze(int maze[MAX_SIZE][MAX_SIZE], int choice);
void saveMazeToFile(int maze[MAX_SIZE][MAX_SIZE]);
void loadMazeFromFile(int maze[MAX_SIZE][MAX_SIZE]);
void displayStatistics();

/*
================================================================================
    MAIN FUNCTION
================================================================================
*/
int main() {
    int maze[MAX_SIZE][MAX_SIZE];
    int choice;
    
    clearScreen();
    
   
    setColor(COLOR_START);
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                                                            ║\n");
    printf("║         RAT IN A MAZE PUZZLE SOLVER - ENHANCED            ║\n");
    printf("║              Advanced Backtracking Algorithm               ║\n");
    printf("║                                                            ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    setColor(COLOR_RESET);
    
    printf("\n🐀 Features:\n");
    printf("  ✓ 4-Directional Movement (UP, DOWN, LEFT, RIGHT)\n");
    printf("  ✓ Find ALL possible paths\n");
    printf("  ✓ Identify SHORTEST path\n");
    printf("  ✓ Animated visualization\n");
    printf("  ✓ Colorful display\n");
    printf("  ✓ Save/Load maze from file\n\n");
    
    displayMenu();
    printf("Enter your choice (1-6): ");
    scanf("%d", &choice);
    
    if (choice >= 1 && choice <= 3) {
        loadPredefinedMaze(maze, choice);
    } else if (choice == 4) {
        printf("\nEnter the size of maze (N x N, max %d): ", MAX_SIZE);
        scanf("%d", &N);
        
        if (N > MAX_SIZE || N < 2) {
            printf("Invalid size! Using default size 5.\n");
            N = 5;
        }
        
        printf("\nEnter the maze (0 for blocked, 1 for open path):\n");
        for (int i = 0; i < N; i++) {
            printf("Row %d: ", i + 1);
            for (int j = 0; j < N; j++) {
                scanf("%d", &maze[i][j]);
            }
        }
    } else if (choice == 5) {
        loadMazeFromFile(maze);
    } else if (choice == 6) {
        printf("\nCreating demo maze for save feature...\n");
        N = 5;
        int demo[5][5] = {
            {1, 1, 0, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
            {0, 0, 1, 0, 1},
            {1, 1, 1, 1, 1}
        };
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                maze[i][j] = demo[i][j];
        
        saveMazeToFile(maze);
        printf("\n✓ Maze saved successfully! You can now load it using option 5.\n");
        printf("\nPress Enter to continue with this maze...");
        getchar();
        getchar();
    } else {
        printf("Invalid choice! Exiting.\n");
        return 1;
    }
    
    clearScreen();
    setColor(COLOR_START);
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║                      INPUT MAZE                            ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    setColor(COLOR_RESET);
    
    int dummy[MAX_SIZE][MAX_SIZE] = {0};
    printMazeVisual(maze, dummy, -1, -1);
    
    printf("\n\n");
    setColor(COLOR_PATH);
    printf("🔍 Finding all possible paths...\n");
    setColor(COLOR_RESET);
    
    
    if (maze[0][0] == 0) {
        setColor(COLOR_WALL);
        printf("\n❌ Starting position is blocked! No solution possible.\n");
        setColor(COLOR_RESET);
        return 1;
    }
    
    if (maze[N-1][N-1] == 0) {
        setColor(COLOR_WALL);
        printf("\n❌ Destination is blocked! No solution possible.\n");
        setColor(COLOR_RESET);
        return 1;
    }
    
    
    bool visited[MAX_SIZE][MAX_SIZE] = {false};
    Position path[MAX_SIZE * MAX_SIZE];
    pathCount = 0;
    
    findAllPaths(maze, 0, 0, visited, path, 0);
    
    if (pathCount == 0) {
        setColor(COLOR_WALL);
        printf("\n╔════════════════════════════════════════════════════════════╗\n");
        printf("║          ❌ NO SOLUTION EXISTS FOR THIS MAZE!             ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n");
        setColor(COLOR_RESET);
    } else {
        findShortestPath();
        
        Sleep(1000);
        displayAllPaths(maze);
        
        
        displayStatistics();
        
        
        setColor(COLOR_PATH);
        printf("\n🎬 Animating SHORTEST PATH...\n");
        setColor(COLOR_RESET);
        printf("Press Enter to start animation...");
        getchar();
        getchar();
        
        animateSolution(maze, shortestPathIndex);
        
        setColor(COLOR_PATH);
        printf("\n\n✓ Animation complete!\n");
        setColor(COLOR_RESET);
    }
    
    printf("\n\nPress Enter to exit...");
    getchar();
    
    return 0;
}

/*
================================================================================
    WINDOWS CONSOLE FUNCTIONS
================================================================================
*/
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void clearScreen() {
    system("cls");
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*
================================================================================
    DISPLAY MENU
================================================================================
*/
void displayMenu() {
    setColor(COLOR_PATH);
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                    SELECT MAZE TYPE                        ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    setColor(COLOR_RESET);
    printf("  1. 🟢 Easy Maze (5x5) - Simple paths\n");
    printf("  2. 🟡 Medium Maze (6x6) - Multiple routes\n");
    printf("  3. 🔴 Hard Maze (8x8) - Complex navigation\n");
    printf("  4. ⚙️  Custom Maze - Enter your own\n");
    printf("  5. 📂 Load Maze from File\n");
    printf("  6. 💾 Save Demo Maze to File\n");
    printf("════════════════════════════════════════════════════════════\n");
}

/*
================================================================================
    LOAD PREDEFINED MAZES
================================================================================
*/
void loadPredefinedMaze(int maze[MAX_SIZE][MAX_SIZE], int choice) {
    // Easy Maze - 5x5
    int easy[5][5] = {
        {1, 1, 0, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 1, 1, 1}
    };
    
    // Medium Maze - 6x6
    int medium[6][6] = {
        {1, 1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 0},
        {1, 0, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 1},
        {0, 0, 1, 1, 1, 1}
    };
    
    // Hard Maze - 8x8
    int hard[8][8] = {
        {1, 1, 0, 0, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 1},
        {0, 1, 0, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1}
    };
    
    if (choice == 1) {
        N = 5;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                maze[i][j] = easy[i][j];
    } else if (choice == 2) {
        N = 6;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                maze[i][j] = medium[i][j];
    } else if (choice == 3) {
        N = 8;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                maze[i][j] = hard[i][j];
    }
}

/*
================================================================================
    PRINT MAZE WITH VISUAL ENHANCEMENTS
================================================================================
*/
void printMazeVisual(int maze[MAX_SIZE][MAX_SIZE], int solution[MAX_SIZE][MAX_SIZE], int ratX, int ratY) {
    printf("\n    ");
    for (int j = 0; j < N; j++) {
        printf("  %d ", j);
    }
    printf("\n");
    
    printf("   ╔");
    for (int j = 0; j < N; j++) {
        printf("═══");
        if (j < N - 1) printf("╦");
    }
    printf("═══╗\n");
    
    for (int i = 0; i < N; i++) {
        printf(" %d ║", i);
        
        for (int j = 0; j < N; j++) {
            
            if (i == ratX && j == ratY) {
                setColor(COLOR_RAT);
                printf(" 🐀");
                setColor(COLOR_RESET);
            }
            
            else if (i == 0 && j == 0) {
                setColor(COLOR_START);
                printf(" S ");
                setColor(COLOR_RESET);
            }
           
            else if (i == N-1 && j == N-1) {
                setColor(COLOR_END);
                printf(" E ");
                setColor(COLOR_RESET);
            }
            
            else if (solution[i][j] == 1) {
                setColor(COLOR_PATH);
                printf(" ● ");
                setColor(COLOR_RESET);
            }
            // Wall
            else if (maze[i][j] == 0) {
                setColor(COLOR_WALL);
                printf(" ▓ ");
                setColor(COLOR_RESET);
            }
            
            else {
                printf("   ");
            }
            
            printf("║");
        }
        
        printf("\n");
        
        if (i < N - 1) {
            printf("   ╠");
            for (int j = 0; j < N; j++) {
                printf("═══");
                if (j < N - 1) printf("╬");
            }
            printf("═══╣\n");
        }
    }
    
    printf("   ╚");
    for (int j = 0; j < N; j++) {
        printf("═══");
        if (j < N - 1) printf("╩");
    }
    printf("═══╝\n");
    
    printf("\n  Legend: ");
    setColor(COLOR_START);
    printf("S=Start");
    setColor(COLOR_RESET);
    printf(" | ");
    setColor(COLOR_END);
    printf("E=End");
    setColor(COLOR_RESET);
    printf(" | ");
    setColor(COLOR_PATH);
    printf("●=Path");
    setColor(COLOR_RESET);
    printf(" | ");
    setColor(COLOR_WALL);
    printf("▓=Wall");
    setColor(COLOR_RESET);
    printf(" | ");
    setColor(COLOR_RAT);
    printf("🐀=Rat");
    setColor(COLOR_RESET);
    printf("\n");
}

/*
================================================================================
    ANIMATE SOLUTION PATH
================================================================================
*/
void animateSolution(int maze[MAX_SIZE][MAX_SIZE], int pathIndex) {
    int solution[MAX_SIZE][MAX_SIZE] = {0};
    
    clearScreen();
    printf("\n");
    setColor(COLOR_PATH);
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║              ANIMATING SHORTEST PATH                       ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    setColor(COLOR_RESET);
    
    for (int i = 0; i < pathLengths[pathIndex]; i++) {
        int x = allPaths[pathIndex][i][0];
        int y = allPaths[pathIndex][i][1];
        solution[x][y] = 1;
        
        gotoxy(0, 4);
        printMazeVisual(maze, solution, x, y);
        
        printf("\n  Step %d of %d", i + 1, pathLengths[pathIndex]);
        
        Sleep(300); 
    }
}

/*
================================================================================
    CHECK IF POSITION IS SAFE (4-DIRECTIONAL)
================================================================================
*/
bool isSafe(int maze[MAX_SIZE][MAX_SIZE], int x, int y, bool visited[MAX_SIZE][MAX_SIZE]) {
    return (x >= 0 && x < N && y >= 0 && y < N && 
            maze[x][y] == 1 && !visited[x][y]);
}

/*
================================================================================
    FIND ALL PATHS - RECURSIVE BACKTRACKING (4-DIRECTIONAL)
================================================================================
*/
void findAllPaths(int maze[MAX_SIZE][MAX_SIZE], int x, int y, bool visited[MAX_SIZE][MAX_SIZE], 
                  Position path[], int pathLen) {
    
    
    path[pathLen].x = x;
    path[pathLen].y = y;
    pathLen++;
    
    
    visited[x][y] = true;
    
    
    if (x == N - 1 && y == N - 1) {
        if (pathCount < MAX_PATHS) {
            // Store this path
            for (int i = 0; i < pathLen; i++) {
                allPaths[pathCount][i][0] = path[i].x;
                allPaths[pathCount][i][1] = path[i].y;
            }
            pathLengths[pathCount] = pathLen;
            pathCount++;
        }
    } else {
        
        if (isSafe(maze, x, y + 1, visited)) {
            findAllPaths(maze, x, y + 1, visited, path, pathLen);
        }
        
        
        if (isSafe(maze, x + 1, y, visited)) {
            findAllPaths(maze, x + 1, y, visited, path, pathLen);
        }
    
        
        if (isSafe(maze, x, y - 1, visited)) {
            findAllPaths(maze, x, y - 1, visited, path, pathLen);
        }
        
        
        if (isSafe(maze, x - 1, y, visited)) {
            findAllPaths(maze, x - 1, y, visited, path, pathLen);
        }
    }
    
    
    visited[x][y] = false;
}

/*
================================================================================
    FIND SHORTEST PATH
================================================================================
*/
void findShortestPath() {
    if (pathCount == 0) return;
    
    int minLength = pathLengths[0];
    shortestPathIndex = 0;
    
    for (int i = 1; i < pathCount; i++) {
        if (pathLengths[i] < minLength) {
            minLength = pathLengths[i];
            shortestPathIndex = i;
        }
    }
}

/*
================================================================================
    DISPLAY ALL PATHS FOUND
================================================================================
*/
void displayAllPaths(int maze[MAX_SIZE][MAX_SIZE]) {
    clearScreen();
    setColor(COLOR_PATH);
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║                  ALL PATHS FOUND: %2d                       ║\n", pathCount);
    printf("╚════════════════════════════════════════════════════════════╝\n");
    setColor(COLOR_RESET);
    
    printf("\nPath Details:\n");
    printf("════════════════════════════════════════════════════════════\n");
    
    for (int i = 0; i < pathCount && i < 10; i++) { 
        if (i == shortestPathIndex) {
            setColor(COLOR_PATH);
            printf("Path %d (SHORTEST): Length = %d steps ⭐\n", i + 1, pathLengths[i]);
            setColor(COLOR_RESET);
        } else {
            printf("Path %d: Length = %d steps\n", i + 1, pathLengths[i]);
        }
        
        printf("  Route: ");
        for (int j = 0; j < pathLengths[i] && j < 15; j++) {  
            printf("(%d,%d)", allPaths[i][j][0], allPaths[i][j][1]);
            if (j < pathLengths[i] - 1 && j < 14) printf(" → ");
        }
        if (pathLengths[i] > 15) printf(" ...");
        printf("\n\n");
    }
    
    if (pathCount > 10) {
        printf("... and %d more paths\n", pathCount - 10);
    }
}

/*
================================================================================
    DISPLAY STATISTICS
================================================================================
*/
void displayStatistics() {
    setColor(COLOR_START);
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║                      STATISTICS                            ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    setColor(COLOR_RESET);
    
    printf("  📊 Total paths found: %d\n", pathCount);
    printf("  ⭐ Shortest path length: %d steps\n", pathLengths[shortestPathIndex]);
    
    
    int totalLength = 0;
    int maxLength = pathLengths[0];
    for (int i = 0; i < pathCount; i++) {
        totalLength += pathLengths[i];
        if (pathLengths[i] > maxLength) {
            maxLength = pathLengths[i];
        }
    }
    float avgLength = (float)totalLength / pathCount;
    
    printf("  📏 Average path length: %.2f steps\n", avgLength);
    printf("  📈 Longest path length: %d steps\n", maxLength);
    printf("  🎯 Maze size: %d x %d\n", N, N);
}

/*
================================================================================
    SAVE MAZE TO FILE
================================================================================
*/
void saveMazeToFile(int maze[MAX_SIZE][MAX_SIZE]) {
    FILE *file = fopen("maze.txt", "w");
    if (file == NULL) {
        printf("Error: Could not create file!\n");
        return;
    }
    
    fprintf(file, "%d\n", N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file, "%d ", maze[i][j]);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
}

/*
================================================================================
    LOAD MAZE FROM FILE
================================================================================
*/
void loadMazeFromFile(int maze[MAX_SIZE][MAX_SIZE]) {
    FILE *file = fopen("maze.txt", "r");
    if (file == NULL) {
        printf("Error: File 'maze.txt' not found!\n");
        printf("Please use option 6 to create a sample maze file first.\n");
        exit(1);
    }
    
    fscanf(file, "%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(file, "%d", &maze[i][j]);
        }
    }
    
    fclose(file);
    printf("\n✓ Maze loaded successfully from 'maze.txt'!\n");
    Sleep(1000);
}

/*
================================================================================
 
     TIME COMPLEXITY: O(4^(N^2)) for finding all paths
    SPACE COMPLEXITY: O(N^2) for recursion + O(N^2 * P) for storing paths
    
================================================================================
*/