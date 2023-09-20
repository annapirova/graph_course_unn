#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <igraph.h>

void print_graph(igraph_t *graph, const char *initial_message) {
    printf("%s\n", initial_message);
    printf("Vertices: %" IGRAPH_PRId ", edges: %" IGRAPH_PRId "\n", 
        igraph_vcount(graph),
        igraph_ecount(graph));
    igraph_write_graph_edgelist(graph, stdout);
    printf("\n");
}

int main (int argc, char *argv[]) {
    igraph_t graph_from_edgelist,
             small_graph,
             star_graph,
             square_lattice_graph,
             cycle_graph,
             simple_path_graph,
             full_graph,
             erdos_renyi_graph;
    const igraph_integer_t num_of_edges = 4;
    const igraph_integer_t num_of_vertices = 4;
    
    
    // create graph from vector of edges (edgelist)
    igraph_vector_int_t edgelist;
    igraph_integer_t edges[] = {0, 1, // edge is a pair of adjacent vertices
                                1, 2,
                                2, 0,
                                3, 0};
    igraph_vector_int_view(&edgelist, edges, num_of_edges * 2);
    igraph_create(&graph_from_edgelist, &edgelist, num_of_edges, 
                                                        IGRAPH_UNDIRECTED);
    print_graph(&graph_from_edgelist, "GRAPH CREATED FROM EDGELIST");

    // create graph by passing edges directly
    // edge is passed as a pair of vertices
    // argument list is terminated with -1
    // number of edges must be equal to 'num_of_edges' argument
    igraph_small(&small_graph, num_of_edges, IGRAPH_UNDIRECTED, 0, 1,
                                                                0, 2, 
                                                                1, 3, 
                                                                2, 3,
                                                                -1);
    print_graph(&small_graph, "SMALL GRAPH CREATED BY PASSING EDGES DIRECTLY");

    // create star graph with 'num_of_vertices' vertices
    // center of star is the vertex 'star_center'
    const igraph_integer_t star_center = 2;
    igraph_star(&star_graph, num_of_vertices, IGRAPH_UNDIRECTED, star_center);
    print_graph(&star_graph, "STAR GRAPH (VERTEX 2 IS A CENTER)");


    // create square lattice 3x3
    igraph_bool_t no_mutual_edges = 0;
    igraph_vector_int_t dimvector;
    igraph_vector_int_init(&dimvector, 2);
    VECTOR(dimvector)[0] = 3;
    VECTOR(dimvector)[1] = 3;
    igraph_square_lattice(&square_lattice_graph, &dimvector, 1, 
        IGRAPH_UNDIRECTED, no_mutual_edges, NULL);
    print_graph(&square_lattice_graph, "SQUARE LATTICE GRAPH");

    // create ring (cycle) graph with 'num_of_vertices' vertices
    igraph_bool_t circular = 1;
    igraph_ring(&cycle_graph, num_of_vertices, IGRAPH_DIRECTED, no_mutual_edges, circular);
    print_graph(&cycle_graph, "CYCLE GRAPH");

    // create path (simple path) graph with 'num_of_vertices' vertices
    igraph_bool_t not_circular = 0;
    igraph_ring(&simple_path_graph, num_of_vertices, IGRAPH_UNDIRECTED, \
                no_mutual_edges, not_circular);
    print_graph(&simple_path_graph, "PATH GRAPH");

    // create full graph with 'num_of_vertices' vertices
    igraph_full(&full_graph, num_of_vertices, IGRAPH_UNDIRECTED, IGRAPH_NO_LOOPS);
    print_graph(&full_graph, "FULL GRAPH");

    // create random graph using Erdos-Renyi model
    igraph_rng_seed(igraph_rng_default(), (igraph_uint_t)time(0));
    igraph_erdos_renyi_game_gnm(&erdos_renyi_graph, num_of_vertices, 
                                num_of_edges, IGRAPH_UNDIRECTED, IGRAPH_NO_LOOPS);
    print_graph(&erdos_renyi_graph, "ERDOS-RENYI RANDOM GRAPH");

    igraph_matrix_t res;
    igraph_vs_t from, to;
    igraph_vector_t weights;
    igraph_vs_1(&from, 1);
    igraph_vs_1(&to, 6);
    igraph_vector_init(&weights, 12);
    for (int i = 0; i < 12; ++i)
        VECTOR(weights)[i] = igraph_rng_get_integer(igraph_rng_default(), 1, 5);
    igraph_vector_print(&weights);
    igraph_matrix_init(&res, 0, 0);
    
    // get shortest paths between all vertices
    // igraph_distances_dijkstra(&square_lattice_graph, &res, igraph_vss_all(), igraph_vss_all(), &weights, IGRAPH_ALL);
    // get shortest path from vertex to vertex
    // igraph_distances_dijkstra(&square_lattice_graph, &res, from, to, &weights, IGRAPH_ALL);
    // get shortest path from vertex to all vertices
    igraph_distances_dijkstra(&square_lattice_graph, &res, from, igraph_vss_all(), &weights, IGRAPH_ALL);
    printf("DIJKSTRA RESULT\n");
    // printf("FROM %"IGRAPH_PRId " TO %"IGRAPH_PRId "\n", (igraph_integer_t)0, (igraph_integer_t)8);
    printf("FROM %"IGRAPH_PRId " TO ALL\n", (igraph_integer_t)0);
    igraph_matrix_print(&res);

    return 0;
}