/* Auteurs : Kevin SAVANE et Tom REDON
 * Creation : 05-02-2019
 * Modification : 14-02-2019 */

#ifndef DEF_FONCTION
#define DEF_FONCTION

#include "Chomp.h"

int sauvegarder_manche(Position pos);
int charger_manche(Position *pos);
Tablette creer_tablette();
void manger(Tablette *t, int x, int y);
int est_legal(Position *pos, Coup *coup);
int est_jeu_termine(Position *pos, Joueur *joueur_gagnant, int* score, int *nb_victoire_J1, int *nb_victoire_J2, int compteur_manche, int nb_lignes, char* nom_J1, char* nom_J2);
void jouer_coup(Position *pos, Coup *coup);
int nombre_manche(int mancheJ1, int mancheJ2);
int* allouer_tableau(int nb_lignes);

#endif
