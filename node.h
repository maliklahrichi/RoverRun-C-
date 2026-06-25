//
// Created by renau on 24/11/2024.
//


typedef struct s_node {
    int value;
    int nbSons;
    struct s_node** sons;
} t_node;

t_node *createNode(int value, int nbsons);