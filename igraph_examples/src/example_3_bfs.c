// BFS
// https://igraph.org/c/doc/igraph-Visitors.html#breadth-first-search

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <igraph.h>
#include "igraph_mtx_reader.h"

// argv[1] - .mtx file 
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Path to MTX file isn't specified\n");
        return -1;
    }

    igraph_t graph;
    igraph_vector_int_t bfs_parents_seq;
    FILE *instream;
    clock_t seq_begin, seq_end;
    
    // reading graph from MTX
    instream = fopen(argv[1], "r");
    if (instream == NULL) {
        printf("Can't open file\n");
        return -2;
    }
    if (read_mtx_to_igraph(&graph, instream) == IGRAPH_PARSEERROR) {
        printf("Error while reading file\n");
        return -3;
    }
    fclose(instream);

    // set bfs_parents_seq = 0
    igraph_vector_int_init(&bfs_parents_seq, 0);

	// bfs returns only parents array
	// https://igraph.org/c/doc/igraph-Visitors.html#igraph_bfs_simple
	// igraph_error_t igraph_bfs_simple(
    //    const igraph_t *graph, igraph_integer_t root, igraph_neimode_t mode,
    //    igraph_vector_int_t *order, igraph_vector_int_t *layers,
    //    igraph_vector_int_t *parents);
	// mode - the direction of the edges (IGRAPH_OUT, IGRAPH_IN, IGRAPH_ALL)
	// order - vertex traversal order
	// layers - the vertices that are at distance i from the root, you need to look 
	//          in the order vector from layers[i] to layers[i+1]
	// parents - index of the parent node for each visited node. 
	//           The values in the vector are set to -2 for vertices that were not visited, 
	//           and -1 for the root vertex.

    seq_begin = clock();
    IGRAPH_CHECK(igraph_bfs_simple(&graph, 0, IGRAPH_ALL,
                                   NULL, NULL, &bfs_parents_seq));
    seq_end = clock();

	// IGRAPH_CHECK Checks the return value of a function call (IGRAPH_SUCCESS or not)
	// https://igraph.org/c/doc/igraph-Error.html#IGRAPH_CHECK
	
    printf("Path to graph: %s\n", argv[1]);
    printf("Simple Sequential BFS time: %ld mcs\n", seq_end - seq_begin);
    igraph_vector_int_print(&bfs_parents_seq);

	// bfs returns all arrays
	// https://igraph.org/c/doc/igraph-Visitors.html#igraph_bfs
	// igraph_error_t igraph_bfs(const igraph_t *graph,
               // igraph_integer_t root, const igraph_vector_int_t *roots,
               // igraph_neimode_t mode, igraph_bool_t unreachable,
               // const igraph_vector_int_t *restricted,
               // igraph_vector_int_t *order, igraph_vector_int_t *rank,
               // igraph_vector_int_t *parents,
               // igraph_vector_int_t *pred, igraph_vector_int_t *succ,
               // igraph_vector_int_t *dist, igraph_bfshandler_t *callback,
               // void *extra);
 
 {
	igraph_vector_int_t order, rank, father, pred, succ, dist;
    igraph_vector_int_init(&order, 0);
    igraph_vector_int_init(&rank, 0);
    igraph_vector_int_init(&father, 0);
    igraph_vector_int_init(&pred, 0);
    igraph_vector_int_init(&succ, 0);
    igraph_vector_int_init(&dist, 0);

    /* call the BFS function */
    seq_begin = clock();

    igraph_bfs(&graph, /*root=*/0, /*roots=*/ NULL, /*neimode=*/ IGRAPH_ALL,
               /*unreachable=*/ 1, /*restricted=*/ NULL,
               &order, &rank, &father, &pred, &succ, &dist,
               /*callback=*/ NULL, /*extra=*/ NULL);
    seq_end = clock();
	
    printf("Sequential BFS time: %ld mcs\n", seq_end - seq_begin);

    /* Print the results */
    // igraph_vector_int_print(&order);
    // igraph_vector_int_print(&rank);
    // igraph_vector_int_print(&father);
    // igraph_vector_int_print(&pred);
    // igraph_vector_int_print(&succ);
    // igraph_vector_int_print(&dist);

    /* Cleam up after ourselves */
    igraph_vector_int_destroy(&order);
    igraph_vector_int_destroy(&rank);
    igraph_vector_int_destroy(&father);
    igraph_vector_int_destroy(&pred);
    igraph_vector_int_destroy(&succ);
    igraph_vector_int_destroy(&dist);	
 }
 
	igraph_destroy(&graph);
	igraph_vector_int_destroy(&bfs_parents_seq);

    return 0;
}