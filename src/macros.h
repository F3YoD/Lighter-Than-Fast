#ifndef _MACROS_H
#define _MACROS_H

#ifndef DEBUG
#define PRINT_DEBUG 0
#else
#define PRINT_DEBUG 1
#endif

#define var_name(variable) #variable

/* Allows to check if everything goes well with SDL */
#define check_SDL(variable)\
    {\
        if (variable == NULL)\
        {\
            fprintf(stderr, "[!] %s initialization failed (%s:%d): %s\n",\
                    #variable, __FILE__, __LINE__, SDL_GetError());     \
            TTF_Quit();                                                 \
            IMG_Quit();                                                 \
            SDL_Quit(); /* This frees memory for everything SDL-related */\
            exit(EXIT_FAILURE);\
        }\
        else if (PRINT_DEBUG)\
            printf("[+] %s initialization success\n", #variable);\
    }

#define check_IMG(variable)                                             \
    {                                                                   \
        if (variable == NULL)                                           \
        {                                                               \
            fprintf(stderr, "[!] %s initialization failed (%s:%d): %s\n",   \
                    #variable, __FILE__, __LINE__, IMG_GetError()); \
            TTF_Quit();                                                 \
            IMG_Quit();                                                 \
            SDL_Quit(); /* This frees memory for everything SDL-related */ \
            exit(EXIT_FAILURE);                                         \
        }                                                               \
        else if (PRINT_DEBUG)                                           \
            printf("[+] %s initialization success\n", #variable);           \
    }

#define check_TTF(variable)                                             \
    {                                                                   \
        if (variable == NULL)                                           \
        {                                                               \
            fprintf(stderr, "[!] %s initialization failed (%s:%d): %s\n",   \
                    #variable, __FILE__, __LINE__, TTF_GetError());     \
            TTF_Quit();                                                 \
            IMG_Quit();                                                 \
            SDL_Quit(); /* This frees memory for everything SDL-related */ \
            exit(EXIT_FAILURE);                                         \
        }                                                               \
        else if (PRINT_DEBUG)                                           \
            printf("[+] %s initialization success\n", #variable);           \
    }

#endif /* _MACROS_H */
