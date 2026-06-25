//
// Created by renau on 14/11/2024.
//

#include "draw.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int disponibilites[] = {MOOVE_10, MOOVE_20, MOOVE_30, MOOVE_B_10, MOOVE_LEFT, MOOVE_RIGHT, MOOVE_U_TURN};

void draw_moove(t_move draw[]) {
    srand(time(NULL));                              // Initialiser le générateur aléatoire
    t_move move;
    int random;
    for (int i=0;i<MAX_MOOVE; i++)
    {
        random = rand() % 7;                             // Choisir un nombre aléatoire entre 0 et 6
        move = random ;                                  // Choisir un mouvement aléatoire
        draw[i]=move;                                    // Ajouter le mouvement au tableau
        disponibilites[random]=disponibilites[random]-1; // Décrémenter le nombre de mouvements disponibles
    }
}

void draw_random_moove(t_move draw[], t_move result[])
{
    int indices[MAX_MOOVE]; // Tableau des indices disponibles
    for (int i=0;i<MAX_MOOVE;i++)
        { // Initialiser les indices (0 à 8)
        indices[i] = i ;
        }
    int n = MAX_MOOVE;                              // Nombre d'éléments dans le tableau
    srand(time(NULL));                         // Initialiser le générateur aléatoire
    for (int i=0;i<MAX_CHOICE;i++) {                // Choisir 5 mouvements aléatoires
        int indexAleatoire=rand() % n;              // Choisir un indice aléatoire
        result[i]=draw[indices[indexAleatoire]];    // Ajouter le mouvement correspondant au résultat
        indices[indexAleatoire]=indices[n-1];       // Remplacer l'indice sélectionné par le dernier
        n--;                                        // Réduire la taille des indices restants
    }
}

void display_tab(t_move tab[])
{
    for (int i = 0; i < MAX_MOOVE; i++)
    {
        printf("%d. %s\n", i + 1, getMoveAsString(tab[i]));
    }
}

void display_tab_random(t_move tab[])
{
    for (int i = 0; i < MAX_CHOICE; i++)
    {
        printf("%d. %s\n", i + 1, getMoveAsString(tab[i]));
    }
}

void choose_random_moove(t_move draw[])
{
    draw_moove(draw); // Générer les mouvements
    printf("____________________________________________________\n");
    printf("Voici les mouvements disponibles :\n");
    display_tab(draw); // Afficher les mouvements
    printf("Veuillez choisir %d mouvements (sans doublons) :\n", MAX_CHOICE);

    t_move selected[MAX_CHOICE];
    int selected_indices[MAX_CHOICE] = {0}; // Tableau pour suivre les indices déjà choisis
    int count = 0;

    while (count < MAX_CHOICE)
    {
        int choice;
        printf("Entrez le numero du mouvement %d : ", count + 1);

        if (scanf("%d", &choice) != 1 || choice < 1 || choice > MAX_MOOVE)
        {
            // Entrée invalide ou hors des limites
            printf("Erreur : Veuillez entrer un numero valide entre 1 et %d.\n", MAX_MOOVE);
            while (getchar() != '\n'); // Vider le buffer
            continue;
        }

        // Vérifier si le mouvement a déjà été choisi
        int already_selected = 0;
        for (int i = 0; i < count; i++)
        {
            if (selected_indices[i] == choice - 1)
            {
                already_selected = 1;
                break;
            }
        }

        if (already_selected)
        {
            printf("Erreur : Mouvement deja choisi, selectionner un autre\n");
        }
        else
        {
            // Ajouter le mouvement sélectionné
            selected[count] = draw[choice - 1];
            selected_indices[count] = choice - 1;
            count++;
        }
    }

    // Remplacer le tableau draw par les mouvements sélectionnés
    for (int i = 0; i < MAX_CHOICE; i++)
    {
        draw[i] = selected[i];
    }

    // Ajouter une terminaison visuelle pour afficher la liste propre
    printf("____________________________________________________\n");
    printf("Voici la liste des mouvements choisis :\n");
    for (int i = 0; i < MAX_CHOICE; i++)
    {
        printf("%d. %s\n", i + 1, getMoveAsString(draw[i]));
    }
}
