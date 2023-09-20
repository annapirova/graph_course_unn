# https://python.igraph.org/en/stable/tutorials/erdos_renyi.html#sphx-glr-tutorials-erdos-renyi-py
# https://python.igraph.org/en/stable/generation.html
# https://python.igraph.org/en/stable/analysis.html
# https://python.igraph.org/en/stable/api/igraph.GraphBase.html --> search here

import igraph as ig
import random
import matplotlib.pyplot as plt

def graph_print_info(graph):
    ig.summary(graph)
    maxd = ig.Graph.maxdegree(graph)
    mind = min(ig.Graph.degree(graph))
    d = ig.Graph.diameter(graph)
    pl = ig.Graph.average_path_length(graph)
    # betw = ig.Graph.betweenness(graph)
    print(maxd, mind, d, pl)

# https://python.igraph.org/en/stable/tutorial.html#layouts-and-plotting
def plot_graph(graph, mylayout="circle", name="graph"):
    fig, ax = plt.subplots()
    ig.plot(
        graph,
        target=ax,
        layout=mylayout,
        vertex_color="lightblue",
        vertex_size=0.15
    )
    plt.show()
    fig.savefig(name+".png")


# %%
# First, we set a random seed for reproducibility
random.seed(0)

# %%
# Then, we generate two :math:`G(n,p)` Erdős–Rényi graphs with identical parameters:
# g1 = ig.Graph.Erdos_Renyi(n=15, p=0.4, directed=False, loops=False)
# g2 = ig.Graph.Erdos_Renyi(n=25, p=0.2, directed=False, loops=False)

g1 = ig.Graph.GRG(n=15, radius=0.3)
g2 = ig.Graph.GRG(n=15, radius=0.4)

#g3 = ig.Graph.Barabasi(n=15, m=10)

graph_print_info(g1)
graph_print_info(g2)
#graph_print_info(g3)

# draw graph
plot_graph(g1, name="er1")
plot_graph(g2, name="er2")
#plot_graph(g3, mylayout="kk", name="ba1")

#save graph
# g1.write_edgelist("er1.el")

import scipy.io as sio
a_mat = g1.get_adjacency_sparse() # a_mat is scipy.sparse.csr_matrix
plt.spy(a_mat)
plt.show()
b_mat = g2.get_adjacency_sparse() # a_mat is scipy.sparse.csr_matrix
plt.spy(b_mat)
plt.show()
#c_mat = g3.get_adjacency_sparse() # a_mat is scipy.sparse.csr_matrix
#plt.spy(c_mat)
#plt.show()

# sio.mmwrite("g1.mtx", a_mat, field='pattern', symmetry = 'symmetric')
# a_mat = sp.coo_matrix()