#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

struct state;

struct pile {
    state* val;
    struct pile* next;
};

struct maillon1 {
    struct state* val;
    struct maillon1* next;
};

struct maillon2 {
    struct state* depart;
    struct state* arrivee;
    struct maillon2* next;
};

struct state {
    char c;
    int index;
    struct maillon1* voisins;
};

struct automate {
    struct state* debut;
    struct maillon1* fin;
};

typedef struct pile pile;
typedef struct maillon1 maillon1;
typedef struct maillon2 maillon2;
typedef struct state state;
typedef struct automate automate;

pile* create_pile_vide()
{

}

void empiler(pile* first, state* new)
{

}

state* depiler(pile* first)
{

}

void addMaillon1(maillon1* first, state* new){
}

void addMaillon2(maillon2* first, state* depart, state* arrivee){
}

void freeAutomate(automate a){
}

int longueurMot(state* mot)
{
    int n =0;
    while(mot[n].c != '\0')
    {
        n++;
    }
    return n;
}

state** match_with(state* nbEx)
{
    pile* traite = create_pile_vide;
    state* traitement = malloc(sizeof(state) * 2);

    int i = 0;
    int caseRempli = 0;
    while(nbEx[i].c != '\0')
    {
        char carTraitement = nbEx[i].c;
        if(carTraitement=='|' || carTraitement=='@')
        {
            if(caseRempli == 0)
            {
                state* mot2 = depiler(traite);
                state* mot1 = depiler(traite);
                if(nbEx[i+1].c == '\0')
                {
                    state* res[3] = {mot1, mot2, &nbEx[i]};
                    return res;
                }
                else
                {
                    int n1 = longueurMot(mot1);
                    int n2 = longueurMot(mot2);
                    state* new= malloc(sizeof(state) * (n1 + n2 + 2));
                    for(int k = 0; k < n1+n2; k++)
                    {
                        if(k < n1-1)
                        {
                            new[k] = mot1[k];
                        }
                        else
                        {
                            new[k] = mot2[k];
                        }
                    }

                    new[n1 + n2] = nbEx[i];

                    new[n1 + n2 + 1].c = '\0';
                    new[n1 + n2 + 1].index = -1;
                    new[n1 + n2 + 1].voisins = NULL;
                    empiler(traite, new);
                }
            }
            if(caseRempli == 1)
            {
                state* mot1 = depiler(traite);
                if(nbEx[i+1].c == '\0')
                {
                    state* res[3] = {mot1, &traitement[0], &nbEx[i]};
                    return res;
                }
                else
                {
                    int n1 = longueurMot(mot1);
                    state* new= malloc(sizeof(state) * (n1 + 3));
                    for(int k = 0; k < n1; k++)
                    {  
                        new[k] = mot1[k];
                    }

                    new[n1] = traitement[0];
                    new[n1+1] = nbEx[i];

                    new[n1 + 2].c = '\0';
                    new[n1 + 2].index = -1;
                    new[n1 + 2].voisins = NULL;
                    empiler(traite, new);
                }
            }
            if(caseRempli == 2)
            {
                if(nbEx[i+1].c == '\0')
                {
                    state* res[3] = {&traitement[0], &traitement[1], &nbEx[i]};
                    return res;
                }
                else
                {
                    state* new= malloc(sizeof(state) * 4);
                    new[0] = traitement[0];
                    new[1] = traitement[1];
                    new[2] = nbEx[i];

                    new[3].c = '\0';
                    new[3].index = -1;
                    new[3].voisins = NULL;
                    empiler(traite, new);
                }
            }
            caseRempli = 0;
        }
        else if(carTraitement=='*' || carTraitement=='?')
        {
            if(caseRempli == 0)
            {
                state* mot1 = depiler(traite);
                if(nbEx[i+1].c == '\0')
                {
                    state* res[3] = {mot1, NULL, &nbEx[i]};
                    return res;
                }
                else
                {
                    int n1 = longueurMot(mot1);
                    state* new= malloc(sizeof(state) * (n1 + 2));
                    for(int k = 0; k < n1; k++)
                    {
                    
                        new[k] = mot1[k];
                  
                    }

                    new[n1] = nbEx[i];

                    new[n1 + 1].c = '\0';
                    new[n1 + 1].index = -1;
                    new[n1 + 1].voisins = NULL;
                    empiler(traite, new);
                }
            }
            if(caseRempli == 1)
            {
                if(nbEx[i+1].c == '\0')
                {
                    state* res[3] = {&traitement[0], NULL, &nbEx[i]};
                    return res;
                }
                else
                {
                    state* new= malloc(sizeof(state) *  3);

                    new[0] = traitement[0];
                    new[1] = nbEx[i];

                    new[2].c = '\0';
                    new[2].index = -1;
                    new[2].voisins = NULL;
                    empiler(traite, new);
                }
                caseRempli = 0;
            }
            if(caseRempli == 2)
            {
                if(nbEx[i+1].c == '\0')
                {
                    state* res[3] = {&traitement[1], NULL, &nbEx[i]};
                    return res;
                }
                else
                {
                    state* new= malloc(sizeof(state) * 3);
                    new[0] = traitement[1];
                    new[1] = nbEx[i];

                    new[2].c = '\0';
                    new[2].index = -1;
                    new[2].voisins = NULL;
                    empiler(traite, new);
                }
                caseRempli = 1;
            }
        }
        else
        {
            traitement[caseRempli] = nbEx[i];
            caseRempli++;
        }
        i++;
    }

}

state* numberEx(char* regex){
    //Léo
    //Elle prend un regex écrit en postfixe et renvoie le tableau des états numérotés
    state* res;
    return res;
}

maillon1* premiers(state* numberRegex){
    //Nathan
    maillon1* res;
    return res;
}

maillon1* derniers(state* numberRegex){
    //Léo
    maillon1* res;
    return res;
}

maillon2* facteurs(state* numberRegex){
    //Nathan
    maillon2* res;
    return res;
}

automate build(maillon1* p, maillon1* d, maillon2* f){
    //Léo
    automate res;
    return res;
}

bool appartient(automate a, char* mot){
    //Nathan
    return false;
}

int main(){

}