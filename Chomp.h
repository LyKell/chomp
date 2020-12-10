/* Auteurs : Kevin SAVANE et Tom REDON
 * Creation : 05-02-2019
 * Modification : 14-02-2019 */
#ifndef DEF_CHOMP
#define DEF_CHOMP

/*
Définition des constantes
*/
#define N 16
#define M 8
#define TAILLE_CARRE 50
#define TAILLE_INTERLIGNE 9

/*
Definition des structures
*/
typedef struct {
	int tableau[N][M];
} Tablette;

typedef enum {
	J1,
	J2
} Joueur;

typedef struct {
	int x;
	int y;
} Coup;

typedef struct {
	Tablette tablette;
	Joueur joueur;
	int nb_coups;
	Coup coups_joues[N*M];
} Position;



#endif
