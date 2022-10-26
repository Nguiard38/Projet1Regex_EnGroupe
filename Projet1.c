#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


#define EPS 256
#define ALL 257
#define MATCH 258

#define MAX_LINE_LENGTH 1024

struct state {
    int c;
    struct state *out1;
    struct state *out2;
    int last_set;
};

typedef struct state state_t;

struct nfa {
    state_t *start;
    state_t *final;
    int n;
};

typedef struct nfa nfa_t;

struct stack {
    int length;
    int capacity;
    nfa_t *data;
};

typedef struct stack stack;

struct set {
    int length;
    int id;
    state_t **states;
};

typedef struct set set_t;

state_t *new_state(int c, state_t *out1, state_t *out2) {
    // À modifier !
    printf("Hello world 2 !");
    return NULL;
}

nfa_t character(int c) {
    // À modifier !
    nfa_t a = {0};
    return a;
}

nfa_t all(void) {
    // À modifier !
    nfa_t a = {0};
    return a;
}

nfa_t concat(nfa_t a, nfa_t b) {
    // À modifier !
    nfa_t c = {0};
    return c;
}

nfa_t alternative(nfa_t a, nfa_t b) {
    // À modifier !
    nfa_t c = {0};
    return c;
}

nfa_t star(nfa_t a) {
    // À modifier !
    nfa_t astar = {0};
    return astar;
}

nfa_t maybe(nfa_t a) {
    // À modifier !
    nfa_t amaybe = {0};
    return amaybe;
}

stack *stack_new(int capacity) {
    stack *s = malloc(sizeof(stack));
    s->data = malloc(capacity * sizeof(nfa_t));
    s->capacity = capacity;
    s->length = 0;
    return s;
}

void stack_free(stack *s) {
    free(s->data);
    free(s);
}

nfa_t pop(stack *s) {
    assert(s->length > 0);
    nfa_t result = s->data[s->length - 1];
    s->length--;
    return result;
}

void push(stack *s, nfa_t a) {
    assert(s->capacity > s->length);
    s->data[s->length] = a;
    s->length++;
}

nfa_t build(char *regex) {
    // À modifier !
    nfa_t result;
    return result;
}


int main(int argc, char* argv[]) {
}
