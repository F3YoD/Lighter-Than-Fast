#include "interface.h"

/* Global colors */
static SDL_Color white, gray;

/* Global textures */
static SDL_Texture *bg_texture, *bg_overlay, *dialog_texture, *continue_texture, *alien_pointer;
static image *health_bar_bg_img, *health_bar_img, *shield_bar_bg_img, *shield_bar_img;
static SDL_Texture *map_texture;
static SDL_Texture *red_dot_texture, *blue_dot_texture, *gray_dot_texture, *dot_texture;
static SDL_Texture *choices_texture;
static SDL_Texture *combat_box_texture;
static SDL_Texture *help_texture;
static SDL_Texture *self_texture, *foe_texture;
static SDL_Texture *belongings_texture;

/* Rendering zones (i.e. rectangles) */
static SDL_Rect inner_overlay_rect, continue_msg_rect;
static SDL_Rect icon_rect, alien_pointer_map_rect, alien_cursor_r;
static SDL_Rect help_rect;
static SDL_Rect self_r, foe_r;
static SDL_Rect belongings_r;
static SDL_Rect game_choices_r;

static int font_height;

// TODO introduce ennemies the Broforce way

void
render_projectile(bool from_enemy, bool *pTir)
/**
 * Render a projectile from one ship to another
 * if pType is true, the enemy is shooting
 * else it's from the player
 */
{
    SDL_Texture *tex_m_e = IMG_LoadTexture(renderer, "../assets/images/enemy_missile.png");
    SDL_Texture *tex_m_a = IMG_LoadTexture(renderer, "../assets/images/ally_missile.png");
    static SDL_Rect pos_m_e = { 800, 300, 0, 0 };
    static SDL_Rect pos_m_a = { 100, 600, 0, 0 };
    int x_limite_e = 100;
    int x_limite_a = 800;

    if(from_enemy && *pTir)
    {
        ///////   enemy   //////

        // draw enemy's missile
        SDL_QueryTexture(tex_m_e, NULL, NULL, &pos_m_e.w, &pos_m_e.h);
        SDL_RenderCopy(renderer, tex_m_e, NULL, &pos_m_e);
        // update missil
        if(pos_m_e.x > x_limite_e)
        {
            --pos_m_e.x;
        }
        else
        {
            pos_m_e.x = 800;
            *pTir = !(*pTir);
        }
    }
    else if(!from_enemy && *pTir)
    {
        ///////   ally    ///////
        SDL_QueryTexture(tex_m_a, NULL, NULL, &pos_m_a.w, &pos_m_a.h);
        SDL_RenderCopy(renderer, tex_m_a, NULL, &pos_m_a);
        // update missil
        if(pos_m_a.x < x_limite_a)
        {
            ++pos_m_a.x;
        }
        else
        {
            pos_m_a.x = 800;
            *pTir = !(*pTir);
        }
    }

    SDL_DestroyTexture(tex_m_e);
    SDL_DestroyTexture(tex_m_a);
}

void
load_interface_components(void)
/**
 * Load images with multiple uses in memory.
 */
{
    static bool loaded = false;
    if (loaded) return;

    bg_texture = load_texture(BACKGROUND_IMAGE);
    bg_overlay = load_texture("../assets/images/1px_overlay.png");
    continue_texture = texture_from_text(font, 1, continue_msg_rect, "Appuyez sur une touche pour continuer...", white, ALIGN_RIGHT);
    alien_pointer = load_texture("../assets/images/alien1.png");

    red_dot_texture = load_texture("../assets/images/red_dot.png");
    blue_dot_texture = load_texture("../assets/images/blue_dot.png");
    gray_dot_texture = load_texture("../assets/images/gray_dot.png");

    health_bar_bg_img = load_image("../assets/images/health_gray.png", 0);
    health_bar_img = load_image("../assets/images/health.png", 0);
    shield_bar_bg_img = load_image("../assets/images/shield_gray.png", 0);
    shield_bar_img = load_image("../assets/images/shield.png", 0);
    preload_first_frame(health_bar_bg_img);
    preload_first_frame(shield_bar_bg_img);

    self_texture = foe_texture = NULL;

    font_height = TTF_FontHeight(font);

    init_colors();
    init_rectangles();

    loaded = true;
}

