#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <SDL2/SDL.h>

#include "tools.h"
#include "ships.h"
#include "dialogs.h"

#define BACKGROUND_IMAGE "../assets/images/gameFond1.jpg"

// NB:
//   display_* functions execute SDL_RenderPresent
//   render_* functions don't

void load_interface_components(void);
void free_interface_components(void);

void init_colors(void);
void init_rectangles(void);

void display_map(map_t, unsigned, unsigned short[], unsigned, unsigned);
void display_fake_loading(unsigned);
void display_dialog(unsigned);
void display_quit_dialog(void);

void render_self(ship_t *, short, short);
void render_foe(ship_t *, short, short);
void render_bars(ship_t *, SDL_Rect *, short, short, bool);
void render_combat_box(void);
void render_help_box(void);
void render_overlay_bg(SDL_Rect *);
void render_background(void);

#endif /* _INTERFACE_H */
