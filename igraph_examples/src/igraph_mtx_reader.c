#include "mmio.h"
#include "igraph_mtx_reader.h"

igraph_error_t read_mtx_to_igraph(igraph_t *graph, FILE *instream) {
    int vertex_count, N, edge_count;
    char matcode[4];
    
    if (mm_read_banner(instream, &matcode)) {
        return IGRAPH_PARSEERROR;
    }
    if (mm_read_mtx_crd_size(instream, &vertex_count, &N, &edge_count)) {
        return IGRAPH_PARSEERROR;
    }
    if (mm_is_complex(matcode) || mm_is_array(matcode)) {
        printf("This application doesn't support %s", mm_typecode_to_str(matcode));
        return IGRAPH_PARSEERROR;
    }
    if (N != vertex_count) {
        printf("Is not a square matrix\n");
        return IGRAPH_PARSEERROR;
    }

    igraph_vector_int_t edgelist;
    igraph_vector_int_init(&edgelist, edge_count * 2);
    {
        igraph_integer_t v1, v2;
        igraph_real_t w;
        
        if (mm_is_pattern(matcode))
            for (igraph_integer_t i = 0; i < edge_count; ++i) {
                if (fscanf(instream, "%"IGRAPH_PRId " %"IGRAPH_PRId,
                           &v1, &v2) != 2)
                    return IGRAPH_PARSEERROR;
                VECTOR(edgelist)[2*i]     = v1 - 1;
                VECTOR(edgelist)[2*i + 1] = v2 - 1;
            }
        else {
            for (igraph_integer_t i = 0; i < edge_count; ++i) {
                if (fscanf(instream, "%"IGRAPH_PRId " %"IGRAPH_PRId "%lf", 
                           &v1, &v2, &w) != 3)
                    return IGRAPH_PARSEERROR;
                VECTOR(edgelist)[2*i]     = v1 - 1;
                VECTOR(edgelist)[2*i + 1] = v2 - 1;
            }
        }
    }
    igraph_bool_t is_directed = (mm_is_symmetric(matcode)) ? IGRAPH_UNDIRECTED :
                                                             IGRAPH_DIRECTED;
    igraph_create(graph, &edgelist, vertex_count, is_directed);

    return IGRAPH_SUCCESS;
}
