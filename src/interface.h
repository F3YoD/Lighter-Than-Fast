#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "shared.h"
#include "tools.h"
#include "ships.h"
#include "dialogs.h"
#include "combat.h"

/*
 * NB:
 *   display_* functions execute SDL_RenderPresent
 *   render_* functions don't
 */

void render_projectile(bool, bool*);

void load_interface_components(void);
void free_interface_components(void);

void init_colors(void);
void init_rectangles(void);

void display_menu(void);
void display_map(map_matrix, unsigned, unsigned short[], unsigned, unsigned);
void display_fake_loading(unsigned);
void display_dialog(unsigned);
void display_quit_dialog(void);
void display_lost(void);
void display_noplasma(void);
void display_win(void);

void render_self(ship *, int, int);
void render_foe(ship *, int, int);
void render_bars(ship *, SDL_Rect *, int, int, bool);
void render_choices(short, char *[], int *, int, int, int);
void render_belongings(ship *);
void render_combat_box(enum combat_choice *, ship *, unsigned, unsigned);
void render_shop_box(enum shop_choice *, ship *, ship *, int);
void render_help_box(void);
void render_overlay_bg(SDL_Rect *, short);
void render_background(void);

#endif /* _INTERFACE_H */
