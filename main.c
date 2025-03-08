#include <stdio.h>
#include <conio.h>  // Use _getch() (Works only on Windows)
#include <windows.h>

#define MAP_WIDTH  149
#define MAP_HEIGHT 5

// Map data (Wall: 'w', Boundary: '#', Exit: 'E', Player: '@')
char map[MAP_HEIGHT][MAP_WIDTH] = {
    "###############################################################################################################################################",
    "#                           w                           w                                                     wE                              #",
    "@                     w                        w                                                              w                               #",
    "#                          w                           w                                                                                      #",
    "###############################################################################################################################################"
};

// Player position
int playerX = -1, playerY = -1;

// Find player position
void findPlayer() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == '@') {
                playerX = x;
                playerY = y;
                map[y][x] = ' ';  // Remove '@' from map (Player is managed separately)
                return;
            }
        }
    }
}

// Print the map (including the player)
void printMap() {
    system("cls");  // Clear console screen (Windows only)
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == playerX && y == playerY) {
                printf("@");  // Print player position
            } else {
                printf("%c", map[y][x]);  // Print the existing map
            }
        }
        printf("\n");
    }
}

// Ice movement function (stops at walls 'w', '#')
void movePlayer(char direction) {
    int newX = playerX, newY = playerY;

    switch (direction) {
        case 'w': case 'W':  // Move up
            while (newY > 0 && map[newY - 1][newX] != 'w' && map[newY - 1][newX] != '#') newY--;
            Beep(300, 100);
            break;
        case 's': case 'S':  // Move down
            while (newY < MAP_HEIGHT - 1 && map[newY + 1][newX] != 'w' && map[newY + 1][newX] != '#') newY++;
            Beep(1000, 100);
            break;
        case 'a': case 'A':  // Move left
            while (newX > 0 && map[newY][newX - 1] != 'w' && map[newY][newX - 1] != '#') newX--;
            Beep(400, 100);
            break;
        case 'd': case 'D':  // Move right
            while (newX < MAP_WIDTH - 1 && map[newY][newX + 1] != 'w' && map[newY][newX + 1] != '#') newX++;
            Beep(500, 100);
            break;
    }

    // Update player position
    playerX = newX;
    playerY = newY;

    // If the player reaches the exit ('E'), end the game
    if (map[playerY][playerX] == 'E') {
        system("cls");
        printf("\n\n\n\t\t\t*** Clear!! ***\n");
        Beep(1500, 500);  // Victory sound effect
        Sleep(10000);  // Pause for 10 seconds
        exit(0);  // End game
    }
}

int main() {
    findPlayer();  // Find initial player position
    while (1) {
        system("title icemaze");
        printMap();  // Print the map

        char input = _getch();  // Get key input
        if (input == 'q' || input == 'Q') break;  // Quit game if 'Q' is pressed

        movePlayer(input);  // Move player
    }

    return 0;
}
