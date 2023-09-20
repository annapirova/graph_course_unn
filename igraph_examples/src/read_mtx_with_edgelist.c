#include <stdio.h>
#include <stdlib.h>
#include <igraph.h>

int main(int argc, char *argv[]) {
    if (argc < 2)
        return -1;
    igraph_t graph;
    
    FILE *istr = fopen(argv[1], "r");
    if (!istr)
        return -2;
    igraph_error_t read_error_code = igraph_read_graph_edgelist(&graph, istr, 0, IGRAPH_UNDIRECTED);
    if (read_error_code == IGRAPH_PARSEERROR)
        printf("Failed to read graph from file.\n");
    printf("Read graph successfully\n");
    fclose(istr);

    printf("%" IGRAPH_PRId " %" IGRAPH_PRId "\n", igraph_vcount(&graph), igraph_ecount(&graph));
    igraph_write_graph_edgelist(&graph, stdout);
    igraph_destroy(&graph);
    return 0;
}
