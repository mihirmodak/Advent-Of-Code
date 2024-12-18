#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

const int DIMENSION = 100;

class Grid {
private:
    const static int dim = DIMENSION;
    std::vector<int> lights;

    // Precomputed neighbor offsets for 1D array traversal
    static const std::array<int, 8> offsets;

public:
    // Default constructor
    Grid() : lights(dim * dim, 0) {}

    // Copy constructor
    Grid(const Grid& other) : lights(other.lights) {}

    // Constructor from file
    Grid(std::ifstream& data) {
        if (!data.is_open()) {
            throw std::runtime_error("No data");
        }

        lights.resize(dim * dim);
        std::string line;
        size_t idx = 0;

        while (std::getline(data, line) && idx < dim * dim) {
            for (char c : line) {
                if (idx < dim * dim) {
                    lights[idx++] = (c == '#') ? 1 : 0;
                }
            }
        }
    }

    // Accessor methods
    int& at(int row, int col) {
        return lights[row * dim + col];
    }

    const int& at(int row, int col) const {
        return lights[row * dim + col];
    }

    // Calculate number of active neighbors for a given cell
    int num_neighbors_on(int row, int col) const {
        int center = row * dim + col;
        int total = 0;

        for (int offset : offsets) {
            int neighbor_idx = center + offset;
            int neighbor_row = neighbor_idx / dim;

            // Bounds checking in a single condition
            bool valid = (neighbor_idx >= 0) &&
                        (neighbor_idx < dim * dim) &&
                        (std::abs(row - neighbor_row) <= 1) &&
                        (std::abs(col - (neighbor_idx % dim)) <= 1);

            total += valid ? lights[neighbor_idx] : 0;
        }
        return total;
    }

    // Perform one simulation step
    void step() {
        std::vector<int> new_lights(dim * dim);
        size_t idx = 0;

        std::transform(
            lights.begin(), lights.end(),
            new_lights.begin(),
            [this, &idx](int current_state) {
                int row = idx / dim;
                int col = idx % dim;
                int neighbors = num_neighbors_on(row, col);
                idx++;

                return (current_state == 1)
                       ? ((neighbors == 2 || neighbors == 3) ? 1 : 0)
                       : (neighbors == 3 ? 1 : 0);
            }
        );

        lights = std::move(new_lights);
    }

    void constant_corner_step() {
        std::vector<int> new_lights(dim * dim);
        size_t idx = 0;

        std::transform(
            lights.begin(), lights.end(),
            new_lights.begin(),
            [this, &idx](int current_state) {
                int row = idx / dim;
                int col = idx % dim;

                // Check if this is a corner light
                bool is_corner = (row == 0 && col == 0) ||                    // Top left
                               (row == 0 && col == dim - 1) ||                // Top right
                               (row == dim - 1 && col == 0) ||                // Bottom left
                               (row == dim - 1 && col == dim - 1);            // Bottom right

                if (is_corner) {
                    idx++;
                    return 1;
                }

                int neighbors = num_neighbors_on(row, col);
                idx++;

                return (current_state == 1)
                       ? ((neighbors == 2 || neighbors == 3) ? 1 : 0)
                       : (neighbors == 3 ? 1 : 0);
            }
        );

        lights = std::move(new_lights);
    }

    // Calculate sum of all active lights
    int matrixSum() const {
        return std::reduce(lights.begin(), lights.end());
    }

    // Print the grid
    void print() const {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                std::cout << (at(i, j) ? '#' : '.') << ' ';
            }
            std::cout << '\n';
        }
        std::cout << std::flush;
    }
};

// Initialize static member
const std::array<int, 8> Grid::offsets = {
    -DIMENSION-1, -DIMENSION, -DIMENSION+1,
    -1,                      +1,
    +DIMENSION-1, +DIMENSION, +DIMENSION+1
};

int simulate(std::ifstream& data, int steps) {
    Grid grid(data);

    for (int step = 0; step < steps; step++) {

        grid.step();
    }

    return grid.matrixSum();
}

int simulate_with_constant_corners(std::ifstream& data, int steps) {
    Grid grid(data);

    // Set the initial states of the corners to be 1
    grid.at(0,0) = 1;
    grid.at(0, DIMENSION-1) = 1;
    grid.at(DIMENSION-1, 0) = 1;
    grid.at(DIMENSION-1, DIMENSION-1) = 1;

    for (int step = 0; step < steps; step++) {
        grid.constant_corner_step();
    }

    return grid.matrixSum();
}


int main() {
    try {
        std::ifstream data("./day18.txt");

        if (!data.is_open()) {
            throw std::runtime_error("Could not open input file");
        }

        // Part 1
        int num_lights_on = simulate(data, 100);
        std::cout << "\nPart 1: final number of lights on = " << num_lights_on << std::endl;

        // reset file to beginning by clearing out eof and fail flags, then seeking to the beginning of the file
        data.clear();
        data.seekg(0);

        // Part 2
        int num_lights_on_with_constant_corners = simulate_with_constant_corners(data, 100);
        std::cout << "\nPart 2: final number of lights on = " << num_lights_on_with_constant_corners << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}