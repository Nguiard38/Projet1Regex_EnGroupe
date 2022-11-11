#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

struct state;

struct couche {
    struct state* val;
    struct couche* next;
};

struct pile {
    struct couche* first;
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

typedef struct couche couche;
typedef struct pile pile;
typedef struct maillon1 maillon1;
typedef struct maillon2 maillon2;
typedef struct state state;
typedef struct automate automate;

pile* create_pile_vide()
{
    pile* p = malloc(sizeof(pile));
    p->first = NULL;
    return p;
}

void empiler(pile* p, state* new)
{
    couche* newFirst = malloc(sizeof(couche));
    newFirst->val = new;
    newFirst->next = p->first;
    p->first = newFirst;
    
}

state* depiler(pile* p)
{
    if(p != NULL)
    {
        state* res = p->first->val;
        couche* aLib = p->first;
        p->first = p->first->next;
        free(aLib);
        return res;
    }
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

state* create_state_from_car(state c)
{
    state* res = malloc(sizeof(state) * 2);
    res[0] = c;
    res[1].c = '\0';
    res[1].index = -1;
    res[1].voisins = NULL;
    return res;
}

state** match_with(state* nbEx)
{
    pile* traite = create_pile_vide();
    state* traitement = malloc(sizeof(state) * 2);

    int i = 0;
    int caseRempli = 0;
    while(nbEx[i].c != '\0')
    {
        char carTraitement = nbEx[i].c;
        if(carTraitement=='|' || carTraitement=='@')
        {
            printf("| ou @\n");
            printf("rempli : %d\n", caseRempli);
            if(caseRempli == 0)
            {
                state* mot2 = depiler(traite);
                state* mot1 = depiler(traite);
                if(nbEx[i+1].c == '\0')
                {
                    printf("Fini\n");
                    state** res = malloc(sizeof(state*) * 3);
                    res[0] = mot1;
                    res[1] = mot2;
                    res[2] = &nbEx[i];
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
            else if(caseRempli == 1)
            {
                printf("test\n");
                state* mot1 = depiler(traite);
                if(nbEx[i+1].c == '\0')
                {
                    printf("fini\n");
                    state** res = malloc(sizeof(state*) * 3);
                    res[0] = mot1;
                    res[1] = create_state_from_car(traitement[0]);
                    res[2] = &nbEx[i];
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
            else if(caseRempli == 2)
            {
                if(nbEx[i+1].c == '\0')
                {
                    state** res = malloc(sizeof(state*) * 3);
                    res[0] = create_state_from_car(traitement[0]);
                    res[1] = create_state_from_car(traitement[1]);
                    res[2] = &nbEx[i];
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
            printf("Kleene\n");
            if(caseRempli == 0)
            {
                state* mot1 = depiler(traite);
                if(nbEx[i+1].c == '\0')
                {
                    state** res = malloc(sizeof(state*) * 3);
                    res[0] = mot1;
                    res[1] = NULL;
                    res[2] = &nbEx[i];
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
                    state** res = malloc(sizeof(state*) * 3);
                    res[0] = create_state_from_car(traitement[0]);
                    res[1] = NULL;
                    res[2] = &nbEx[i];
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
                    state** res = malloc(sizeof(state*) * 3);
                    res[0] = create_state_from_car(traitement[1]);
                    res[1] = NULL;
                    res[2] = &nbEx[i];
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
            printf("Lettre\n");
            traitement[caseRempli] = nbEx[i];
            caseRempli++;
            if(nbEx[i+1].c == '\0')
            {
                state** res = malloc(sizeof(state*) * 3);
                res[0] = create_state_from_car(traitement[caseRempli]);
                res[1] = NULL;
                res[2] = &nbEx[i];
                return res;
            }
        }
        i++;
    }

}

state* numberEx(char* regex){
    //Léo
    //Elle prend un regex écrit en postfixe et renvoie le tableau des états numérotés

    int n = 0;
    while (regex[n] != '\0') {
        n++;
    }

    state* res = malloc(sizeof(state)*(n+1));

    int index = 0;

    for(int i=0; i<n; i++){
        if(regex[i]=='|' || regex[i]=='@' || regex[i]=='*' || regex[i]=='?'){
            res[i].index=-1;
        } else {
            res[i].index=index;
            index++;
        }
        res[i].c=regex[i];
        res[i].voisins=NULL;
    }
    
    res[n].c='\0';
    res[n].index=-1;
    res[n].voisins=NULL;

    return res;
}

maillon1* premiers(state* numberRegex){
    state** match = match_with(numberRegex);
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

void print_state(state* mot)
{
    int i = 0;
    while(mot[i].c != '\0')
    {
        printf("%c", mot[i].c);
        i++;
    }
    printf("\n");
}

int main(){
    state a;
    a.c = 'a';
    a.index = 0;
    a.voisins = NULL;

    state b;
    b.c = 'b';
    b.index = 1;
    b.voisins = NULL;

    state arobase;
    arobase.c = '@';
    arobase.index = -1;
    arobase.voisins = NULL;

    state fin;
    fin.c = '\0';
    fin.index = -1;
    fin.voisins = NULL;

    state test[4] = {a,b,arobase,fin};
    state* test2 = numberEx("ab|a|");

    print_state(test2);

    state** match = match_with(test2);
    
    print_state(match[0]);
    print_state(match[1]);
    printf("%c\n", match[2][0].c);


}