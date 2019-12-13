//
// Created by mslip on 12/12/19.
//

#include <stdio.h>
#include "h/evolution.h"
#include "xmalloc.h"
#include "array.h"
#include "read.h"
#include "write.h"
#include "linked-list.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
struct point {
    int i;
    int j;
};

static inline int random(int n);
static void free_herd(conscell *herd);
static int dead_or_alive(const void *aa);
static conscell *remove_the_dead(conscell *herd);
static int nearer_the_eden(const void *aa, const void *bb, void *params);
static void initialize_plants(struct world *world);
static void add_plants(struct world *world);
static int gene_to_activate(int genes[8]);
static void turn(struct animal *animal);
static void move(struct world *world, struct animal *animal);
static void feed(struct world *world, struct animal *animal);
static struct animal *clone(struct animal *old);
static void mutate(int genes[8]);
static void reproduce(struct world *world, struct animal *animal);
static void update_world(struct world *world);
static void evolve(struct world *world, unsigned int n);
static void evolve_with_figs(struct world *world, unsigned int n);
static void show_usage(char *progname);

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

    cleanup:
        free_matrix(world->plants);
        free_herd(world->herd);
        return exit_status;


}