#include "input.h"
#include <stdlib.h>


void engine_input_load()
{
  engine_input.keys = list_create();
  engine_input.mouse.x = NULL;
  engine_input.mouse.y = NULL;
  engine_input.mouse.var = NULL;
}

void engine_input_unload()
{
  list_destroy(engine_input.keys);
  engine_input.mouse.x = NULL;
  engine_input.mouse.y = NULL;
  engine_input.mouse.var = NULL;
}

void engine_input_bind_key(SDLKey k, Uint8 *state, int type)
{
  Engine_input_binding *b = malloc(sizeof(Engine_input_binding));
  b->key = k;
  b->var = state;
  b->type = type;
  b->prevstate = 0;
  list_enqueue(engine_input.keys, b, free);
}

void engine_input_bind_mouse(Uint8 *state, int *x, int *y)
{
  engine_input.mouse.x = x;
  engine_input.mouse.y = y;
  engine_input.mouse.var = state;
}

Uint8 engine_input_keydown(Uint8 *keyboard, SDLKey key)
{
  if(keyboard[key])
    return 1;
  return 0;
}

Uint8 engine_input_pressed(Uint8 *keyboard, SDLKey key, Uint8 prevstate)
{
  if(keyboard[key] && !prevstate)
    return 1;
  return 0;
}

Uint8 engine_input_released(Uint8 *keyboard, SDLKey key, Uint8 prevstate)
{
  if(prevstate && !keyboard[key])
    return 1;
  return 0;
}

void engine_input_refresh()
{
  List_node *p;
  Engine_input_binding *b;
  Uint8 *keystate;
  SDL_PumpEvents();
  keystate = SDL_GetKeyState(NULL);

  for(p = engine_input.keys->first; p; p = p->next)
  {
    b = (Engine_input_binding*)p->obj;
    switch(b->type)
    {
    case ENGINE_INPUT_KEYPRESSED:
      *(b->var) = engine_input_pressed(keystate, b->key, b->prevstate);
      b->prevstate = keystate[key];
      break;
    case ENGINE_INPUT_KEYRELEASED:
      *(b->var) = engine_input_released(keystate, b->key, b->prevstate);
      b->prevstate = keystate[key];
      break;
    case ENGINE_INPUT_KEYDOWN:
      *(b->var) = engine_input_keydown(keystate, b->key);
      break;
    case ENGINE_INPUT_KEYUP:
      *(b->var) = !(engine_input_keydown(keystate, b->key));
      break;
    }
  }
  if(engine_input.mouse.var)
    *engine_input.mouse.var = SDL_GetMouseState(engine_input.mouse.x, engine_input.mouse.y);
  else
  {
    if(engine_input.mouse.x || engine_input.mouse.y)
      SDL_GetMouseState(engine_input.mouse.x, engine_input.mouse.y);
  }
}
