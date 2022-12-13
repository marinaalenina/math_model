#include <iostream>
#include <fstream>
#include <vector>
#include<tuple>
#include <math.h>


double function(double x) {
    //return (1 / (1+ std::exp(-x))) - 0.5 ;
    return 2 * std::sin(x) - std::cos(x) * std::cos(x);
    //return x*x - 9;

}

// --------------------------------------------------------------

std::tuple<std::vector<int>, std::vector<double>> nonlinearNewton(double (*function)(double), double start, double error, double h) {

    double x0 = start;
    double fx0 = function(x0);
    int i{ 0 };
    std::vector <int> iteration;
    std::vector<double> result;

    while (std::fabs(fx0) > error) {

        double diff = (function(x0 + h) - fx0) / h;
        x0 = x0 - fx0 / diff;
        fx0 = function(x0);

        iteration.push_back(i);
        result.push_back(x0);
        i++;
    }
    return std::make_tuple(iteration, result);
}


// --------------------------------------------------------------


int main() {
    std::tuple<std::vector<int>, std::vector<double>> result = nonlinearNewton(function, 1.0, 0.000001, 0.001);
    std::vector<int> iter = std::get<0>(result);
    std::vector<double> solution = std::get<1>(result);

    std::ofstream out;
    out.open("data.txt");
    for (int i = 0; i < iter.size(); i++)
        out << iter[i] << "\t" << solution[i] << std::endl;
    //plotNumericalApproach(iter, solution);
    out.close();
    for (auto& i : solution)
        std::cout << i << std::endl;
}