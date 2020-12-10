/* Auteurs : Kevin SAVANE et Tom REDON
 * Creation : 05-02-2019
 * Modification : 14-02-2019 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "graphique.h"

/*
Cette fonction permet d'afficher le plateau de jeu.
Elle prend en paramètre une structure Position qui contient la tablette
et le joueur dont c'est le tour.
Elle ne retourne rien.
*/
void afficher_position(Position *pos, char* nom_J1, char* nom_J2, int compteur_manche, int nb_manche) {
	int i, j;
	char message[61] = "Au tour de ";
	MLV_draw_filled_rectangle(0,0,N*TAILLE_CARRE, M*TAILLE_CARRE, MLV_COLOR_BLACK);
	MLV_draw_filled_rectangle(N*TAILLE_CARRE, 0, (N+4)*TAILLE_CARRE, M*TAILLE_CARRE, MLV_COLOR_DEEPSKYBLUE);
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			if (pos->tablette.tableau[i][j] == 1){
				MLV_draw_filled_rectangle(i*TAILLE_CARRE, j*TAILLE_CARRE, TAILLE_CARRE, TAILLE_CARRE, MLV_COLOR_GRAY91);
				MLV_draw_rectangle(i*TAILLE_CARRE, j*TAILLE_CARRE, TAILLE_CARRE, TAILLE_CARRE, MLV_COLOR_BLUE);
			}
			MLV_draw_filled_circle(TAILLE_CARRE/2, TAILLE_CARRE/2, 3, MLV_COLOR_BLUE);
		}
	}
	/* Affichage du joueur actuel */
	if ((*pos).joueur == J1) {
		MLV_draw_text_box(
			N * TAILLE_CARRE, TAILLE_CARRE,
			4 * TAILLE_CARRE, 2 * TAILLE_CARRE,
			strcat(message, nom_J1),
			TAILLE_INTERLIGNE,
			MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_YELLOW, MLV_COLOR_DEEPSKYBLUE,
			MLV_TEXT_CENTER,
			MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
		);
	} else {
		MLV_draw_text_box(
			N * TAILLE_CARRE, TAILLE_CARRE,
			4 * TAILLE_CARRE, 2 * TAILLE_CARRE,
			strcat(message, nom_J2),
			TAILLE_INTERLIGNE,
			MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_PURPLE, MLV_COLOR_DEEPSKYBLUE,
			MLV_TEXT_CENTER,
			MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
		);
	}
	afficher_bouton_sauvegarde();
	afficher_manche(compteur_manche, nb_manche);
	MLV_actualise_window();
}


/*
Cette fonction permet de récupérer les coordonnées pour un coup joué sur le plateau.
Elle prend en paramètre la structure position.
Elle retourne le coup lu.
*/
Coup lire_coup(Position *pos) {
	int x = -1, y = -1;
	Coup coup;

	do {
		MLV_wait_mouse(&x, &y);
	} while((x < 0 || x > TAILLE_CARRE*N) && (y < 0 || y > TAILLE_CARRE*M));
	x = (x/TAILLE_CARRE);
	y = (y/TAILLE_CARRE);

	coup.x = x;
	coup.y = y;
	return coup;
}


/*
Cette fonction permet d'afficher le vainqueur à la fin d'une partie.
Elle prend en paramètre un entier (qui symbolise le gagnant).
Elle ne retourne rien.
*/
void afficher_vainqueur(int vainqueur, char* nom_J1, char* nom_J2) {
	char message[72] = "Victoire de ";
	switch (vainqueur) {
		case 0:
			MLV_draw_text_box(
				N * TAILLE_CARRE, 3 * TAILLE_CARRE,
				4 * TAILLE_CARRE, TAILLE_CARRE,
				"Egalité !",
				TAILLE_INTERLIGNE,
				MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_BLACK, MLV_COLOR_DEEPSKYBLUE,
				MLV_TEXT_CENTER,
				MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
			);
			break;
		case 1:
			MLV_draw_text_box(
				N * TAILLE_CARRE, 3 * TAILLE_CARRE,
				4 * TAILLE_CARRE, TAILLE_CARRE,
				strcat(message, nom_J1),
				TAILLE_INTERLIGNE,
				MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_YELLOW, MLV_COLOR_DEEPSKYBLUE,
				MLV_TEXT_CENTER,
				MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
			);
			break;
		case 2:
			MLV_draw_text_box(
				N * TAILLE_CARRE, 3 * TAILLE_CARRE,
				4 * TAILLE_CARRE, TAILLE_CARRE,
				strcat(message, nom_J2),
				TAILLE_INTERLIGNE,
				MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_PURPLE, MLV_COLOR_DEEPSKYBLUE,
				MLV_TEXT_CENTER,
				MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
			);
			break;
	}
	MLV_actualise_window();
	MLV_wait_seconds(2);
}


