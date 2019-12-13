
#ifndef H_EVOLUTION_H

#define H_EVOLUTION_H

#include "linked-list.h"

struct animal {

    int i; // row numberofanimal’sposition

    int j; // columnnumberofanimal’s position

    int d; // direction theanimalisfacing: 0,...,7

    int e; // animal’s energy

    int genes[8]; // theanimal’schromosome(array ofgenes)

} animal;

struct world {
    int world_h; // world’sheight
    int world_w; // world’swidth
    int eden_h; // Eden’sheight
    int eden_w; // Eden’swidth
    int plant_energy; // plantenergy
    int reproduction_threshold; // reproduction threshold

    int **plants; // world_h×world_warray ofplants
    conscell *herd; // theheadofthelinkedlistoftheani
};

#endif /∗ H_EVOLUTION_H */
