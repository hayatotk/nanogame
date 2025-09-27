#include "Level.hpp"
#include <cstdio>
#include <cstring>

int level[15][64];
int current_level = 0;

bool load_level(int id) {
    char path[64];
    snprintf(path, sizeof(path), "level%d.txt", id);
    FILE* f = fopen(path, "r");
    if (!f) return false;
    char line[80];
    int y = 0;
    while (fgets(line, sizeof(line), f) && y < 15) {
        for (int x = 0; x < 64 && line[x]; x++) {
            if (line[x] == '1') level[y][x] = 1;
            else if (line[x] == '2') level[y][x] = 2;
            else level[y][x] = 0;
        }
        y++;
    }
    fclose(f);
    return true;
}
