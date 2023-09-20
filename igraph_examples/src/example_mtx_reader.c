#include <stdio.h>
#include <stdlib.h>
#include "igraph_mtx_reader.h"

void print_graph(igraph_t *graph, const char *initial_message) {
    printf("%s\n", initial_message);
    printf("Vertices: %" IGRAPH_PRId ", edges: %" IGRAPH_PRId "\n", 
        igraph_vcount(graph),
        igraph_ecount(graph));
    igraph_write_graph_edgelist(graph, stdout);
    printf("\n");
}

int main(int argc, char *argv[]) {
    igraph_t graph_from_mtx;
    FILE *instream;
    
    if (argc < 2) {
        printf("Path to MTX file isn't specified\n");
        return -1;
    }
    instream = fopen(argv[1], "r");
    if (instream == NULL) {
        printf("Can't open file\n");
        return -2;
    }
    if (read_mtx_to_igraph(&graph_from_mtx, instream) == IGRAPH_PARSEERROR) {
        printf("Error while reading file\n");
        return -3;
    }
    fclose(instream);
    
    print_graph(&graph_from_mtx, "GRAPH FROM MTX FILE");
    return 0;
}