void
free_interface_components(void)
/**
 * Destroy static textures of this file.
 * FIXME check if all textures are present here
 */
{
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(bg_overlay);
    SDL_DestroyTexture(continue_texture);
    SDL_DestroyTexture(alien_pointer);

    free_image(&health_bar_bg_img);
    free_image(&health_bar_img);
    free_image(&shield_bar_bg_img);
    free_image(&shield_bar_img);

    SDL_DestroyTexture(map_texture);

    SDL_DestroyTexture(red_dot_texture);
    SDL_DestroyTexture(blue_dot_texture);
    SDL_DestroyTexture(gray_dot_texture);

    SDL_DestroyTexture(choices_texture);
    SDL_DestroyTexture(combat_box_texture);
    SDL_DestroyTexture(help_texture);
    SDL_DestroyTexture(belongings_texture);

    SDL_DestroyTexture(self_texture);
    SDL_DestroyTexture(foe_texture);
}

void
init_colors(void)
/**
 * Create colors for text rendering.
 */
{
    static bool initiated = false;
    if (initiated) return;

    white = (SDL_Color){ 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE };
    gray = (SDL_Color){ 0x20, 0x20, 0x20, SDL_ALPHA_OPAQUE };

    initiated = true;
}

void
init_rectangles(void)
/**
 * Set values for SDL_Rects with multiple uses.
 */
{
    static bool initiated = false;
    if (initiated) return;

    // FIXME inner_overlay_rect was formerly known as base_overlay_rect
    inner_overlay_rect = (SDL_Rect){ WINDOW_WIDTH / 8, WINDOW_HEIGHT / 4, 3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 2 };
    continue_msg_rect = rect_from_texture(continue_texture, 5 * WINDOW_WIDTH / 6, 3 * WINDOW_HEIGHT / 4);

    SDL_QueryTexture(alien_pointer, NULL, NULL, &alien_cursor_r.w, &alien_cursor_r.h);

    SDL_QueryTexture(red_dot_texture, NULL, NULL, &icon_rect.w, &icon_rect.h);

    self_r = (SDL_Rect){ .x = WINDOW_WIDTH / 20, .y = 4 * WINDOW_HEIGHT / 7 };

    foe_r = (SDL_Rect){ .x = 19 * WINDOW_WIDTH / 20, .y = 4 * WINDOW_HEIGHT / 7 };

    belongings_r = (SDL_Rect){ .x = 60, .y = 60 };
    game_choices_r = (SDL_Rect){ WINDOW_WIDTH / 20, 3 * WINDOW_HEIGHT / 4, 1, 1 };

    initiated = true;
}

void
display_menu(void)
{
    // FIXME
}

