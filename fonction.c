/* Auteurs : Kevin SAVANE et Tom REDON
 * Creation : 05-02-2019
 * Modification : 14-02-2019 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <MLV/MLV_all.h>
#include "fonction.h"
#include "graphique.h"


/*
Amélioration #2 - gestion de la sauvegarde
*/

/*
Fonction permettant de sauvegarder l'état d'une manche dans un fichier.
Elle prend en paramètre la structure Position et retourne un entier pour
savoir si tout s'est bien passé.
*/
int sauvegarder_manche(Position pos){
	int i;
	FILE *fichier = fopen("sauvegarde.txt","w");

	fprintf(fichier, "%d %d\n", N, M);
	fprintf(fichier, "%d\n", pos.joueur);
	for (i = 0; i < pos.nb_coups; i++){
		fprintf(fichier, "%d %d\n", pos.coups_joues[i].x, pos.coups_joues[i].y);
	}

	fclose(fichier);
	return 0;
}

/*
Fonction permettant de charger l'état d'une manche dans un fichier.
Elle prend en paramètre la structure Position et retourne un entier pour
savoir si tout s'est bien passé.
*/
int charger_manche(Position *pos){
	int i, j, joueur;
	FILE *fichier = fopen("sauvegarde.txt","r");

	assert(pos != NULL);
	/*
	A modifier si l'on a la tablette dynamique.
	*/
	fscanf(fichier, "%d %d", &i, &j);

	fscanf(fichier, "%d", &joueur);
	if (joueur == 0){
		pos->joueur = J1;
	}
	else {
		pos->joueur = J2;
	}
	while (fscanf(fichier, "%d %d", &i, &j) != EOF){
		manger(&(pos)->tablette, i, j);
	}
	fclose(fichier);
	return 0;
}


/*
Cette fonction permet d'initialiser une tablette de chocolat complète.
Elle ne prend pas de paramètres.
Elle retourne cette tablette de chocolat initialisée.
*/
Tablette creer_tablette() {
	Tablette tablette;
	int i, j;
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			tablette.tableau[i][j] = 1;
		}
	}
	return tablette;
}


/*
Cette fonction permet de supprimer les carrés de chocolat mangés par
le joueur lorsqu'un coup est joué.
Elle prend en paramètre une tablette, ainsi que deux entiers x et y.
Elle ne retourne rien.
*/
void manger(Tablette *t, int x, int y) {
	int i, j;

	assert(t != NULL);
	assert(x >= 0);
	assert(y >= 0 && y < M);

	for (i = x; i < N; i++) {
		for (j = y; j < M; j++) {
			(*t).tableau[i][j] = 0;
		}
	}
}



/*
Cette fonction permet de vérifier qu'un coup est légal
ou que l'on clique sur le bouton de sauvegarde.
Elle prend en paramètre la structure Position, ainsi que le coup joué.
Elle retourne un entier (1 si le coup est légal, 0 sinon).
*/
int est_legal(Position *pos, Coup *coup) {
	if (pos->tablette.tableau[coup->x][coup->y] != 0
		&& (coup->x >= 0 && coup->x < N && coup->y >= 0 && coup->y < M)) {
		return 1;
	}

	if ((coup->x >= (N+1) && coup->x <= (N+3))
		&& (coup->y >= (M-2) && coup->y <= (M-1))){
		return 2;
	}
	return 0;
}



/*
Cette fonction permet d'effectuer un certain affichage dans le terminal
si le jeu est terminé.
Elle prend en paramètre la structure Position, le joueur qui a gagné,
ainsi que le nombre de manches gagnées par le joueur 1 et celui pour
le joueur 2.
Elle retourne un entier (1 si la partie est terminée, 0 sinon).
*/
int est_jeu_termine(Position *pos, Joueur *joueur_gagnant, int* score, int *nb_victoire_J1, int *nb_victoire_J2, int compteur_manche, int nb_lignes, char* nom_J1, char* nom_J2) {
	if ((*pos).tablette.tableau[0][0] == 0) {
		printf("\n");
		if ((*pos).joueur == J1) {
			*joueur_gagnant = J1;
			/* Gestion de match */
			*nb_victoire_J1 = *nb_victoire_J1 + 1;
			affiche_gagnant_manche(nom_J1);
		} else {
			*joueur_gagnant = J2;
			/* Gestion de match */
			*nb_victoire_J2 = *nb_victoire_J2 + 1;
			affiche_gagnant_manche(nom_J2);
		}
		score[compteur_manche * nb_lignes + 0] = *nb_victoire_J1;
		score[compteur_manche * nb_lignes + 1] = *nb_victoire_J2;
		/* Gestion de match */
		printf("Joueur 1	%d - %d		Joueur 2\n", score[compteur_manche * nb_lignes + 0], score[compteur_manche * nb_lignes + 1]);

		return 1;
	}
	return 0;
}



/*
Cette fonction permet qu'un coup valide soit joué dans la partie.
Elle prend en paramètre la structure Position et
le coup qui vient d'être joué.
Elle ne retourne rien.
*/
void jouer_coup(Position *pos, Coup *coup) {
	int code_validation = est_legal(pos, coup);

	assert(coup->x >= 0);
	assert(coup->y >= 0 && coup->y < M);

	if (code_validation == 0){
		afficher_coup();
		return;
	}
	if (code_validation == 2){
		printf("Sauvegarde . . .\n");
		sauvegarder_manche(*pos);
		return;
	}
	manger(&(pos)->tablette, coup->x, coup->y);
	pos->coups_joues[pos->nb_coups].x = coup->x;
	pos->coups_joues[pos->nb_coups].y = coup->y;
	pos->nb_coups += 1;

	if (pos->joueur == J1){
		pos->joueur = J2;
	}
	else {
		pos->joueur = J1;
	}
}


/*
Fonction permettant d'allouer un tableau d'entier.
Prend en paramètre le nombre de manche.
Retourne l'adresse du tableau d'entier.
*/
int* allouer_tableau(int nb_manches) {
	int* tmp = (int *)malloc(nb_manches * 2 * sizeof(int));

	if (tmp == NULL) {
		return NULL;
	}

	return tmp;
}
