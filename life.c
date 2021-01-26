#include <stdio.h>
#include <stdlib.h>

struct life {
  int width;
  int height;
  char *cell;
};
#define LIFE_INIT                                                              \
  { 0, 0, NULL }

void lifeNewGame(struct life *game, int height, int width) {
  int celllen = height * width;
  game->height = height;
  game->width = width;
  game->cell = malloc(sizeof(char) * celllen);
  for (int i = 0; i < celllen; i++) {
    game->cell[i] = 0;
  }
}

void lifeDrawGen(struct life *game) {
  int height = game->height;
  int width = game->width;
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      printf("%d", game->cell[h * 10 + w]);
    }
    printf("\n");
  }
}

int main() {
  struct life game = LIFE_INIT;
  lifeNewGame(&game, 10, 10);
  lifeDrawGen(&game);
  return 0;
}
