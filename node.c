//
// Created by renau on 24/11/2024.
//

#include "node.h"
#include <stdlib.h>


t_node *createNode(int value, int nbsons)
{
    t_node *new_node; // Créer un nouveau nœud
    new_node = (t_node *) malloc(sizeof(t_node)); // Allouer de la mémoire pour le nœud
    new_node->value = value; // Initialiser la valeur du nœud
    new_node->nbSons = nbsons; // Initialiser le nombre de fils
    new_node->sons = (t_node **) malloc(nbsons * sizeof(t_node *)); // Allouer de la mémoire pour les fils
    for (int i = 0; i < nbsons; i++) { // Initialiser les fils à NULL
        new_node->sons[i] = NULL;
    }
    return new_node;
}

