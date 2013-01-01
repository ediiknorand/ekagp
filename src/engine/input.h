#ifndef H_ENGINE_INPUT_H
#define H_ENGINE_INPUT_H

#include <SDL/SDL.h>
#include "../util/list.h"

#define ENGINE_INPUT_KEYDOWN 10
#define ENGINE_INPUT_KEYUP 11
#define ENGINE_INPUT_KEYPRESSED 12
#define ENGINE_INPUT_KEYRELEASED 13

typedef struct
{
  SDLKey key;
  Uint8 *var;
  int type;
  Uint8 prevstate;
} Engine_input_binding;

typedef struct
{
  Uint8 *var;
  int *x, *y;
} Engine_input_binding_mouse;

typedef struct
{
  List *keys;
  Engine_input_binding_mouse mouse;
} Engine_input;

Engine_input engine_input;

void engine_input_load();
void engine_input_unload();

void engine_input_bind_key(SDLKey k, Uint8 *state, int type);
void engine_input_bind_mouse(Uint8 *state, int *x, int *y);

void engine_input_refresh();

#endif
