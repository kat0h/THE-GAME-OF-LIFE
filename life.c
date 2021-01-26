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
int lifeGetPos(struct life *game, int x, int y);
void lifeDrawGen(struct life *game);
int lifeLivesAround(struct life *game, int x, int y);
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
int gen1_width = 10;
int gen1_height = 10;
char gen1[10 * 10] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main() {
  struct life game = LIFE_INIT;
  lifeNewGame(&game, gen1_height, gen1_width, gen1);
  /* int counter = 0; */
  clearScreen();
  lifeDrawGen(&game);
  char c;
  while (scanf("%c", &c), c != 'q') {
    clearScreen();
    lifeNextGen(&game);
    lifeDrawGen(&game);
  }
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

int lifeGetPos(struct life *game, int x, int y) {
  if ((x < 0) || (x >= game->width) || (y < 0) || (y >= game->height))
    return -1;
  return (y * game->width + x);
}

void lifeDrawGen(struct life *game) {
  int height = game->height;
  int width = game->width;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (game->cell[lifeGetPos(game, x, y)] == 0) {
        printf("□ ");
      } else {
        printf("■ ");
      }
    }
    printf("\n");
  }
}

int lifeLivesAround(struct life *game, int x, int y) {
  int count = 0;
  for (int a = x - 1; a <= x + 1; a++) {
    for (int b = y - 1; b <= y + 1; b++) {
      if (!(a == x && b == y)){
        int pos = lifeGetPos(game, a, b);
        if (pos != -1)
          count += game->cell[pos];
      }
    }
  }
  return count;
}

void lifeNextGen(struct life *game) {
  char *nextGen;
  nextGen = malloc(sizeof(char) * game->width * game->height);
  for (int y = 0; y < game->height; y++) {
    for (int x = 0; x < game->width; x++) {
      // 対応するセルの次の世代を求める
      int cellArrive = lifeLivesAround(game, x, y);
      // 生きている
      if (game->cell[lifeGetPos(game, x, y)] == 1){
        if (cellArrive == 2 || cellArrive == 3){
          nextGen[lifeGetPos(game, x, y)] = 1;
        } else if(cellArrive <= 1 || cellArrive >= 4){
          nextGen[lifeGetPos(game, x, y)] = 0;
        }
      } else {
        if (cellArrive == 3) {
          nextGen[lifeGetPos(game, x, y)] = 1;
        }
      }
      // 死んでいる
    }
  }
  int c = game->height * game->width;
  for (int l = 0; l < c; l++) {
    game->cell[l] = nextGen[l];
  }
}
