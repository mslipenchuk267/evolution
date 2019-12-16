//
// Created by mslip on 12/12/19.
//

#include <stdio.h>
#include "h/evolution.h"
#include "stdlib.h"
#include "h/array.h"
#include "h/read.h"
#include "h/linked-list.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
struct point {
    int i;
    int j;
};

static inline int randomInt(int n); // done - not tested
static void free_herd(conscell *herd); // done - not tested
static int dead_or_alive(const void *aa); // done - not tested
static conscell *remove_the_dead(conscell *herd); // done - not tested
static int nearer_the_eden(const void *aa, const void *bb, void *params); // not done ***********
static void initialize_plants(struct world *world); // done - not tested
static void add_plants(struct world *world); // done - not tested
static int gene_to_activate(int genes[8]); // done - not tested
static void turn(struct animal *animal); // done - not tested
static void move(struct world *world, struct animal *animal); // done - not tested
static void feed(struct world *world, struct animal *animal); // done - not tested
static struct animal *clone(struct animal *old); // done - not tested
static void mutate(int genes[8]); // done - not tested
static void reproduce(struct world *world, struct animal *animal); // done - not tested
static void update_world(struct world *world); // done - not tested
static void evolve(struct world *world, unsigned int n); // done - not tested
static void evolve_with_figs(struct world *world, unsigned int n); // done - not tested
static void show_usage(char *progname); // done - not tested

// Return a random integer from 0 to n-1
static inline int randomInt(int n) {
    return rand() / (RAND_MAX/n + 1);
}

static void initialize_plants(struct world *world) {
    make_matrix(world->plants, world->world_h, world->world_w);
}

static int nearer_the_eden(const void *aa, const void *bb, void *params) {

}

static int gene_to_activate(int genes[8]) {
    int random_gene;
    random_gene = randomInt(8);
    return random_gene;
}

static void free_herd(conscell *herd) {
    for (conscell *p = herd; p != NULL; p = p->next) {
        free(p->data);
    }
    ll_free(herd);
}

static int dead_or_alive(const void *aa){
    if (aa < 1) {
        return 0;
    } else {
        return 1;
    }
}

static conscell *remove_the_dead(conscell *herd) {
    conscell *dead = NULL;
    herd = ll_filter(herd, dead_or_alive, &dead);
    free_herd(dead);
    return herd;
}

static struct animal *clone(struct animal *old) {
    struct animal *new = xmalloc(sizeof *new);
    new->i = old->i;
    new->j = old->j;
    new->d = old->d;
    new->e = old->e;
    int i;
    for (i = 0; i < 9; i++) {
        new->genes[i] = old->genes[i];
    }
    return new;
}

static void feed(struct world *world, struct animal *animal) {
    if (world->plants[animal->i][animal->j] > 0) {
        world->plants[animal->i][animal->j] -= 1;
        animal->e += world->plant_energy;
    }
}

static void turn(struct animal *animal) {
    int activated_gene;
    // Select which gene is activated
    activated_gene = gene_to_activate(animal->genes);
    // Update animal's orientation i.e. direction
    animal->d = (animal->d + activated_gene) % 8;
}

static void move(struct world *world, struct animal *animal) {
    struct {
        int i;
        int j;
    } motion_vectors[] = {
            {1,0},
            {1,1},
            {0,1},
            {-1, 1},
            {-1, 0},
            {-1, -1},
            {0, -1},
            {1, -1}
    };
    int i = animal->i + motion_vectors[animal->d].i;
    int j = animal->j + motion_vectors[animal->d].j;
    if (i < 0) {
        i += world->world_h;
    } else if (i >= world->world_h) {
        i -= world->world_h;
    }
    if (j < 0) {
        j += world->world_w;
    } else if (j >= world->world_w) {
        j -= world->world_w;
    }
    animal->i = i;
    animal->j = j;
}

static void mutate(int genes[8]) {
    int gene_to_mutate = randomInt(8);
    int mutations[3] = {-1, 0, 1};
    genes[gene_to_mutate] += mutations[randomInt(3)];
}

static void add_plants(struct world *world) {
    // Deposit food in world
    int i = randomInt(world->world_h);
    int j = randomInt(world->world_w);
    world->plants[i][j]++; // Deposit morsel of food
    // Deposit food in Eden if it exists
    if (world->eden_h > 0 && world->eden_w > 0) {
        i = randomInt(world->eden_h);
        j = randomInt(world->eden_w);
        world->plants[i][j]++;
    }
}



static void reproduce(struct world *world, struct animal *animal) {
    animal->e /= 2;
    struct animal *new = clone(animal);
    mutate(new->genes);
    world->herd = ll_push(world->herd, new);
}

static void update_world(struct world *world) {
    world->herd = remove_the_dead(world->herd);
    for (conscell *p = world->herd; p != NULL; p = p->next) {
        struct animal *a = p->data;
        turn(a);
        move(world, a);
        feed(world, a);
        a->e--;
        if(a->e >= world->reproduction_threshold) {
            reproduce(world, a);
        }
    }
    add_plants(world);
}

static void evolve_with_figs(struct world *world, unsigned int n){
    char buf[16];
    for (unsigned long int i = 0; i < n; i++) {
        sprintf(buf, "fig%04lu.eps", i);
        world_to_eps(world, buf);
        if (i < n - 1) {
            update_world(world);
        }
    }
}

static void evolve(struct world *world, unsigned int n){
    char buf[16];
    for (unsigned long int i = 0; i < n; i++) {
        sprintf(buf, "World Update #: %d", i);
        if (i < n - 1) {
            update_world(world);
        }
    }
}

static void show_usage(char *progname){
    // square bracket indicates optional parameter
    printf("Reads World Definition from infile, performs nupdates, and writes result to outfile.\nUsage: ./evolution n [f] <infile  >outfile\nn >= 0 : (Req.) number of updates\nf >= 0: number of snapshots after n updates");
}

int main(int argc, char **argv) {
    unsigned long int n;
    unsigned long int f = 0;
    struct world World;
    struct world *world = &World;
    int exit_status = EXIT_SUCCESS;
    world->herd   = NULL;
    world->plants = NULL;

    if (argc < 2 || argc > 3) {
        show_usage(argv[0]);
        goto cleanup;
    }

    if (sscanf(argv[1], "%lu", &n) != 1) {
        show_usage(argv[0]);
        goto cleanup;
    }

    if (argc > 2 && sscanf(argv[2], "%lu", &f) != 1) {
        show_usage(argv[0]);
        goto cleanup;
    }

    if (!read_wdf(world)) {
        goto cleanup;
    }
    initialize_plants(world);
    evolve(world, n);
    if (f > 0) {
        evolve_with_figs(world, f);
    }

    struct point eden_center;
    eden_center.i = (world->world_h - 1)/2;
    eden_center.j = (world->world_w - 1)/2;
    world->herd = ll_sort(world->herd, nearer_the_eden, &eden_center);
    write_wdf(world);
    exit_status = EXIT_SUCCESS;

    cleanup:
        free_matrix(world->plants);
        free_herd(world->herd);
        return exit_status;
}