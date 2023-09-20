cmake_minimum_required(VERSION 3.18)
project(igraph_test)

list(APPEND CMAKE_PREFIX_PATH "/common/home/group/slasolver/soft/igraph_install")
find_package(igraph REQUIRED)

add_library(mtx_reader_lib STATIC
            include/igraph_mtx_reader.h
            include/mmio.h
            src/igraph_mtx_reader.c
            src/mmio.c)

include_directories("/common/home/group/slasolver/soft/igraph")
include_directories(include)
link_libraries(igraph::igraph)
link_libraries(mtx_reader_lib)
target_link_libraries(mtx_reader_lib igraph::igraph)
link_directories(build)

add_executable(igraph_test_read_edgelist       src/read_mtx_with_edgelist.c)
add_executable(igraph_example_mtx_reader       src/example_mtx_reader.c)
add_executable(igraph_example_graph_generators src/example_graph_generators.c)
add_executable(igraph_example_sssp     		   src/example_sssp.c)

#target_link_libraries(igraph_example_mtx_reader PUBLIC mtx_reader_lib)
#target_link_libraries(igraph_test_read_edgelist PUBLIC igraph::igraph)
#target_link_libraries(igraph_example_generators PUBLIC igraph::igraph)