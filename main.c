#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define WIDTH 1920
#define HEIGHT 1080

const unsigned int LINE_COLORS[] = {0x9AC2B3, 0xC7B8EA, 0xB0BEC5, 0xFBC02D,
                                    0xEF9A9A, 0x81C784, 0xA5D6A7, 0xDCE775,
                                    0x90A4AE, 0xCCEEFF};

int is_all_digits(const char *str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc != 2) {
        printf("Usage: %s <walker_number>\n", argv[0]);
        return -1;
    }

    if (!is_all_digits(argv[1])) {
        printf("Argument isn't a valid number.\nProgram Terminated\n");
        return -1;
    }

    int walker_number = atoi(argv[1]);

    SDL_Window *pwindow =
        SDL_CreateWindow("Random Walker", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    // Init walkers
    SDL_Rect *walkers = malloc(sizeof(SDL_Rect) * walker_number);
    for (int i = 0; i < walker_number; i++) {
        SDL_Rect *cur_walker = walkers + i;
        cur_walker->x = WIDTH / 2;
        cur_walker->y = HEIGHT / 2;
        cur_walker->h = 5;
        cur_walker->w = 5;
    }

    int scale = 5;
    int app_running = 1;
    while (app_running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) app_running = 0;
        }

        for (int iwalkers = 0; iwalkers < walker_number; iwalkers++) {
            SDL_Rect *cur_walker = walkers + iwalkers;
            int dir = rand() % 4;

            // Walk to dest pixel by pixel
            for (int step = 0; step < scale; step++) {
                switch (dir) {
                    case 0:
                        cur_walker->x += 1;
                        break;
                    case 1:
                        cur_walker->x -= 1;
                        break;
                    case 2:
                        cur_walker->y += 1;
                        break;
                    case 3:
                        cur_walker->y -= 1;
                        break;
                    default:
                        fprintf(stderr, "Error: Unknown Dir\n");
                        break;
                }

                // Rotate different colors
                unsigned int color = LINE_COLORS[iwalkers % 10];
                SDL_FillRect(psurface, cur_walker, color);
            }
        }
        SDL_UpdateWindowSurface(pwindow);
    }
}
