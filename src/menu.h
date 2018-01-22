#ifndef _MENU_H
#define _MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "shared.h"
#include "tools.h"
#include "macros.h"

enum menu_choice { CONTINUE_GAME, NEW_GAME, QUIT_GAME, NB_CHOICES_MENU };

enum menu_choice menu(bool);

#endif /* _MENU_H */
