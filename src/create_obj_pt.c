#include "../includes/create_obj_pt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int vertex_number;
float* vertex_coord;
float* normal_coord;

void createCoordinates(unsigned int* sz_pt) {
	// Vous devez fixer :
	// - le nombre de sommets (vertex_number)
	// - le tableau des coordonnees des sommets (vertex_coord)
	// - le tableau des coordonnees des normales (normal_coord)
	// Vous pouvez changer :
	// - la taille des points GL affichés à l'écran (sz_pt)

	*sz_pt = 5; // A CHANGER EVENTUELLEMENT
	vertex_number = 0; // A CHANGER
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
	normal_coord = (float*) calloc(sizeof(float),3*vertex_number);

	// CONSTRUIRE LES TABLEAUX
}
