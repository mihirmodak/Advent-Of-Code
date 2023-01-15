
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Matrix {
    private:
        int num_rows, num_cols;
        vector<int> values; // save a 2D array as a 1D vector, and use indexing to get elements at (x,y) position


        // overloaded function to translate (x,y) coords to a 1D index
        /*
        Inputs: 
            int x: The x coordinate (0-indexed) of the desired point
            int y: The y coordinate (0-indexed) of the desired point
        Returns:
            int  : the integer index in the values vector of the desired point
        */
        int _calculate_idx(int x, int y) {
            return (x*num_cols)+y;
        }
        int _calculate_idx(int coords[]) {
            int x = coords[0];
            int y = coords[1];
            return (x*num_cols)+y;
        }

    public:
        vector<int> shape;
        int size;

        // constructor
        Matrix(int r, int c) { 
            this->num_rows=r; 
            this->num_cols=c; 
            this->shape={r,c};
            this->values = vector<int> (num_rows*num_cols, 0);
            this->size = values.size();
        }
        
        // Access a single value at a location
        /*
        Matrix.at(4,3) = (4-1)*num_cols + 3
            1  2  3  4  5  (x)   
            • ————————————→
        1 | ————————————>
        2 | ————————————>
        3 | ————————————>
        4 | ——————x
        5 ↓
        (y)
        */
        // at (row, col)
        int at(int x, int y) {
           int idx = _calculate_idx(x,y);
           return values.at( idx );
        }
        // at( (row,col) )
        int at(int coords[]) {
           int idx = _calculate_idx(coords);
           return values.at( idx );
        }

        // Access a set of values
        Matrix slice(int start_coords[], int end_coords[]) {
            int start_idx = _calculate_idx(start_coords);
            int end_idx = _calculate_idx(end_coords);

            auto first = (this->values).begin() + start_idx;
            auto last = (this->values).begin() + end_idx;

            vector<int> subset_values (first, last);

            // Matrix subset (shape[0], shape[1]);
            Matrix subset ( end_coords[0]-start_coords[0]+1, end_coords[1]-start_coords[1]+1 );

            subset.set( subset_values );

            return subset;

        }

        // Print out the whole Matrix
        void show() {
            for (int i = 0; i < size; i++) {
                int curr_elem = values[i];
                if (i % num_cols == 0) {
                    cout << '\n';
                }
                if (curr_elem == 1) {
                    cout << "\x1b[47m" << ' ';
                } else {
                    cout << "\x1b[40m" << ' ';
                }
                // cout << curr_elem << ' ';
            }
            cout << "\x1b[0m" << '\n';
        }

        // Print out the whole unformatted matrix
        void show_raw() {
            for (int elem : values) {
                cout << elem << ' ';
            }
            cout << '\n';
        }

        // Set a single value
        void set(int coords[], int new_value) {
            int idx = _calculate_idx(coords);
            // cout << '(' << coords[0] << ',' << coords[1] << ") -> " << idx << endl;
            values[idx] = new_value;    // Does this destroy the memory containing values[idx] and create a new entry with the new value?
                                        // Or does it simply change where values[idx] points?
        }

        // Set all the values
        void set(vector<int> new_values) { // pass a reference to new_values
            assert (new_values.size() == this->values.size());
            this->values = new_values;
        }

        // Replace the values from a specific start index to an end index
        void replace(int start_coords[], int end_coords[], vector<int> new_values) {
            int start_idx = _calculate_idx(start_coords);
            int end_idx = _calculate_idx(end_coords);

            auto left_first = values.begin();
            auto left_last = values.begin() + start_idx;
            vector<int> left (left_first, left_last);


            auto right_first = values.begin() + end_idx;
            auto right_last = values.end();
            vector<int> right (right_first, right_last);

            left.insert( left.end(), new_values.begin(), new_values.end() );
            left.insert( left.end(), right.begin(), right.end() );

            assert( (this->values).size() == left.size() );
            this->values = left;
        }

};

