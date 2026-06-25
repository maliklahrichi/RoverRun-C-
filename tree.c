//
// Created by Arshdeep SINGH on 22/11/2024.
//

#include "tree.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>


t_node *createTreeRecursive(t_map map, t_localisation rover, t_move selection[], int depth) {
    // Vérification des limites initiales de la position du rover
    if (rover.pos.x < 0 || rover.pos.x >= map.x_max || rover.pos.y < 0 || rover.pos.y >= map.y_max) {
        return NULL;
    }

    // Mise à jour des coûts de la carte
    calculateCosts(map);

    // Récupération de la valeur du coût actuel à la position du rover
    int cost = map.costs[rover.pos.y][rover.pos.x];
    if (cost > 10000 || depth == 0) {
        return NULL; // Condition d'arrêt : coût trop élevé ou profondeur atteinte
    }

    // Création du nœud courant avec la valeur du coût et le nombre de fils égal à la profondeur
    t_node *node = createNode(cost, depth);

    // Génération récursive des fils pour chaque mouvement
    for (int i = 0; i < depth; i++) {
        // Copie de la localisation actuelle pour éviter de modifier la position de départ
        t_localisation updatedRover = rover;

        // Mise à jour de la localisation avec le mouvement courant
        updateLocalisation(&updatedRover, selection[i]);

        // Vérification après la mise à jour de la validité de la nouvelle localisation
        if (isValidLocalisation(updatedRover.pos, map.x_max, map.y_max)) {
            // Appel récursif pour générer le sous-arbre
            node->sons[i] = createTreeRecursive(map, updatedRover, selection, depth - 1);
        } else {
            // Si la position est invalide, on n'ajoute pas de fils
            node->sons[i] = NULL;
        }
    }


    return node;
}





// Wrapper pour appeler la fonction récursive
t_node *createTree(t_map map, t_localisation rover, t_move selection[]) {
    return createTreeRecursive(map, rover, selection, 5); // Profondeur maximale de 5
}

#include <stdio.h>

// Fonction récursive pour afficher un arbre
void displayTreeRecursive(t_node *node, int depth) {
    if (node == NULL) {
        return;
    }

    // Indentation en fonction de la profondeur
    for (int i = 0; i < depth; i++) {
        printf("  "); // Ajoute deux espaces par niveau
    }

    // Afficher la valeur du nœud
    printf("|- Value: %d\n", node->value);

    // Afficher les fils récursivement
    for (int i = 0; i < node->nbSons; i++) {
        displayTreeRecursive(node->sons[i], depth + 1);
    }
}

// Wrapper pour afficher l'arbre depuis la racine
void displayTree(t_node *root) {
    if (root == NULL) {
        printf("L'arbre est vide.\n");
        return;
    }

    printf("Affichage de l'arbre :\n");
    displayTreeRecursive(root, 0); // Commence à la profondeur 0
}


#include <limits.h> // Pour INT_MAX

/**
 * @brief Fonction récursive pour trouver le coût minimal parmi les feuilles d'un arbre
 * @param node : le nœud courant
 * @return le coût minimal parmi les feuilles de l'arbre
 */
int findMinLeafCostRecursive(t_node *node) {
    if (node == NULL) {
        return INT_MAX; // Retourne un coût très élevé si le nœud est nul
    }

    // Vérifie si c'est une feuille (pas de fils)
    int isLeaf = 1;
    for (int i = 0; i < node->nbSons; i++) {
        if (node->sons[i] != NULL) {
            isLeaf = 0; // Pas une feuille si un fils existe
            break;
        }
    }

    // Si c'est une feuille, retourne son coût
    if (isLeaf) {
        return node->value;
    }

    // Sinon, trouve le coût minimal parmi tous les fils
    int minCost = INT_MAX;
    for (int i = 0; i < node->nbSons; i++) {
        int childCost = findMinLeafCostRecursive(node->sons[i]);
        if (childCost < minCost) {
            minCost = childCost;
        }
    }

    return minCost;
}

int findMinLeafCost(t_node *root) {
    if (root == NULL) {
        printf("Erreur : L'arbre est vide.\n");
        return -1; // Retourne -1 pour indiquer une erreur
    }

    int minCost = findMinLeafCostRecursive(root);
    if (minCost == INT_MAX) {
        printf("Erreur : Aucune feuille trouvée.\n");
        return -1; // Retourne -1 si aucune feuille n'a été trouvée
    }

    return minCost;
}

void findPathToMinLeaf(t_node *root, t_localisation rover, t_map map, t_position *path, int *pathSize) {
    if (!root) {
        *pathSize = 0; // Aucun chemin si l'arbre est vide
        return;
    }

    int targetCost = findMinLeafCost(root); // Trouver le coût minimal parmi les feuilles
    int index = 0;

    while (root) {
        // Ajouter les coordonnées actuelles au chemin
        path[index].x = rover.pos.x;
        path[index].y = rover.pos.y;
        index++;

        // Si c'est une feuille ou si la valeur cible est atteinte, arrêter
        if (root->nbSons == 0 || root->value == targetCost) {
            break;
        }

        // Rechercher le fils contenant le coût cible
        for (int i = 0; i < root->nbSons; i++) {
            if (root->sons[i] && findMinLeafCost(root->sons[i]) == targetCost) {
                // Mettre à jour la localisation du rover
                rover = move(rover, i); // Suppose que `i` correspond au mouvement réalisé
                root = root->sons[i];  // Passer au fils correspondant
                break;
            }
        }
    }

    // Marquer la fin du chemin
    *pathSize = index; // Stocker la taille du chemin
}



int moveTowardsBase(t_node *root, t_map map, t_localisation rover, t_position *path, int *pathSize) {
    if (!root) {
        *pathSize = 0; // Aucun chemin si l'arbre est vide
        return 1;
    }

    // Obtenir les coordonnées de la base
    t_position basePosition = getBaseStationPosition(map);
    printf("Base position: (%d, %d)\n", basePosition.x, basePosition.y);

    int index = 0;

    while (root) {
        // Ajouter la position actuelle du rover au chemin
        path[index].x = rover.pos.x;
        path[index].y = rover.pos.y;
        index++;

        // Afficher la position actuelle du rover


        // Vérifier si la position actuelle du rover est celle de la base
        if (rover.pos.x == basePosition.x && rover.pos.y == basePosition.y) {
            *pathSize = index; // Mettre à jour la taille du chemin
            return 0; // La base est atteinte
        }

        // Identifier le fils avec le coût minimal
        int minCost = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < root->nbSons; i++) {
            if (root->sons[i] && root->sons[i]->value < minCost) {
                minCost = root->sons[i]->value;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            break; // Aucun fils valide, arrêt de l'exploration
        }

        // Mettre à jour la localisation du rover
        t_localisation updatedRover = rover;
        updateLocalisation(&updatedRover, (t_move)minIndex);



        // Appliquer la mise à jour au rover
        rover = updatedRover;

        // Passer au nœud suivant
        root = root->sons[minIndex];
    }

    *pathSize = index; // Stocker la taille du chemin
    return 1; // La base n'a pas été atteinte
}
