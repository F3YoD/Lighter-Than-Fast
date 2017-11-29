#ifndef _PROJ_TOOLS_
#define _PROJ_TOOLS_

#ifndef DEBUG
#define PRINT_DEBUG 0
#else
#define PRINT_DEBUG 1
#endif

/* Allows to check if everything goes well with SDL */
#define check_SDL(variable)\
    {\
        if (variable == NULL)\
        {\
            fprintf(stderr, "%s initialization failed: %s\n",\
                    #variable, SDL_GetError());\
            SDL_Quit(); /* This frees memory for everything SDL-related */\
            IMG_Quit();\
            exit(EXIT_FAILURE);\
        }\
        else if (PRINT_DEBUG)\
            printf("%s initialization success\n", #variable);\
    }

#endif
