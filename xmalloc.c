//
// Created by mslip on 12/15/19.
//

#include <stdlib.h>
#include "h/xmalloc.h"

void *malloc_or_exit (size_t nbytes, const char *file, int line) {
    // Homemade implementation of xmalloc
    //   If nbytes = 0,
    //    then this function assumes that they are they indicating that
    //    they want a null pointer.
    //   If malloc(nbytes) = NULL,
    //    then the user is requesting for more bytes than is possible to
    //    allocate and we exit the program and print error.
    //
    // Args:
    //   - nbytes : the number of byes to be allocated
    //   - *file  : pointer to executing file
    //   - line   : currently executing line (i.e. the one that throws error)
    //
    // Output:
    //  If nbytes = 0               -> return NULL pointer.
    //  If malloc(nbytes) != NULL   -> return void pointer of size nbytes
    //  If malloc allocation failes -> return EXIT_FAILURE & exit

    if (nbytes == 0) { // User wants a null pointer
        return NULL; // make sure NULL is returned and not bogus value
    }

    void *x;
    if ( (x = malloc(nbytes)) == NULL) {
        // Save what you have now to save current state of what they are doing
        exit(EXIT_FAILURE);
    } else { // Allocation Successful
        return x;
    }
}