/*
Fonction permettant d'afficher si le coup est impossible.
Ne prend pas de paramètre et ne retourne rien.
*/
void afficher_coup() {
	MLV_draw_text_box(
		N * TAILLE_CARRE, 3 * TAILLE_CARRE,
		4 * TAILLE_CARRE, TAILLE_CARRE,
		"Coup impossible !",
		TAILLE_INTERLIGNE,
		MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_RED, MLV_COLOR_DEEPSKYBLUE,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	MLV_actualise_window();
	MLV_wait_seconds(1);
}


/*
Fonction permettant d'initialiser la partie au niveau du nombre de manches.
Prend en paramètre un entier qui retournera le nombre de manches à jouer.
Retourne la chaine de caractere dans laquelle est inscrite le nom du joueur.
*/
char* initialiser_jeu(int* nb_manche_J) {
	char* nom_J, *manche;
	MLV_draw_filled_rectangle(0, 0, (N+4) * TAILLE_CARRE, M * TAILLE_CARRE, MLV_COLOR_BLACK);
	MLV_draw_filled_rectangle(0, 0, (N+4) * TAILLE_CARRE, M * TAILLE_CARRE, MLV_COLOR_DEEPSKYBLUE);
	MLV_draw_text_box(
		0, 0,
		(N + 4) * TAILLE_CARRE, TAILLE_CARRE,
		"Jeu du Chomp",
		TAILLE_INTERLIGNE,
		MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_BLUE, MLV_COLOR_DEEPSKYBLUE,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);

	MLV_wait_input_box(
		8 * TAILLE_CARRE, TAILLE_CARRE,
		4 * TAILLE_CARRE, 0.8 * TAILLE_CARRE,
		MLV_COLOR_BLACK, MLV_COLOR_BLUE4, MLV_COLOR_STEELBLUE1,
		"Votre nom : ",
		&nom_J
	);
	nom_J[strlen(nom_J)] = '\0';

	do {
		MLV_wait_input_box(
			8 * TAILLE_CARRE, TAILLE_CARRE,
			4 * TAILLE_CARRE, 0.8 * TAILLE_CARRE,
			MLV_COLOR_BLACK, MLV_COLOR_BLUE4, MLV_COLOR_STEELBLUE1,
			"Nombre de manches : ",
			&manche
		);
		*nb_manche_J = atoi(manche);
	} while (*nb_manche_J == 0);

	MLV_draw_text_box(
		8 * TAILLE_CARRE, TAILLE_CARRE,
		4 * TAILLE_CARRE, 0.8 * TAILLE_CARRE,
		"Joueur enregistré.",
		TAILLE_INTERLIGNE,
		MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_GREEN, MLV_COLOR_DEEPSKYBLUE,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	MLV_actualise_window();

	MLV_wait_seconds(1);

	return nom_J;
}


/*
Fonction permettant de calculer le nombre de manches.
Prend en paramètre le nombre de manches décidé par chaque joueur.
Retourne un entier pour savoir si tout s'est bien passé.
*/
int nombre_manche(int mancheJ1, int mancheJ2) {
	int nb_manche = (mancheJ1 + mancheJ2) / 2;
	char chaine_manche[2], message[100] = "Il y aura ";
	sprintf(chaine_manche, "%d", nb_manche);

	assert(mancheJ1 > 0);
	assert(mancheJ2 > 0);

	MLV_draw_text_box(
		8 * TAILLE_CARRE, TAILLE_CARRE,
		4 * TAILLE_CARRE, 0.8 * TAILLE_CARRE,
		strcat(strcat(message, chaine_manche), " manches."),
		TAILLE_INTERLIGNE,
		MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_RED, MLV_COLOR_DEEPSKYBLUE,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	MLV_actualise_window();
	MLV_wait_seconds(2);

	return nb_manche;
}


/*
Fonction permettant d'afficher la manche courante.
Prend en paramètre deux entiers, le compteur de manche et le nombre de manches.
Ne retourne rien.
*/
void afficher_manche(int compteur_manche, int nb_manche) {
	char message[100] = "Manche ", chaine_cpt_manche[2], chaine_nb_manche[2];
	sprintf(chaine_cpt_manche, "%d", compteur_manche+1);
	sprintf(chaine_nb_manche, "%d", nb_manche);

	MLV_draw_text_box(
		N * TAILLE_CARRE, 0,
		4 * TAILLE_CARRE, TAILLE_CARRE,
		strcat(strcat(strcat(message, chaine_cpt_manche), "/"), chaine_nb_manche),
		TAILLE_INTERLIGNE,
		MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_GREEN, MLV_COLOR_DEEPSKYBLUE,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	MLV_actualise_window();
}


/*
Fonction permettant d'afficher le gagnant de la manche.
Prend en paramètre le nom du gagnant (une chaine de caractere).
Ne retourne rien.
*/
void affiche_gagnant_manche(char* nom_gagnant) {
	char message[100];
	strcpy(message, nom_gagnant);
	MLV_draw_text_box(
		N * TAILLE_CARRE, 3 * TAILLE_CARRE,
		4 * TAILLE_CARRE, TAILLE_CARRE,
		strcat(message, " gagne !"),
		TAILLE_INTERLIGNE,
		MLV_COLOR_DEEPSKYBLUE, MLV_COLOR_RED, MLV_COLOR_DEEPSKYBLUE,
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	MLV_actualise_window();
	MLV_wait_seconds(1);
}


/*
Amelioration #2 - gestion de la sauvegarde
*/

/*
Cette fonction permet d'afficher le bouton de sauvegarde sur la fenêtre.
Elle ne prend pas de paramètre et ne retourne rien.
*/
void afficher_bouton_sauvegarde(){
	MLV_draw_filled_rectangle((N+1)*TAILLE_CARRE, TAILLE_CARRE*(M-2), TAILLE_CARRE*2, TAILLE_CARRE, MLV_COLOR_WHITE);
	MLV_draw_text((N+1.1) * TAILLE_CARRE, TAILLE_CARRE * (M-1.7), "SAUVEGARDE", MLV_COLOR_BLACK);
}
