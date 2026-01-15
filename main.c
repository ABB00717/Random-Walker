#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#define True 1

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <walker_number>\n", argv[0]);
    return -1;
  }

  SDL_CreateWindow("Test", 0, 0, 1920, 1080, 0);
  int app_running = 1;
  while (app_running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        app_running = 0;
    }
  }
}
