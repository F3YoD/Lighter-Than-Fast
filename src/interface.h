#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <SDL2/SDL.h>

#include "tools.h"
#include "ships.h"
#include "dialogs.h"
#include "combat.h"

/*
 * NB:
 *   display_* functions execute SDL_RenderPresent
 *   render_* functions don't
 */

void load_interface_components(void);
void free_interface_components(void);

void init_colors(void);
void init_rectangles(void);

void display_menu(void);
void display_map(map_t, unsigned, unsigned short[], unsigned, unsigned);
void display_fake_loading(unsigned);
void display_dialog(unsigned);
void display_quit_dialog(void);

void render_self(ship_t *, short, short);
void render_foe(ship_t *, short, short);
void render_bars(ship_t *, SDL_Rect *, short, short, bool);
void render_choices(SDL_Rect *, short, char *[], short, short, short, short);
void render_belongings(ship_t *);
void render_combat_box(enum combat_choice, ship_t *);
void render_shop_box(enum shop_choice, ship_t *, ship_t *);
void render_help_box(void);
void render_overlay_bg(SDL_Rect *, short);
void render_background(void);

#endif /* _INTERFACE_H */
