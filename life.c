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
void lifeNewGame(struct life *game, int height, int width);
void lifeFreeMem(struct life *game);
void lifeDrawGen(struct life *game);

int main() {
  struct life game = LIFE_INIT;
  lifeNewGame(&game, 10, 10);
  clearScreen();
  lifeDrawGen(&game);
  return 0;
}

void clearScreen(){
  printf("\033[2J");
  printf("\033[%d;%dH" ,0,0);
}

void lifeNewGame(struct life *game, int height, int width) {
  int celllen = height * width;
  game->height = height;
  game->width = width;
  game->cell = malloc(sizeof(char) * celllen);
  for (int i = 0; i < celllen; i++) {
    game->cell[i] = 0;
  }
}

void lifeFreeMem(struct life *game){
  free(game->cell);
}

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
