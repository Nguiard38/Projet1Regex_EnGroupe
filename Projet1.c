#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define MAX_LINE_LENGTH 1024

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

maillon1* addMaillon1(maillon1* first, state* new){

    if(first == NULL)
    {
        first = malloc(sizeof(maillon1));
        first->next = NULL;
        first->val = new;
    }
    else
    {
        maillon1* current = first;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = malloc(sizeof(maillon1));
        current->next->next = NULL;
        current->next->val = new;
    }   
    return first;
    
}

maillon1* unionMaillon1(maillon1* u, maillon1* v)
{
    maillon1* current = u;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = v;
    return u;
    
}

maillon2* addMaillon2(maillon2* first, state* depart, state* arrivee){

    if(first == NULL)
    {
        first = malloc(sizeof(maillon2));
        first->next = NULL;
        first->depart = depart;
        first->arrivee = arrivee;
    }
    else
    {
        maillon2* current = first;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = malloc(sizeof(maillon2));
        current->next->next = NULL;
        current->next->depart = depart;
        current->next->arrivee = arrivee;
    }
    return first;
}

maillon2* unionMaillon2(maillon2* u, maillon2* v)
{
    if(u == NULL)
    {
        return v;
    }
    else
    {
        maillon2* current = u;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = v;
        return u;
    }
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

void print_maillon1(maillon1* ensemble)
{
    maillon1* current = ensemble;
    while(current != NULL)
    {
        printf("%c%d\n", current->val->c, current->val->index);
        current = current->next;
    }
}

void print_maillon2(maillon2* ensemble)
{
    maillon2* current = ensemble;
    while(current != NULL)
    {
        printf("%c%d%c%d\n", current->depart->c, current->depart->index, current->arrivee->c,  current->arrivee->index);
        current = current->next;
    }
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

state* create_stateEtoile_from_state(state c)
{
    //Cette fonction prend en argument un state c et retourne le tableau de state contenant c et le state vide
    state* res = malloc(sizeof(state) * 2);
    res[0] = c;
    res[1].c = '\0';
    res[1].index = -1;
    res[1].voisins = NULL;
    return res;
}

state** match_with(state* nbEx)
{
    /*
    Cette fonction prend en argument une expression (un tableau de state) et retourne le tableau contenant le match de cette expression
    
    EX : (a|b)(ab) -> ab|ab@@
    match[0] : (a|b) -> ab|
    match[1] : ab -> ab@
    match[2] : @

    L'algo fonctionne grace a un tableau de trois state qui represente les caractere entrain d'etre traite
    et grace a une pile d'expression (tableau de state) qui represente les expression deja traite
    */
    pile* traite = create_pile_vide();
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
           
                state* mot1 = depiler(traite);
                if(nbEx[i+1].c == '\0')
                {
             
                    state** res = malloc(sizeof(state*) * 3);
                    res[0] = mot1;
                    res[1] = create_stateEtoile_from_state(traitement[0]);
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
                    res[0] = create_stateEtoile_from_state(traitement[0]);
                    res[1] = create_stateEtoile_from_state(traitement[1]);
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
                    res[0] = create_stateEtoile_from_state(traitement[0]);
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
                    res[0] = create_stateEtoile_from_state(traitement[1]);
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
            traitement[caseRempli] = nbEx[i];
            caseRempli++;
            if(nbEx[i+1].c == '\0')
            {
                state** res = malloc(sizeof(state*) * 3);
                res[0] = create_stateEtoile_from_state(traitement[caseRempli]);
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
    /*
    Cette fonction prend en argument une expression (tableau de state)
    Et retourne la liste (maillon chaine) des state qui peuevent etre premieres lettres de l'expression
    */

    maillon1* res = NULL; 

    if(numberRegex[0].c == '\0')
    {
        return res;
    }
    else if(numberRegex[1].c == '\0')
    {
        res = malloc(sizeof(maillon1));
        res->val = malloc(sizeof(state));
        res->val->c = numberRegex[0].c;
        res->val->index = numberRegex[0].index;
        res->val->voisins = numberRegex[0].voisins;
        res->next = NULL;
        return res;
    }
    else
    {
        state** match = match_with(numberRegex);
        if(match[2][0].c == '@')
        {
            if(match[0][longueurMot(match[0])-1].c == '*' || match[0][longueurMot(match[0])-1].c == '?')
            {
                return unionMaillon1(premiers(match[0]), premiers(match[1]));
            }
            else
            {
                return premiers(match[0]);
            }
        }
        else if(match[2][0].c == '|')
        {
            return unionMaillon1(premiers(match[0]), premiers(match[1]));
        }
        else
        {
            return premiers(match[0]);
        }
    }
}

maillon1* derniers(state* numberRegex){
    maillon1* res = NULL;
    if(numberRegex[0].c=='\0'){
        return res;
    }else if(numberRegex[1].c=='\0'){
        res = malloc(sizeof(maillon1));
        res->val = malloc(sizeof(state));
        res->val->c = numberRegex[0].c;
        res->val->index = numberRegex[0].index;
        res->val->voisins = numberRegex[0].voisins;
        res->next = NULL;
        return res;
    }else{
        state** match = match_with(numberRegex);
        if(match[2][0].c=='|'){
            return unionMaillon1(derniers(match[0]), derniers(match[1]));
        } else if(match[2][0].c=='@'){
            if(match[1][longueurMot(match[1])-1].c == '*' || match[1][longueurMot(match[1])-1].c == '?'){
                return unionMaillon1(derniers(match[0]), derniers(match[1]));
            } else {
                return derniers(match[1]);
            }
        }else {
            return derniers(match[0]);
        }
    }
}

maillon2* ensembleDernPrem(state* u, state* v)
{

    /*
    Cette fonction prend en argument deux expressions u et v (tableau de state) et renvoie 
    l'ensemble des facteurs possible que forment la concatenation de u et v en utilisant les derniers de u et les premiers de v
    */

    maillon2* res = NULL;
    maillon1* dern = derniers(u);
    maillon1* prem = premiers(v);

    maillon1* currentDern = dern;
    
    while(currentDern != NULL)
    {
        maillon1* currentPrem = prem;
        while(currentPrem != NULL)
        {
            res = addMaillon2(res, currentDern->val, currentPrem->val);
            currentPrem = currentPrem->next;
        }
        currentDern = currentDern->next;
    }
    
    return res;
}

maillon2* facteurs(state* numberRegex)
{
    /*
    Cette fonction prend en argument une expression (tableau de state)
    Et retourne la liste (maillon chaine) des couples de state qui sont facteur de l'expression
    */

    if(numberRegex[0].c == '\0' || numberRegex[1].c == '\0')
    {
        return NULL;
    }
    else
    {
        state** match = match_with(numberRegex);
        if(match[2][0].c == '@')
        {
            return unionMaillon2(facteurs(match[0]), unionMaillon2(facteurs(match[0]), ensembleDernPrem(match[0], match[1])));
        }
        else if(match[2][0].c == '|')
        {
            return unionMaillon2(facteurs(match[0]), facteurs(match[1]));
        }
        else if(match[2][0].c == '*')
        {
            return unionMaillon2(facteurs(match[0]), ensembleDernPrem(match[0], match[0]));
        }
        else
        {
            return facteurs(match[0]);
        }
    }
}

automate build(state* numberRegex){
    automate res;

    maillon1* p = premiers(numberRegex);
    maillon1* d = derniers(numberRegex);
    maillon2* f = facteurs(numberRegex);

    state* debut = malloc(sizeof(state));
    debut->c=1;
    debut->index=-1;
    debut->voisins=p;
   
    while(f!=NULL){
        f->depart->voisins = addMaillon1(f->depart->voisins, f->arrivee);
        f=f->next;
    }

    res.debut=debut;
    res.fin=d;
    return res;
}

bool appartienMaillon1(state* s, maillon1* d)
{
    maillon1* current = d;
    while(current!= NULL)
    {
        if(current->val->c == s->c && current->val->index == s->index)
        {
            return true;
        }
        current = current->next;
    }
}

bool reconnu(automate a, char* mot){
    if(mot[0] == '\0')
    {
        return appartienMaillon1(a.debut, a.fin);
    }
    else
    {
        
        maillon1* current = a.debut->voisins;
        while(current!= NULL)
        {
            if(current->val->c == mot[0] || current->val->c == '.')
            {
                automate new;
                new.debut = current->val;
                new.fin = a.fin;
                if(reconnu(new, &mot[1]))
                {
                    return true;
                }

            }
            
            current = current->next;
        }
        return false;
    }
  
}


int main(int argc, char* argv[]){
    state a;
    state b;
    state c;
    state epsilon;

    a.c = 'a';
    a.index = 0;
    a.voisins = NULL;
    a.voisins = addMaillon1(a.voisins, &a);
    a.voisins = addMaillon1(a.voisins, &b);
    a.voisins = addMaillon1(a.voisins, &c);


    b.c = 'b';
    b.index = 1;
    b.voisins = NULL;
    b.voisins = addMaillon1(b.voisins, &a);
    b.voisins = addMaillon1(b.voisins, &b);
    b.voisins = addMaillon1(b.voisins, &c);
        
    c.c = 'c';
    c.index = 2;
    c.voisins = NULL;

    epsilon.c = 'e';
    epsilon.index = '2';
    epsilon.voisins = NULL;
    epsilon.voisins = addMaillon1(epsilon.voisins, &a);
    epsilon.voisins = addMaillon1(epsilon.voisins, &b);
    epsilon.voisins = addMaillon1(epsilon.voisins, &c);

    automate automateTest;
    automateTest.debut = &epsilon;
    automateTest.fin = NULL;
    automateTest.fin = addMaillon1(automateTest.fin, &a);
    automateTest.fin = addMaillon1(automateTest.fin, &c);


    state arobase;
    arobase.c = '@';
    arobase.index = -1;
    arobase.voisins = NULL;



    state fin;
    fin.c = '\0';
    fin.index = -1;
    fin.voisins = NULL;

    state test[4] = {a,b,arobase,fin};
    state* test2 = numberEx("ab|");

    printf("Expr de base : \n");
    print_state(test2);
    printf("\n");

    /*state** match = match_with(test2);
    printf("Match : \n");
    print_state(match[0]);
    print_state(match[1]);
    printf("%c\n\n", match[2][0].c);
    printf("\n");*/

    printf("Premiers : \n");
    print_maillon1(premiers(test2));
    printf("\n");

    printf("Derniers : \n");
    print_maillon1(derniers(test2));
    printf("\n");

    printf("Facteurs : \n");
    print_maillon2(facteurs(test2));
    printf("\n");

    state* exNum = numberEx(argv[1]);
    automate au = build(exNum);

    FILE* in = fopen(argv[2], "r");
    char* line = malloc((MAX_LINE_LENGTH + 1) * sizeof(char));
    while (true) {
        if (fgets(line, MAX_LINE_LENGTH, in) == NULL) break;
        int i = 0; 
        while(line[i] != '\0')
        {
            i++;
        }
        line[i-1] = '\0';
        if (reconnu(au, line)) {
            puts(line);
        }
    }
    fclose(in);
    free(line);
    
    return 0;

}