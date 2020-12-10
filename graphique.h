/* Auteurs : Kevin SAVANE et Tom REDON
 * Creation : 05-02-2019
 * Modification : 14-02-2019 */

#ifndef DEF_GRAPHIQUE
#define DEF_GRAPHIQUE

#include "Chomp.h"

void afficher_position(Position *pos, char* nom_J1, char* nom_J2, int compteur_manche, int nb_manche);
Coup lire_coup(Position *pos);
void afficher_vainqueur(int vainqueur, char* nom_J1, char* nom_J2);
void afficher_coup();
char* initialiser_jeu(int* nb_manche_J);
int nombre_manche(int mancheJ1, int mancheJ2);
void afficher_manche(int compteur_manche, int nb_manche);
void affiche_gagnant_manche(char* nom_gagnant);
void afficher_bouton_sauvegarde();

#endif
