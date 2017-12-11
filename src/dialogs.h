#ifndef _DIALOG_H
#define _DIALOG_H

char hello[] = "Vite !\n"
    "Votre equipage s'est fait enlever par la confederation !\n\n"
    "L'horrible Zblorx, aide par Slarx et Vlerx les tiennent\nprisonniers.\n"
    "Tuez les chasseurs sur votre chemin pour les liberer.";

char hello1[] = "Unite 731 !\n"
    "Nous avions bien cru que nous ne reussirions pas a vous reveiller !\n"
    "Dieu merci, vous semblez avoir reussi a accumuler de l'energie a proximite\n"
    "de razia-111.\n";
char hello2[] = "Trois jours sont passes, le temps presse pour votre equipage.\n"
    "Vous avez reussi a echapper aux mains de la confederation mais\n"
    "ce n'est malheureusement pas leur cas.";
char hello3[] = "Ne perdons pas une minute ! Les mecadrones semblent avoir repare\n"
    "les degats infliges a la coque pendant votre veille.\n\n"
    "";

char hello_wake[] = "Vous vous eveillez au soleil.\n"
    "Trois jours ? Il n'est pas dans votre habitude de rester en veille\nsi longtemps...\n"
    "Vous etes engourdi, quelque chose a l'air etrange.";
char hello_sensor[] = "Certains de vos capteurs semblent ne plus\netre en etat de marche. "
    "Ce sont pourtant des elements\nfacile a remplacer pour des techniciens comme les notres.\n";
char hello_scan[] = "Les techniciens !!\nPersonne ne semble etre a bord !\n"
    "Le commandant semble lui aussi avoir deserte... C'est impossible !";
char hello_cctv[] = "Les capteurs vous rememorent du chaos a bord il y a trois jours :\n"
    "La confederation avait finalement reussi a retrouver votre trace";

#define NB_DIALOGS 3
char *dialogs[] = { hello1, hello2, hello3 };

#endif /* _DIALOG_H */
