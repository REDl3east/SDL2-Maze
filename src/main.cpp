#include "main.h"

#include <chrono>
#include <thread>

constexpr int INITIAL_WORLD_SCALE = 1;
constexpr int INITIAL_WINDOW_WIDTH = 1001 * INITIAL_WORLD_SCALE;
constexpr int INITIAL_WINDOW_HEIGHT = 1001 * INITIAL_WORLD_SCALE;
constexpr int WORLD_WIDTH = INITIAL_WINDOW_WIDTH / INITIAL_WORLD_SCALE;
constexpr int WORLD_HEIGHT = INITIAL_WINDOW_HEIGHT / INITIAL_WORLD_SCALE;
constexpr const char *APP_NAME = "SDL Maze";

int main(int argc, char **argv) {
  SDL_Event event;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

  std::shared_ptr<SDL_Renderer> renderer(SDL_CreateRenderer(window, -1, 0), [](auto *p) { SDL_DestroyRenderer(p); });

  BinaryTreeMaze world(renderer, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, WORLD_WIDTH, WORLD_HEIGHT, INITIAL_WORLD_SCALE);

  world.init();

  bool done = false;
  bool quit = false;
  bool mouse_down = false;
  bool paused = false;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: {
          quit = true;
          break;
        }
        case SDL_KEYDOWN: {
          if (event.key.keysym.sym == SDLK_s) {
            world.save_time("../../assets");
          }
          if (event.key.keysym.sym == SDLK_p) {
            paused = !paused;
          }
          break;
        }
        case SDL_MOUSEBUTTONDOWN: {
          if (event.button.button == SDL_BUTTON_LEFT) {
            mouse_down = true;
          }
          break;
        }
        case SDL_MOUSEBUTTONUP: {
          if (event.button.button == SDL_BUTTON_LEFT) {
            mouse_down = false;
          }
          break;
        }
        case SDL_MOUSEMOTION: {
          if (mouse_down) {
            world.update_position(event.motion.xrel, event.motion.yrel);
          }
          break;
        }
        case SDL_MOUSEWHEEL: {
          int mousex, mousey;
          SDL_GetMouseState(&mousex, &mousey);
          if (event.wheel.y > 0) {  //up
            world.zoom_in(mousex, mousey);
          } else if (event.wheel.y < 0) {  //down
            world.zoom_out(mousex, mousey);
          }
          break;
        }
      }
    }

    if (quit) break;

    if (done || !world.iterate()) done = true;

    if (!paused) {
      SDL_RenderClear(renderer.get());

      world.render();

      SDL_RenderPresent(renderer.get());

      // std::this_thread::sleep_for (std::chrono::seconds(1));
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
