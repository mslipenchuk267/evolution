#ifndef H_EVOLUTION_H
#define H_EVOLUTION_H

#include "h/linked-list.h"
struct animal {
    int i;
    int j;
    int d;
    int e;
    int genes[8];
}; animal;
struct world {
    int world_h;
    int world_w;
    int eden_h;
    int eden_w;
    int plant_energy;
    int reproduction_threshold;
    int **plants;
    conscell *herd;
};
#endif //H_EVOLUTION_H
