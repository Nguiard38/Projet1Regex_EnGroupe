#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

struct state;

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

typedef struct maillon1 maillon1;
typedef struct maillon2 maillon2;
typedef struct state state;
typedef struct automate automate;

void addMaillon1(maillon1* first, state* new){
}

void addMaillon2(maillon2* first, state* depart, state* arrivee){
}

void freeAutomate(automate a){
}

state* numberEx(char* regex){
    //Elle prend un regex écrit en postfixe et renvoie le tableau des états numérotés
    state* res;
    return res;
}

maillon1* premiers(state* numberRegex){
    maillon1* res;
    return res;
}

maillon1* derniers(state* numberRegex){
    maillon1* res;
    return res;
}

maillon2* facteurs(state* numberRegex){
    maillon2* res;
    return res;
}

automate build(maillon1* p, maillon1* d, maillon2* f){
    automate res;
    return res;
}

bool appartient(automate a, char* mot){
    return false;
}

int main(){

}