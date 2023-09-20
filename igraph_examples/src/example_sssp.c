#include <igraph.h>

// example from file igraph\examples\simple
int main1(void) {

    igraph_t graph;
    igraph_vector_t weights;
    igraph_real_t weights_data[] = { 0, 2, 1, 0, 5, 2, 1, 1, 0, 2, 2, 8, 1, 1, 3, 1, 1, 4, 2, 1 };
    igraph_matrix_t res;
    igraph_real_t cutoff;

    igraph_small(&graph, 10, IGRAPH_DIRECTED,
                 0, 1, 0, 2, 0, 3,    1, 2, 1, 4, 1, 5,
                 2, 3, 2, 6,          3, 2, 3, 6,
                 4, 5, 4, 7,          5, 6, 5, 8, 5, 9,
                 7, 5, 7, 8,          8, 9,
                 5, 2,
                 2, 1,
                 -1);

    igraph_matrix_init(&res, 0, 0);

    printf("Unweighted distances:\n\n");

    igraph_distances(&graph, &res, igraph_vss_all(), igraph_vss_all(), IGRAPH_OUT);
    igraph_matrix_print(&res);

    cutoff = 3; /* distances longer than this will be returned as infinity */
    printf("\nUnweighted distances with a cutoff of %g:\n\n", cutoff);
    igraph_distances_cutoff(&graph, &res, igraph_vss_all(), igraph_vss_all(), IGRAPH_OUT, cutoff);
    igraph_matrix_print(&res);

    printf("\nWeighted distances:\n\n");

    igraph_vector_view(&weights, weights_data,
                       sizeof(weights_data) / sizeof(weights_data[0]));

    igraph_distances_dijkstra(&graph, &res, igraph_vss_all(), igraph_vss_all(),
                              &weights, IGRAPH_OUT);
    igraph_matrix_print(&res);

    cutoff = 8; /* distances longer than this will be returned as infinity */
    printf("\nWeighted distances with a cutoff of %g:\n\n", cutoff);
    igraph_distances_dijkstra_cutoff(&graph, &res, igraph_vss_all(), igraph_vss_all(),
                              &weights, IGRAPH_OUT, cutoff);
    igraph_matrix_print(&res);

    igraph_matrix_destroy(&res);
    igraph_destroy(&graph);

    return 0;
}


// my example
int main(void) {

    igraph_t graph;
    igraph_vector_t weights;
    igraph_matrix_t res;
    igraph_uint_t num_of_vertices = 100;
	igraph_integer_t num_of_edges = 20 * num_of_vertices;

    // create random graph using Erdos-Renyi model
    igraph_rng_seed(igraph_rng_default(), (igraph_uint_t)time(0));
    igraph_erdos_renyi_game_gnm(&graph, num_of_vertices, 
                                num_of_edges, IGRAPH_UNDIRECTED, IGRAPH_NO_LOOPS);

    igraph_vector_init(&weights, num_of_edges);
	// integer weights
    // for (int i = 0; i < num_of_edges; ++i)
        // VECTOR(weights)[i] = igraph_rng_get_integer(igraph_rng_default(), 1, 10);
    // //igraph_vector_print(&weights);
    igraph_matrix_init(&res, 0, 0);

    // real weights
    for (int i = 0; i < num_of_edges; ++i)
        VECTOR(weights)[i] = igraph_rng_get_unif(igraph_rng_default(), 1.0, 10.0);


	igraph_vs_t from;
    igraph_vs_1(&from, 0);
	
    printf("\nWeighted distances:\n\n");
    igraph_distances_dijkstra(&graph, &res, from, igraph_vss_all(),
                              &weights, IGRAPH_OUT);
    igraph_matrix_print(&res);

    igraph_matrix_destroy(&res);
    igraph_destroy(&graph);

    return 0;
}