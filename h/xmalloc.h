//
// Created by mslip on 12/15/19.
//

#ifndef H_XMALLOC_H
#define H_XMALLOC_H


void *malloc_or_exit(size_t nbytes, const char *file, int line);

#define xmalloc(nbytes) malloc_or_exit(nbytes,__FILE__,__LINE__);


#endif //H_XMALLOC_H
