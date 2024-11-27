#include <iostream>
#include <cmath>
#include <functional>
#include <limits>
#include <vector>
#include "Eigen/Dense"
#include <gsl/gsl_integration.h>

using namespace std;

vector<double> linspace(double lower_bound, double upper_bound, double increment) {


    vector<double> result;
    
    // Ensure increment is non-zero to avoid division by zero
    if (increment == 0) {
        std::cerr << "Error: Increment cannot be zero.\n";
        return result;
    }
    
    // Calculate the number of elements in the vector
    int num_elements = static_cast<int>((upper_bound - lower_bound) / increment) + 1;
    cout << "Generating linspace: " << lower_bound << " - " << upper_bound << " with increment = " << increment << " and " << num_elements << " elements."<< endl;
    
    // Generate the linearly spaced vector
    for (int i = 0; i < num_elements; ++i) {

        double value = lower_bound + i * increment;
        result.push_back(value);
    }
    
    return result;
}
vector<double> linspace(double lower_bound, double upper_bound, int num_elements) {
    double increment = (upper_bound - lower_bound) / (num_elements-1);
    return linspace(lower_bound, upper_bound, increment);
}

typedef function<double(double)> Func;
typedef function<double(Func, double)> Derivative;

namespace SingleVar {
    double derivative(Func f, double x) {
        double h = sqrt(numeric_limits<double>::epsilon());
        return (f(x + h) - f(x - h)) / (2.0 * h);
    }

    double integration(Func f, double a, double b, int num_steps = 1000) {

        num_steps = max(num_steps, 1000); // num_steps must be at least 1000

        double h = (b - a) / num_steps;
        double sum = (f(a) + f(b)) / 2.0; // initial sum is the mean of the y values at the lower & upper limit ?
        
        for (int i = 1; i < num_steps; ++i) {
            double x = a + i * h;
            sum += f(x);
            cout << x << " " << f(x) << endl;
        }
        
        return sum * h;
    }
};

typedef function<double(const vector<double>&)> MultiVarFunc;

namespace MultiVar {
    double partial_derivative(MultiVarFunc f, const vector<double>& x, int var_index) {
        double h = sqrt(numeric_limits<double>::epsilon());
        vector<double> x_plus_h = x;
        vector<double> x_minus_h = x;

        x_plus_h[var_index] += h;
        x_minus_h[var_index] -= h;

        return (f(x_plus_h) - f(x_minus_h)) / (2.0 * h);
    }

    double partial_integration1(MultiVarFunc f, const vector<double> & lower_limits, const vector<double> & upper_limits, int num_steps = 1000) {
        int num_dimensions = lower_limits.size();
        vector<double> step_sizes(num_dimensions);

        vector<double> partial_sums(num_dimensions, 0.0);

        for (int i = 0; i < num_dimensions; ++i) {
            step_sizes[i] = (upper_limits[i] - lower_limits[i]) / num_steps;
        }

        vector<double> current_point = lower_limits;

        for (int i = 0; i < num_steps; ++i) {
            for (int j = 0; j < num_dimensions; ++j) {
                current_point[j] += step_sizes[j];
                partial_sums[j] += f(current_point);
            }
        }

        double result = 1.0;
        for (int i = 0; i < num_dimensions; ++i) {
            result *= partial_sums[i] * step_sizes[i];
        }

        return result;
    }

    double partial_integration2(MultiVarFunc f, const vector<double> & lower_limits, const vector<double> & upper_limits, int num_steps = 1000) {
        num_steps = max(num_steps, 1000);   // num_steps must be at least 1000
        size_t num_dimensions = lower_limits.size();
        
        vector<vector<double>> ranges (num_dimensions, vector<double>(num_steps));
        double h;

        for (size_t dim=0; dim < num_dimensions; dim++) {
            ranges[dim] = ( linspace(lower_limits[dim], upper_limits[dim], num_steps) );
            h = (upper_limits[dim] - lower_limits[dim]) / num_steps;
        }

        vector<double> variables_subset;
        variables_subset.reserve(num_dimensions);
        double sum = 0.0;
        for (int step=0; step < num_steps; step++) {


            // Re-generate the variables subset from linspace ranges
            variables_subset.clear();
            for (vector<double> range : ranges) {
                variables_subset.push_back(range[step]);
            }

            cout << variables_subset[0] << " " << variables_subset[1] << " " << f(variables_subset) << endl;

            sum += f(variables_subset);

        }

        cout << "\n";
        return sum*h;

    }
};


double roots(Func f, double x0, double precision) {
    double x = x0;
    Derivative d = SingleVar::derivative;
    for (size_t i = 0;; i++) {
        x = x - (f(x) / d(f, x));

        if (abs(f(x)) < precision) {
            return x;
        }
    }
}




int main() {
    // Func fibbonaci = [] (double x) -> double {return pow(x, 3) + 2.0 * pow(x, 2) + 10.0 * x - 20.0;};
    // Func linear = [] (double x) -> double {return x;};
    // Func sine = [] (double x) -> double {return sin(x);};

    // // Single Variable Derivative Test
    // string value_str;
    // cout << "Enter the value to calculate the derivative at: ";
    // cin >> value_str;
    // double value = stod(value_str);
    // cout << SingleVar::derivative(sine, value) << "\n"; 

    // // Single Variable Integration Test
    // cout << SingleVar::integration(sine, 0, M_PI/2) << endl;  

    // Multi Variable Functions
    MultiVarFunc polynomial = [] (const vector<double> & variables) -> double {
        double x = variables[0];
        double y = variables[1];

        return pow(x+3, 2) + pow(y-2, 2) - 1;  // equation of circle
    };  
    MultiVarFunc threeVarPolynomial = [] (const vector<double> & variables) -> double {
        double x = variables[0];
        double y = variables[1];
        double z = variables[2];

        return pow(x+3, 2) + pow(y-2, 2) - pow(2*z, 3);  
    };  
    MultiVarFunc trig = [] (const vector<double> & variables) -> double {
        double x = variables[0];
        double y = variables[1];

        return sin(x) * cos(y);
    };
    // vector<double> variables = {M_PI/4, M_PI};
    // cout << MultiVar::partial_derivative(trig, variables, 0) << endl;

    // Multi Variable Partial Integration
    vector<double> lower_limits = {0.0, 0.0, 0.0};
    vector<double> upper_limits = {1.0, 2.0, 5.0};
    cout << MultiVar::partial_integration2(threeVarPolynomial, lower_limits, upper_limits) << endl;
}