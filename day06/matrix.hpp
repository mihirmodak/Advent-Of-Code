#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Matrix {
    private:
        int m_num_rows, m_num_cols;
        int *mp_shape;
        vector<int> m_values;

        // overloaded function to translate (x,y) coords to a 1D index
        /*
        Inputs: 
            int x: The x coordinate (0-indexed) of the desired point
            int y: The y coordinate (0-indexed) of the desired point
        Returns:
            int  : the integer index in the values vector of the desired point
        */
        int _calculate_1d_idx(int row_idx, int col_idx) {
            return (row_idx * m_num_cols) + col_idx;
        }

    public:

        Matrix(int num_rows_val, int num_cols_val) {
            this->m_num_rows = num_rows_val;
            this->m_num_cols = num_cols_val;
            this->mp_shape = new int[2] {m_num_rows, m_num_cols};
            (this->m_values).assign( m_num_rows*m_num_cols, 0 );
        }

        int * getShape(bool to_print = true) {
            return mp_shape; // return the pointer to the array
        }

        void printShape() {
            cout << '[' << mp_shape[0] << ',' << mp_shape[1] << ']' << endl;
        }

        int getSize() {
            return m_values.size();
        }

        void printSize() {
            cout << to_string( this->getSize() ) << endl;
        }

        vector<int> getValues() {
            return m_values;
        }

        void printValues() {
            for (int i = 0; i < this->getSize(); i++) {
                int curr_elem = m_values[i];

                // if it is at the end of a row, then move to a new line
                if (i % m_num_cols == 0) {
                    cout << '\n';
                }

                cout << curr_elem << ' ';

                // // show black and white squares instead of numbers
                // if (curr_elem == 1) {
                //     // cout << "\x1b[47m" << ' ';  // print white for 1
                // } else  if (curr_elem == 0) {
                //     cout << "\x1b[40m" << ' '; // print black for 0
                // } else {
                //     cout << "\x1b[41m" << ' '; // print red for anything else
                // }
            }
            // cout << "\x1b[0m" << '\n';
            cout << '\n';
        }

        void show() {
            this->printValues();
        }

        vector<int>::iterator begin() {
            return m_values.begin();
        }

        vector<int>::iterator end() {
            return m_values.end();
        }

        void BoolFlip() {
            vector<int> flipped;
            flipped.reserve( this->getSize() );
            // this will convert all the elements of the int array to booleans (0 and 1), but keep the type as an int array
            // cannot invert negative numbers
            for (int i : m_values) {
                if (i >= 1) {
                    flipped.push_back(0);
                } else if (i == 0) {
                    flipped.push_back(1);
                } else {
                    string msg = "The values vector contained a negative number. Negative numbers cannot be inverted."; 
                    throw domain_error(msg);
                }
            }

            this->setSlice(0,0, (m_num_rows)-1, (m_num_cols)-1, flipped);
        }

        vector<int> operator[] (int idx) {
            // index the m_values vector to a specific index
            Matrix sub (1, this->m_num_cols);
            this->getSlice(idx,0, idx,(this->m_num_cols)-1, sub);
            return sub.getValues();
        }

        void setSlice(int startRow, int startCol, int endRow, int endCol, const vector<int>& newValues) {
            // all indices are inclusive

            if(newValues.size() != (endRow-startRow+1)*(endCol-startCol+1)) {
                string msg = "The vector of new values is not the same size as the slice being replaced.\n  Size of matrix slice: " + to_string( (endRow-startRow+1)*(endCol-startCol+1) ) + "\tSize of New Values: " + to_string(newValues.size());
                throw length_error(msg);
            }

            int k = 0;
            for (int i = startRow; i <= endRow; i++) {
                for (int j = startCol; j <= endCol; j++) {
                    int idx = _calculate_1d_idx(i, j);
                    (this->m_values)[idx] = newValues[k++]; // add consecutive values of the vector into the positional indices
                }
            }
        }

        void getSlice(int startRow, int startCol, int endRow, int endCol, Matrix& output) {
            vector<int> sub_vals;
            for (int i = startRow; i <= endRow; i++) {
                for (int j = startCol; j <= endCol; j++) {
                    int idx = _calculate_1d_idx(i, j);
                    sub_vals.push_back(m_values[idx]);
                }
            }

            output.setSlice(0,0, output.getShape()[0]-1, output.getShape()[1]-1, sub_vals);
        }

};

void ones(Matrix& output) {
    // output.printShape();
    vector<int> values (output.getSize(), 1);
    output.setSlice(0, 0, output.getShape()[0]-1,output.getShape()[1]-1, values);
}

void toggle(int startRow, int startCol, int endRow, int endCol, Matrix& m) {
    Matrix sub (endRow-startRow+1, endCol-startCol+1);
    m.getSlice(startRow, startCol, endRow, endCol, sub);

    sub.BoolFlip();

    m.setSlice(startRow, startCol, endRow, endCol, sub.getValues());
}

void on(int startRow, int startCol, int endRow, int endCol, Matrix& m) {
    int new_size = (endRow-startRow+1)*(endCol-startCol+1);
    m.setSlice(startRow, startCol, endRow, endCol, vector<int> (new_size, 1));
}

void off(int startRow, int startCol, int endRow, int endCol, Matrix& m) {
    int new_size = (endRow-startRow+1)*(endCol-startCol+1);
    m.setSlice(startRow, startCol, endRow, endCol, vector<int> (new_size, 0));
}

void adjustBrightness(int adjustment, int startRow, int startCol, int endRow, int endCol, Matrix& m) {
    Matrix sub (endRow-startRow+1, endCol-startCol+1);
    m.getSlice(startRow, startCol, endRow, endCol, sub);

    // for (int i : sub.getValues()) {
    //     cout << i << ' ';
    // } 
    // cout << '\n';

    transform(
        sub.begin(), sub.end(),
        sub.begin(),
        [adjustment] (int val) { if (val+adjustment < 0) { return 0; } else { return val+adjustment; } }
    );

    // for (int i : sub.getValues()) {
    //     cout << i << ' ';
    // } 
    // cout << '\n';

    m.setSlice(startRow, startCol, endRow, endCol, sub.getValues());
}

// int main() {
//     timing::start();

//     Matrix m (9,9);
//     m.show();

//     on(2,2, 6,6, m);
//     m.show();

//     toggle(0,0, 3,3, m);
//     m.show();

//     off(5,5, 8,8, m);
//     m.show();

//     timing::end();

//     system("pause");

//     return 0;
// }