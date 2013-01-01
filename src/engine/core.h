#include <SDL/SDL.h>

#ifndef H_ENGINE_CORE_H
#define H_ENGINE_CORE_H

/* Structures */
typedef struct
{
  int width, height, bpp;
  Uint32 flags;
  SDL_Surface *surface;
  Uint32 delay;
} Engine_screen;

typedef struct
{
  int loaded;
  void *(*load_fnc)(void*);
  void *(*unload_fnc)(void*);

  int (*logic_fnc)(void*, Uint8*, double);

  void *data;
} Engine_scene;

typedef struct
{
  int loaded;
  void *(*load_fnc)(void*);
  void *(*unload_fnc)(void*);

  void (*render_fnc)(void*, void*, double);

  void *data;
} Engine_resource;

/* Global Vars */
Engine_screen engine_screen;
Engine_scene engine_scene;
Engine_resource engine_resource;

/* Init functions */
void engine_init_sdl();
void engine_init_screen(int width, int height, int bpp, Uint32 flags);
void engine_set_title(const char *title, const char *icon);

/* Main Loop */
void engine_main_loop();

/* Generic Refresh Functions */
int engine_logic_refresh(double delta);
void engine_render_refresh(double delta);

/* Loader Function */
void engine_load_scene(void *(*loadfnc)(void*), void *(*unloadfnc)(void*), int (*logicfnc)(void*,Uint8*,double));
void engine_load_resource(void *(*loadfnc)(void*), void *(*unloadfnc)(void*), void (*renderfnc)(void*,void*,double));

#endif