void
display_map(map_matrix map, unsigned map_length, unsigned short height_index[], unsigned current_col, unsigned choice_node)
/**
 * Render the map and display it on an overlay.
 */
{
    static map_matrix prev_map;
    static unsigned short prev_col, prev_node;

    if (map_texture && map == prev_map && current_col == prev_col && choice_node == prev_node)
    {
        SDL_RenderCopy(renderer, map_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        return;
    }

    if (map_texture)
        SDL_DestroyTexture(map_texture);
    map_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetTextureBlendMode(map_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, map_texture);

    render_overlay_bg(NULL, 0);

    // Define the distance between two dots on map
    unsigned step_x = inner_overlay_rect.w / (map_length + 1);
    unsigned step_y;

    icon_rect.x = inner_overlay_rect.x - icon_rect.w / 2;

    // Render all columns
    for (unsigned short i = 0; i < map_length; i++)
    {
        // Determinate x position of this dot
        icon_rect.x += step_x;
        icon_rect.y = inner_overlay_rect.y - icon_rect.h / 2;

        step_y = inner_overlay_rect.h / (height_index[i] + 1);

        // Render all nodes
        for (unsigned short j = 0; j < height_index[i]; j++)
        {
            // Determinate y position
            icon_rect.y += step_y;

            // Choose icon texture depending on map node's nature
            if (!map[i] || !map[i][j])
                dot_texture = gray_dot_texture;
            else if (map[i][j]->is_shop)
                dot_texture = blue_dot_texture;
            else if (i == map_length - 1)
                dot_texture = red_dot_texture; // TODO prepare special dot for the boss
            else
                dot_texture = red_dot_texture;

            SDL_RenderCopy(renderer, dot_texture, NULL, &icon_rect);

            // Render cursor if necessary
            if (i == current_col && j == choice_node)
            {
                alien_pointer_map_rect = rect_from_texture(alien_pointer, icon_rect.x, icon_rect.y);
                alien_pointer_map_rect.x -= alien_pointer_map_rect.w + 5;
                alien_pointer_map_rect.y += (TTF_FontHeight(font) - alien_pointer_map_rect.h) / 2;
                SDL_RenderCopy(renderer, alien_pointer, NULL, &alien_pointer_map_rect);
            }
        }
    }

    SDL_SetRenderTarget(renderer, NULL);

    SDL_RenderCopy(renderer, map_texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    prev_map = map;
    prev_col = current_col;
    prev_node = choice_node;
}

void
display_fake_loading(unsigned miliseconds)
/**
 * Display a fake loading screen during a given time in miliseconds.
 */
{
    SDL_Color white = { 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE };
    SDL_Point pts[4][2];

    unsigned int endtime = SDL_GetTicks() + miliseconds;

    // Prepare shuttle symbol
    SDL_Texture *shuttle = load_texture("../assets/images/big_shuttle_white.png");
    SDL_Rect shuttle_rect = rect_from_texture(shuttle, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    shuttle_rect.x -= shuttle_rect.w / 2;
    shuttle_rect.y -= shuttle_rect.h / 2;

    // Prepare "Loading..." message
    SDL_Texture *load_msg = create_txt(font, "Loading...", white);
    SDL_Rect load_rect = rect_from_texture(load_msg, WINDOW_WIDTH / 2, 4 * WINDOW_HEIGHT / 5);
    load_rect.x -= load_rect.w / 2;
    load_rect.y -= load_rect.h / 2;

    // Prepare lines under shuttle symbol
    for (int i = 0; i < 4; i++)
    {
        int lx = WINDOW_WIDTH / 2 - (-3 + 2 * i) * shuttle_rect.w / 8;
        int ly1 = shuttle_rect.y + shuttle_rect.h + WINDOW_HEIGHT / 70;
        if (i == 1 || i == 2) ly1 += 20;
        int ly2 = ly1 + WINDOW_HEIGHT / 14;

        pts[i][0] = (SDL_Point){ lx, ly1 };
        pts[i][1] = (SDL_Point){ lx, ly2 };
    }

    int i = 0;
    while (SDL_GetTicks() < endtime)
    {
        // Show green background
        SDL_SetRenderDrawColor(renderer, 0x0A, 0x35, 0x36, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Show shuttle and loading message
        SDL_RenderCopy(renderer, shuttle, NULL, &shuttle_rect);
        SDL_RenderCopy(renderer, load_msg, NULL, &load_rect);

        // Show all lines except one
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
        for (int j = 0; j < 4; j++)
            if (j != i)
                SDL_RenderDrawLine(renderer, pts[j][0].x, pts[j][0].y, pts[j][1].x, pts[j][1].y);

        i = (i + 1) % 4;

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    SDL_DestroyTexture(shuttle);
    SDL_DestroyTexture(load_msg);

    SDL_SetRenderDrawColor(renderer, 0x06, 0x00, 0x0B, 0xFF);
    SDL_RenderClear(renderer);
}

void
display_dialog(unsigned counter)
/**
 * Display immersive text.
 */
{
    static unsigned prev_c;

    if (!dialog_texture || prev_c != counter)
    {
        dialog_texture = texture_from_text(font, 10, inner_overlay_rect, dialogs[counter], white, ALIGN_LEFT);
        prev_c = counter;
    }

    render_overlay_bg(NULL, 0);

    SDL_RenderCopy(renderer, dialog_texture, NULL, NULL);
    SDL_RenderCopy(renderer, continue_texture, NULL, &continue_msg_rect);

    SDL_RenderPresent(renderer);
}

void
display_quit_dialog(void)
/**
 * Display text asking user if he wants to quit the game.
 */
{
    SDL_Texture *confirm_quit_texture = texture_from_text(font, 1, inner_overlay_rect, "Voulez-vous vraiment quitter ?", white, ALIGN_LEFT);
    SDL_Texture *quit_choice_texture = texture_from_text(font, 1, continue_msg_rect, "(O)ui / (N)on", white, ALIGN_RIGHT);

    render_overlay_bg(NULL, 0);
    SDL_RenderCopy(renderer, confirm_quit_texture, NULL, NULL);
    SDL_RenderCopy(renderer, quit_choice_texture, NULL, NULL);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(confirm_quit_texture);
    SDL_DestroyTexture(quit_choice_texture);
}

void
render_self(ship *s, int health, int shield)
/**
 * Render the ship representing the player.
 */
{
    render_image_align(s->img, self_r.x, self_r.y, ALIGN_BOTTOM, ALIGN_LEFT);
    render_bars(s, &self_r, health, shield, false);
}

void
render_foe(ship *s, int health, int shield)
/**
 * Render the ship representing the ennemy.
 */
{
    static SDL_Texture *name_tex;
    static ship *prev_s;
    static SDL_Rect name_r;

    if (!name_tex || prev_s != s)
    {
        name_tex = create_txt(font, s->name, white);
        name_r = rect_from_texture(name_tex, foe_r.x - s->img->width - 24, foe_r.y - s->img->height);
        prev_s = s;
    }

    SDL_RenderCopy(renderer, name_tex, NULL, &name_r);
    render_image_align(s->img, foe_r.x, foe_r.y, ALIGN_BOTTOM, ALIGN_RIGHT);
    render_bars(s, &foe_r, health, shield, true);
}

void
announce_foe(ship *s)
{
    static SDL_Texture *behold, *name;
    static SDL_Rect behold_r, name_r;
    static int i;
    static ship *prev_s;

    if (!behold)
    {
        behold = create_txt(font, "BEHOLD", white);
        SDL_QueryTexture(behold, NULL, NULL, &behold_r.w, &behold_r.h);
        behold_r.x = WINDOW_WIDTH / 2 - behold_r.w;
        behold_r.y = WINDOW_WIDTH / 3 - behold_r.h;
    }

    if (prev_s != s)
    {
        SDL_QueryTexture(name, NULL, NULL, &name_r.w, &name_r.h);
        name_r.x = WINDOW_WIDTH / 2 - name_r.w;
        name_r.y = behold_r.y + behold_r.h + 8;
        i = 0;
        prev_s = s;
    }

    // FIXME cycle colors
    name = create_txt(font, s->name, white);
}

void
render_bars(ship *s, SDL_Rect *ship_r, int health, int shield, bool reversed)
/**
 * Render health and shield bars.
 * If true, the `reversed' parameter will display the bars for the foe rather than the player.
 */
{
    static SDL_Rect health_clip, shield_clip;

    if (health_clip.h == 0)
    {
        health_clip.h = health_bar_bg_img->height;
        shield_clip.h = shield_bar_bg_img->height;

#ifdef DEBUG
        s->health -= 10;
        s->shield -= 10;
#endif
    }

    int health_x, health_y, shield_x, shield_y;

    // Define bars positions
    health_x = ship_r->x;
    health_y = ship_r->y + ship_r->h + 10;

    shield_x = ship_r->x;
    shield_y = health_y + health_bar_bg_img->height + 2;

    // Define clipping
    health_clip.w = s->health * health_bar_bg_img->width / health;
    shield_clip.w = s->shield * shield_bar_bg_img->width / shield;
    if (reversed)
    {
        health_clip.x = health_bar_bg_img->width - health_clip.w;
        shield_clip.x = shield_bar_bg_img->width - shield_clip.w;
    }
    else
    {
        health_clip.x = shield_clip.x = 0;
    }

    x_align x_al = reversed ? ALIGN_RIGHT : ALIGN_LEFT;

    // Render bars background
    render_image_align(health_bar_bg_img, health_x, health_y, ALIGN_TOP, x_al);
    render_image_align(shield_bar_bg_img, shield_x, shield_y, ALIGN_TOP, x_al);

    // Render bars foreground
    render_image_scale_clip_align(health_bar_img, health_x, health_y, 1, 1, 0, &health_clip, ALIGN_TOP, x_al);
    render_image_scale_clip_align(shield_bar_img, shield_x, shield_y, 1, 1, 0, &shield_clip, ALIGN_TOP, x_al);
}

void
render_belongings(ship *s)
{
    // TODO move the rect to render in in the parameters to be able to render foe's?
    struct belongings *b = &s->belongings;
    static struct belongings prev_b;

    if (b->plasma != prev_b.plasma || b->scraps != prev_b.scraps || b->money != prev_b.money)
    {
        char strrepr[128];
        snprintf(strrepr, 128, "Plasma: %d\nScraps: %d\nMoney: %d", b->plasma, b->scraps, b->money);

        if (belongings_texture)
            SDL_DestroyTexture(belongings_texture);
        belongings_texture = texture_from_text(font, 10, belongings_r, strrepr, white, ALIGN_LEFT);

        prev_b.plasma = b->plasma;
        prev_b.scraps = b->scraps;
        prev_b.money = b->money;
    }

    SDL_RenderCopy(renderer, belongings_texture, NULL, NULL);
}

void
render_choices(short nb_choices, char **choices_text, int *current_choice, int mask, int line_spacing, int overlay_padding)
/**
 * Render a set of choices (expressed by the strings in `choices_text[]') with a cursor.
 * The position of the choices on the screen is given through the `choices_r' structure.
 * Forbidden options can be expressed bit-wise with the `mask' parameter.
 * An optionnal overlay can be added if `overlay_padding' is greater or equal to zero.
 */
{
    static short prev_mask, prev_choice;
    static char **prev_text;

    static SDL_Rect bg_r, cursor_r;

    while (!((mask >> *current_choice) & 1))
    {
        *current_choice = (*current_choice + 1) % nb_choices;
    }

    // (Re)evaluate cursor position if necessary
    if (!cursor_r.w || prev_choice != *current_choice)
    {
        // Evaluate cursor position
        if (!cursor_r.w)
            cursor_r = (SDL_Rect){ .w = alien_cursor_r.w, .h = alien_cursor_r.h };
        cursor_r.x = game_choices_r.x - cursor_r.w - 8;
        cursor_r.y = game_choices_r.y + (font_height + line_spacing) * *current_choice + (font_height - cursor_r.h) / 2;

        // Allow parameters comparison
        prev_choice = *current_choice;
    }

    // Reload the texture if a parameter changed
    if (mask != prev_mask || choices_text != prev_text)
    {
        SDL_Texture *t;
        SDL_Color color;
        SDL_Rect r;

        r = bg_r = (SDL_Rect){ .x = game_choices_r.x, .y = game_choices_r.y };

        // Create new texture to render on
        if (choices_texture)
            SDL_DestroyTexture(choices_texture);
        choices_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
        SDL_SetTextureBlendMode(choices_texture, SDL_BLENDMODE_BLEND);
        SDL_SetRenderTarget(renderer, choices_texture);

        // Render choices on new texture
        for (int i = 0; i < nb_choices; i++)
        {
            // Write in gray if the mask says so
            color = ((mask >> i) & 1) ? white : gray;
            if ((mask >> i) & 1)
            {
                color = white;
            }
            else
            {
                color = gray;
                current_choice += 1;
            }

            t = create_txt(font, choices_text[i], color);

            r = rect_from_texture(t, r.x, r.y);
            SDL_RenderCopy(renderer, t, NULL, &r);

            // Memorize the highest width among the lines
            if (r.w > bg_r.w)
                bg_r.w = r.w;

            // Move rendering rectangle downward for next iteration
            if (i < nb_choices - 1)
                r.y += r.h + line_spacing;
            bg_r.h += r.h + (i > 0 ? line_spacing : 0);

            SDL_DestroyTexture(t);
        }

        // Count cursor in overlay size
        if (prev_text != choices_text)
        {
            bg_r.x = cursor_r.x;
            bg_r.w += cursor_r.w + 8;
        }

        // Allow parameters comparision
        prev_mask = mask;
        prev_text = choices_text;
    }

    // Done rendering intermediary texture
    SDL_SetRenderTarget(renderer, NULL);

    // Render & display
    if (overlay_padding >= 0)
        render_overlay_bg(&bg_r, overlay_padding);
    SDL_RenderCopy(renderer, choices_texture, NULL, NULL);
    SDL_RenderCopy(renderer, alien_pointer, NULL, &cursor_r);
}

void
render_combat_box(enum combat_choice *choice, ship *self, unsigned current_col, unsigned map_length)
/**
 * Render dialog to interact with shops
 */
{
    static short line_spacing = 8;
    int mask = 0;

    short prices[NB_CHOICES_COMBAT];
    prices[COMBAT_ATTACK] = RULE_COMBAT_ATTACK_COST;
    prices[COMBAT_REPAIR] = RULE_COMBAT_REPAIR_COST;
    prices[COMBAT_FLEE] = RULE_COMBAT_FLEE_COST;

    const size_t max_size = 32;
    static char *choices_text[NB_CHOICES_SHOP];

    // Constitute mask and perform memory allocation for choices strings
    for (int i = 0; i < NB_CHOICES_SHOP; i++)
    {
        choices_text[i] = (char *)malloc(max_size * sizeof(char));

        bool can_repair = i == COMBAT_REPAIR && self->belongings.scraps >= RULE_COMBAT_REPAIR_COST;
        bool has_enough_plasma = self->belongings.plasma >= prices[i];
        bool can_flee = i == COMBAT_FLEE && current_col != map_length - 1 && has_enough_plasma;
        bool can_attack = i == COMBAT_ATTACK && has_enough_plasma;

        if (can_flee || can_repair || can_attack)
            mask |= 1 << i;
    }

    // Fill strings with actual values
    snprintf(choices_text[COMBAT_ATTACK], max_size, "Attaquer (%d plasma)", prices[COMBAT_ATTACK]);
    snprintf(choices_text[COMBAT_REPAIR], max_size, "Se reparer (%d scraps)", prices[COMBAT_REPAIR]);
    snprintf(choices_text[COMBAT_FLEE], max_size, "Fuir le combat (%d plasma)", prices[COMBAT_FLEE]);

    render_choices(NB_CHOICES_COMBAT, choices_text, (int *)choice, mask, line_spacing, 20);

    for (int i = 0; i < NB_CHOICES_COMBAT; i++)
    {
        free(choices_text[i]);
    }
}

void
render_shop_box(enum shop_choice *choice, ship *self, ship *shop)
/**
 * Render dialog to interact with shops
 */
{
    static short line_spacing = 8;
    short mask = 0;

    short prices[NB_CHOICES_SHOP];
    prices[SHOP_HEALTH] = RULE_SHOP_HEALTH_COST;
    prices[SHOP_SCRAPS] = RULE_SHOP_SCRAPS_COST;
    prices[SHOP_LEAVE] = RULE_SHOP_LEAVE_COST;

    const size_t max_size = 32;
    static char *choices_text[NB_CHOICES_SHOP];

    // Constitute mask and perform memory allocation for choices strings
    for (int i = 0; i < NB_CHOICES_SHOP; i++)
    {
        choices_text[i] = (char *)malloc(max_size * sizeof(char));

        if (i == SHOP_LEAVE || (self->belongings.money >= prices[i] && shop->belongings.all[i] > 0))
            mask |= 1 << i;
    }

    // Fill strings with actual values
    snprintf(choices_text[SHOP_HEALTH], max_size, "Se guerir ($%d)", prices[SHOP_HEALTH]);
    snprintf(choices_text[SHOP_SCRAPS], max_size, "Acheter des scraps ($%d)", prices[SHOP_SCRAPS]);
    snprintf(choices_text[SHOP_LEAVE], max_size, "Sortir du shop");

    render_choices(NB_CHOICES_SHOP, choices_text, (int *)choice, mask, line_spacing, 20);

    for (int i = 0; i < NB_CHOICES_SHOP; i++)
    {
        free(choices_text[i]);
    }
}

void
render_help_box(void)
/**
 * Render box to display help during game.
 */
{
    if (!help_texture)
    {
        help_texture = texture_from_text(font, 5, help_rect, help_txt, white, ALIGN_LEFT);
        help_rect = rect_from_texture(help_texture, WINDOW_WIDTH - 224, WINDOW_HEIGHT - 164);
    }


    render_overlay_bg(&help_rect, 10);
    SDL_RenderCopy(renderer, help_texture, NULL, &help_rect);
}

void
render_overlay_bg(SDL_Rect *rect, short padding)
/**
 * Render a semi-transparent background for dialogs/map readability.
 */
{
    if (rect)
    {
        SDL_Rect r = *rect;

        if (padding)
        {
            r.x -= padding;
            r.y -= padding;
            r.w += 2 * padding;
            r.h += 2 * padding;
        }

        SDL_RenderCopy(renderer, bg_overlay, NULL, &r);
    }
    else
    {
        SDL_RenderCopy(renderer, bg_overlay, NULL, NULL);
    }
}

void
render_background(void)
/**
 * Render background image.
 */
{
    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
}
