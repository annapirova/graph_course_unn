import numpy as np
from scipy.sparse import csr_matrix, find
from scipy.io import mmread, mmwrite, mminfo
import gzip


def load_matrix(filename):
    """
    Loads a matrix from a file [mtx, mtx.gz] formats
    """
    return mmread(filename), mminfo(filename)


def save_matrix(matrix, filename):
    """
    Saves a matrix to a file.
    """
    mmwrite(filename, matrix)


def compute_statistics(matrix_info):
    """
    Computes statistics about a matrix.
    """
    row_count = matrix_info[0]
    column_count = matrix_info[1]
    size = row_count * column_count
    nonzero_count = matrix_info[2]
    matrix_format = matrix_info[3]
    matrix_datatype = matrix_info[4]

    nonzero_fraction = nonzero_count / size
    sparsity = 1.0 - nonzero_count / size

    return {
        'row_count': row_count,
        'column_count': column_count,
        'nonzero_count': nonzero_count,
        'size': size,
        'format': matrix_format,
        'data_type': matrix_datatype,
        'nonzero_fraction': nonzero_fraction,
        'sparsity': sparsity
    }


def nnz_per_row(matrix):
    """
    Computes the number of non-zero entries per row.
    """
    return matrix.getnnz(axis=1)


def plot_matrix(matrix):
    """
    Plots a matrix.
    """
    import matplotlib.pyplot as plt
    plt.spy(matrix, markersize=0.5)
    plt.show()


if __name__ == '__main__':

    # parse command line args
    import argparse

    parser = argparse.ArgumentParser(description='Loads a matrix from a file.')
    parser.add_argument('filename', help='the file to load')

    try:
        args = parser.parse_args()
        matrix_file = args.filename
    except IOError as e:
        parser.error(e)
        exit(1)

    # Load the matrix.
    matrix, matrix_info = load_matrix(matrix_file)

    # Compute statistics about the matrix.
    statistics = compute_statistics(matrix_info)

    # Print the statistics.
    print(statistics)

    nnz_per_row = nnz_per_row(matrix)
    # print(nnz_per_row)

    # Plot the matrix.
    plot_matrix(matrix)