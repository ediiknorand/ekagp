#include <SDL/SDL.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "core.h"
#include "input.h"

/* Init functions */
void engine_init_sdl()
{
  if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
}

void engine_init_screen(int width, int height, int bpp, Uint32 flags)
{
  /* Init engine_screen struct */
  engine_screen.width = width;
  engine_screen.height = height;
  engine_screen.bpp = bpp;
  engine_screen.flags = flags;
  engine_screen.delay = 10;

  engine_screen.surface = SDL_SetVideoMode(width, height, bpp, flags);
  if(!(engine_screen.surface))
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    exit(1);
  }
  /* input load */
  engine_input_load();
}

void engine_set_title(const char *title, const char *icon)
{
  SDL_WM_SetCaption(title, icon);
}

void engine_init_scene()
{
  /* place holder values */
  engine_scene.loaded = 0;
  engine_scene.load_fnc = NULL;
  engine_scene.unload_fnc = NULL;
  engine_scene.logic_fnc = NULL;
  engine_scene.data = NULL;
}

void engine_init_resource()
{
  /* place holder values */
  engine_resource.loaded = 0;
  engine_resource.load_fnc = NULL;
  engine_resource.unload_fnc = NULL;
  engine_resource.render_fnc = NULL;
  engine_resource.data = NULL;
}

/* Main Loop */
void engine_main_loop()
{
  int running;
  Uint32 now, before;

  if(!(engine_scene.loaded))
  {
    fprintf(stderr, "Nothing loaded!\n");
    exit(1);
  }

  running = 1;
  before = SDL_GetTicks();
  while(running)
  {
    now = SDL_GetTicks();
    running = engine_logic_refresh((now - before)*0.001);
    //if(!running) break; /* Avoid unnecessary render refresh */
    if(!running) exit(0);
    if(engine_resource.loaded && engine_resource.render_fnc)
      engine_render_refresh((now - before)*0.001);
    before = now;
    SDL_Delay(engine_screen.delay); /* <- Why not Vsynced? */
  }
}


/* Generic Refresh Functions */
int engine_logic_refresh(double delta)
{
  engine_input_refresh();
  return engine_scene.logic_fnc(engine_scene.data, delta);
}

void engine_render_refresh(double delta)
{
  engine_resource.render_fnc(engine_scene.data, engine_resource.data, delta);
  SDL_Flip(engine_screen.surface);
  SDL_FillRect(engine_screen.surface, NULL, 0);
}

/* Scene Loader Function */
void engine_load_scene(void *(*loadfnc)(void*), void *(*unloadfnc)(void*), int (*logicfnc)(void*,double))
{
  if(engine_scene.loaded)
    engine_scene.data = engine_scene.unload_fnc(engine_scene.data);
  if(loadfnc && unloadfnc && logicfnc)
  {
    engine_scene.loaded = 1;
    engine_scene.load_fnc = loadfnc;
    engine_scene.unload_fnc = unloadfnc;
    engine_scene.logic_fnc = logicfnc;
  } else {
    fprintf(stderr, "NULL functions!\n");
    exit(1);
  }
  engine_scene.data = engine_scene.load_fnc(engine_scene.data);
}

void engine_load_resource(void *(*loadfnc)(void*), void *(*unloadfnc)(void*), void (*renderfnc)(void*,void*,double))
{
  if(engine_resource.loaded)
    engine_resource.data = engine_resource.unload_fnc(engine_resource.data);
  if(loadfnc && unloadfnc && renderfnc)
  {
    engine_resource.loaded = 1;
    engine_resource.load_fnc = loadfnc;
    engine_resource.unload_fnc = unloadfnc;
    engine_resource.render_fnc = renderfnc;
  } else {
    fprintf(stderr, "NULL functions!\n");
    exit(1);
  }
  engine_resource.data = engine_resource.load_fnc(engine_resource.data);
}
