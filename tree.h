//
// Created by Arshdeep SINGH on 22/11/2024.
//


#include "node.h"
#include "map.h"
#include "loc.h"
#include "moves.h"

t_node *createTreeRecursive(t_map map, t_localisation rover, t_move selection[], int depth);
t_node *createTree(t_map map, t_localisation rover, t_move selection[]);
void displayTreeRecursive(t_node *node, int depth);
void displayTree(t_node *root);

int findMinLeafCost(t_node *root);

int findMinLeafCostRecursive(t_node *node);

void findPathToMinLeaf(t_node *root, t_localisation rover, t_map map, t_position *path, int *pathSize);

int moveTowardsBase(t_node *root, t_map map, t_localisation rover, t_position *path, int *pathSize);

void findBaseWithRandomMoves(t_map map, t_localisation rover);