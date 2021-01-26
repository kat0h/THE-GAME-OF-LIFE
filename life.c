/*
 _____ _   _ _____    ____    _    __  __ _____    ___  _____
|_   _| | | | ____|  / ___|  / \  |  \/  | ____|  / _ \|  ___|
  | | | |_| |  _|   | |  _  / _ \ | |\/| |  _|   | | | | |_
  | | |  _  | |___  | |_| |/ ___ \| |  | | |___  | |_| |  _|
  |_| |_| |_|_____|  \____/_/   \_\_|  |_|_____|  \___/|_|
 _     ___ _____ _____
| |   |_ _|  ___| ____|
| |    | || |_  |  _|
| |___ | ||  _| | |___
|_____|___|_|   |_____|
*/

#include <stdio.h>
#include <stdlib.h>

struct life {
  int width;
  int height;
  char *cell;
};
#define LIFE_INIT                                                              \
  { 0, 0, NULL }

void clearScreen();
void lifeNewGame(struct life *game, int height, int width, char *initialState);
void lifeFreeMem(struct life *game);
void lifeDrawGen(struct life *game);
void lifeNextGen(struct life *game);

/*
State of 1st gen
char gen1[10*10] = {
  0,0,0,0,0,0,0,0,0,0,
  0,0,1,0,0,0,0,0,0,0,
  0,0,0,1,0,0,0,0,0,0,
  0,1,1,1,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0
};
*/
char gen1[10 * 10] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main() {
  struct life game = LIFE_INIT;
  lifeNewGame(&game, 10, 10, gen1);
  clearScreen();
  lifeDrawGen(&game);
  lifeFreeMem(&game);
  return 0;
}

void clearScreen() {
  printf("\033[2J");
  printf("\033[%d;%dH", 0, 0);
}

void lifeNewGame(struct life *game, int height, int width, char *initialState) {
  int celllen = height * width;
  game->height = height;
  game->width = width;
  game->cell = malloc(sizeof(char) * celllen);
  for (int i = 0; i < celllen; i++) {
    game->cell[i] = initialState[i];
  }
}

void lifeFreeMem(struct life *game) { free(game->cell); }

void lifeDrawGen(struct life *game) {
  int height = game->height;
  int width = game->width;
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      if (game->cell[h * 10 + w] == 0) {
        printf("□ ");
      } else {
        printf("■ ");
      }
    }
    printf("\n");
  }
}

void lifeNextGen(struct life *game) {}
