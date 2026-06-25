#include <stdio.h>
#include "tree.h"
#include "draw.h"


// Fonction pour afficher une carte
void show_map_info(t_map map) {
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Fonction pour afficher les coûts des cases
void show_map_costs(t_map map) {
    printf("Map costs:\n");
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
}



void welcome_message()
{
    printf("=======================================================================\n");
    printf("=                                                                     =\n");
    printf("=                           Rover Run                                 =\n");
    printf("=                                                                     =\n");
    printf("=======================================================================\n");
    printf("\n");
    printf("Appuyez sur une entrer pour continuer\n");
    printf("\n");
    getchar();
}

void wait_for_user() {
    printf("Appuyez sur une touche pour continuer...\n");
    getchar(); // Consomme le '\n' laissé par scanf
    getchar(); // Attend une nouvelle entrée de l'utilisateur
}


int main() {

    t_map map = createMapFromFile("..\\maps\\example1.map");
    t_localisation marc = loc_init(1, 1, EAST);

    printf("Marc est a la position : x=%d, y=%d, orientation=%d\n",marc.pos.x, marc.pos.y, marc.ori);

    t_position path[100]; // Taille maximale arbitraire pour les coordonnées
    int pathSize = 0; // Taille du chemin
    t_move tab[MAX_MOOVE]; // Tableau de mouvements
    t_move draw[MAX_CHOICE]; // Tableau de mouvements aléatoires
    draw_moove(draw); // Générer les mouvements
    draw_random_moove(draw, tab); // Générer les mouvements aléatoires
    t_node *tree = createTree(map, marc, draw); // Créer l'arbre

    welcome_message(); // Afficher le message de bienvenue

    int choice = 0;

    do {
        // Menu principal
        printf("\n");
        printf("------------------------------------\n");
        printf("               Menu                 \n");
        printf("------------------------------------\n");
        printf(" 1. Gestion des cartes\n");
        printf(" 2. Gestion des mouvements\n");
        printf(" 3. Arbres\n");
        printf(" 4. Jouer\n");
        printf(" 5. Quitter\n");
        printf("\n");

        // Lire le choix utilisateur
        printf("Entrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Sous-menu pour la gestion des cartes
                int map_choice = 0;
                printf("\n");
                printf("----------------\n");
                printf("-    CARTES    -\n");
                printf("----------------\n");
                printf("1. Charger la carte par defaut\n");
                printf("2. Charger une carte personnalisee (9x9)\n");
                printf("3. Afficher la carte\n");
                printf("4. Calculer les couts et les afficher\n");
                printf("5. Affichage graphique\n");
                printf("6. Retour\n");
                printf("\n");

                // Lire le choix pour la gestion des cartes
                printf("Entrez votre choix : ");
                scanf("%d", &map_choice);

                switch (map_choice) {
                    case 1:
                        map = createMapFromFile("..\\maps\\example1.map");
                        printf("Carte par defaut chargee avec succes.\n");
                        break;
                    case 2:
                        map = createMapFromFile("..\\maps\\custom9x9.map");
                        printf("Carte personnalisee (9x9) chargee avec succès.\n");
                        break;
                    case 3:
                        show_map_info(map); // Afficher les informations de la carte
                        break;
                    case 4:
                        calculateCosts(map); // Calculer les coûts
                        show_map_costs(map); // Afficher les coûts
                        break;
                    case 5:
                        displayMap(map); // Afficher la carte
                        break;
                    case 6:
                        printf("Retour au menu principal.\n");
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;
            }
            case 2:
                int mvt_choice = 0;
                printf("\n");
                printf("-----------------\n");
                printf("-   Mouvement   -\n");
                printf("-----------------\n");
                printf("1. Effectuer les mouvements aleatoires\n");
                printf("2. Retour\n");
                printf("\n");

                // Lire le choix pour la gestion des cartes
                printf("Entrez votre choix : ");
                scanf("%d", &mvt_choice);
                switch (mvt_choice)
                    {
                    case 1 :
                        printf("Voici les mouvements disponibles :\n");
                        display_tab(draw);
                        printf("Activer les mouvements aleatoires, y/n\n");
                        printf("1. oui\n");
                        printf("2. non\n");
                        int choix;
                        scanf("%d", &choix);
                        switch (choix) {
                            case 1 :
                                display_tab_random(tab);
                                break;
                            case 2 :
                                choose_random_moove(draw);
                                break;
                            default:
                                printf("Choix invalide.\n");
                        }
                    break;

                    case 2 :
                        printf("Retour au menu principal.\n");
                        break;

                }
                break;
            case 3:
                int tree_choice = 0;

                do {
                    printf("\n");
                    printf("-----------------\n");
                    printf("-     Arbre     -\n");
                    printf("-----------------\n");
                    printf("1. Afficher l'arbre\n");
                    printf("2. Calculer la valeur minimale des feuilles\n");
                    printf("3. Trouver le chemin vers les feuilles minimale\n");
                    printf("4. Retour au menu precedent\n");
                    printf("\n");

                    // Lire le choix utilisateur
                    printf("Entrez votre choix : ");
                    scanf("%d", &tree_choice);

                    switch (tree_choice) {
                        case 1:
                            display_tab_random(draw);
                        createTree(map, marc, draw);
                        displayTree(tree);
                        wait_for_user();
                        break;
                        case 2:
                            printf("Valeur minimale des feuilles : %d\n", findMinLeafCost(tree));
                            wait_for_user();
                        break;
                        case 3:
                            findPathToMinLeaf(tree, marc, map, path, &pathSize);
                        printf("Chemin trouve vers la feuille minimale.\n");
                        for (int i = 0; i < pathSize; i++) {
                            printf("etape %d : (x: %d, y: %d)\n", i + 1, path[i].x, path[i].y);
                            wait_for_user();
                        }
                        break;
                        case 4:
                            printf("Retour au menu precedent...\n");
                        break;
                        default:
                            printf("Choix invalide, essayez encore.\n");
                    }
                } while (tree_choice != 4); // Sortir de la boucle si l'utilisateur choisit 4
            case 4:
                int play_choice = 0;
                do {
                    printf("\n");
                    printf("-----------------\n");
                    printf("-     Jouer     -\n");
                    printf("-----------------\n");
                    printf("1. Jouer au jeu \n");
                    printf("2. Retour\n");
                    printf("\n");

                    printf("Veuiilez entrer votre choix : ");
                    scanf("%d", &play_choice);

                    switch (play_choice) {
                        case 1:
                            if ((moveTowardsBase(tree, map, marc, path, &pathSize))== 0 ) {
                                printf("Le rover a atteint la base. Chemin suivi :\n");
                            } else {
                                printf("Le rover n'a pas atteint la base. \n Voici le chemin suivi :\n");
                            }

                            for (int i = 0; i < pathSize; i++) {
                                printf("Mouvement : %d - (x : %d, y :%d)\n ", i+1 , path[i].x, path[i].y);
                            }
                            wait_for_user();
                            break;
                        case 2:
                            printf("Retour au menu precedent...\n");
                            break;
                        default:
                            printf("Choix invalide, essayez encore.\n");
                    }

                }while (play_choice != 2);


                break;
        }

        wait_for_user();

    } while (choice != 3);

    return 0;
}
