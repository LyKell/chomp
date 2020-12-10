/* Auteurs : Kevin SAVANE et Tom REDON
 * Creation : 05-02-2019
 * Modification : 14-02-2019 */

#include <MLV/MLV_all.h>
#include "fonction.h"
#include "graphique.h"



/*
Cette fonction est la fonction principale du programme.
Elle permet d'initialiser les variables nécessaires au jeu de base et aux améliorations.
Elle renvoie un entier (1 si tout s'est bien passé, 0 sinon).
*/
int main(void){
	Tablette tab;
	Position pos;
	Coup coup;
	char* nom_J1 = NULL, *nom_J2 = NULL;
	int continuer, vainqueur;
	int compteur_manche = 0, nb_victoire_J1 = 0, nb_victoire_J2 = 0, nb_manche = 0, manche_J1 = 0, manche_J2 = 0;
	int* score;
	char reponse_chargement;



	printf("Voulez-vous charger une partie pour la première manche ? (O pour Oui, N pour Non) : ");
	scanf(" %c", &reponse_chargement);



	MLV_create_window( "Chomp", "Chomp", TAILLE_CARRE*(N+4), TAILLE_CARRE*M);

	nom_J1 = initialiser_jeu(&manche_J1);
	nom_J2 = initialiser_jeu(&manche_J2);

	nb_manche = nombre_manche(manche_J1, manche_J2);

	score = allouer_tableau(nb_manche);


	/* Boucle principale */
	do {
		tab = creer_tablette();
		pos.tablette = tab;
		pos.joueur = J1;
		pos.nb_coups = 0;
		if (reponse_chargement == 'O' && compteur_manche == 0){
			printf("Chargement . . .\n");
			charger_manche(&pos);
		}

		do {
			afficher_position(&pos, nom_J1, nom_J2, compteur_manche, nb_manche);
			coup = lire_coup(&pos);
			jouer_coup(&pos, &coup);
			continuer = est_jeu_termine(&pos, &(pos).joueur, score, &nb_victoire_J1, &nb_victoire_J2, compteur_manche, nb_manche, nom_J1, nom_J2);
		} while(continuer == 0);

		compteur_manche++;
	} while (compteur_manche != nb_manche);


	/* Affichage du vainqueur */
	if (nb_victoire_J1 > nb_victoire_J2) {
		vainqueur = 1;
	} else if (nb_victoire_J2 > nb_victoire_J1) {
		vainqueur = 2;
	} else {
		vainqueur = 0;
	}

	afficher_vainqueur(vainqueur, nom_J1, nom_J2);

	MLV_free_window();

	return 1;
}
