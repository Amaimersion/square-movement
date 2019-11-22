#include <iostream>


struct Matrix {
    int** matrix;
    const unsigned int size;
};

struct Index {
    unsigned int i;
    unsigned int j;
};


void print_matrix(
    const Matrix matrix
);

void swap(
    const Matrix matrix,
    const Index index_1,
    const Index index_2
);

void shift_layers(
    const Matrix matrix,
    const unsigned int steps,
    const bool print
);

void shift_layer(
    const Matrix matrix,
    const Index start_index,
    const Index end_index
);


int main()
{
    unsigned int n = 0;

    std::cout << "Enter n: ";
    std::cin >> n;
    std::cout << std::endl;

    int **matrix = new int*[n];

    for (unsigned int i = 0; i != n; i++) {
        matrix[i] = new int[n];

        for (unsigned int j = 0; j != n; j++) {
            std::cout << "Enter M (" << i + 1 << ", " << j + 1 << "): ";
            std::cin >> matrix[i][j];
        }
    }

    unsigned int k = 0;

    std::cout << "\nEnter k: ";
    std::cin >> k;
    std::cout << std::endl;

    shift_layers(
        {matrix: matrix, size: n}, 
        k, 
        true
    );

    for (unsigned int i = 0; i != n; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;

    return 0;
}


void print_matrix(
    const Matrix matrix
) {
    for (unsigned int i = 0; i != matrix.size; i++) {
        for (unsigned int j = 0; j != matrix.size; j++) {
            std::cout << matrix.matrix[i][j] << ' ';
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}


void swap(
    const Matrix matrix,
    const Index index_1,
    const Index index_2
) {
    const int temp = matrix.matrix[index_1.i][index_1.j];
    matrix.matrix[index_1.i][index_1.j] = matrix.matrix[index_2.i][index_2.j];
    matrix.matrix[index_2.i][index_2.j] = temp;
}


void shift_layers(
    const Matrix matrix,
    const unsigned int steps,
    const bool print
) {
    if (print) {
        print_matrix(matrix);
    }

    for (unsigned int i = 0; i != steps; i++) {
        Index start = {
            i: 0, 
            j: 0
        }, end = {
            i: matrix.size - 1, 
            j: matrix.size - 1
        };

        for (unsigned int j = 0; j != matrix.size / 2; j++) {
            shift_layer(matrix, start, end);

            start.i += 1;
            start.j += 1;
            end.i -= 1;
            end.j -= 1;
        }

        if (print) {
            print_matrix(matrix);
        }
    }
}


void shift_layer(
    const Matrix matrix,
    const Index start,
    const Index end
) {
    if (
        (start.i == end.i) &&
        (start.j == end.j)
    ) {
        return;
    }

    Index current = start;
    bool on = true, row = false, increase = true;

    while (on) {
        if (row) {
            if (increase) {
                current.i++;

                if (current.i == end.i) {
                    row = false;
                    increase = false;
                }
            } else {
                current.i--;

                if (current.i == start.i) {
                    on = false;
                }
            }
        } else {
            if (increase) {
                current.j++;

                if (current.j == end.j) {
                    row = true;
                }
            } else {
                current.j--;

                if (current.j == start.j) {
                    row = true;
                    increase = false;
                }
            }
        }

        swap(matrix, start, current);
    }
}
