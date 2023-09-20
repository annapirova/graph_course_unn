#ifndef IGRAPH_MTX_READER
#define IGRAPH_MTX_READER

#include <igraph.h>

igraph_error_t read_mtx_to_igraph(igraph_t *graph, FILE *instream);

#endif