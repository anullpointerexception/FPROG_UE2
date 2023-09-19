#include <iostream>
#include <cmath>
#include <functional>

// Lambda for the square function
auto silly_square = [](double x) { return x * x; };

// Lambda for the square root function
auto square_root = [](double x, double epsilon = 1e-10, int max_iterations = 1000) {
    if (x < 0) {
        return -1.0; // Corrected to return a double for invalid input
    }
    if (x == 0) {
        return 0.0;
    }

    double low = 0, high = x;
    double mid;
    for (int i = 0; i < max_iterations; ++i) {
        mid = (low + high) / 2.0;
        double mid_square = mid * mid;

        if (mid_square > x) {
            high = mid;
        } else if (mid_square < x) {
            low = mid;
        }

        if (high - low < epsilon) {
            break;
        }
    }

    return mid;
};

// Curried function to calculate median
std::function<std::function<std::function<double(double)>(double)>(double)> calculate_median_curried =
    [](double a) {
        return [a](double b) {
            return [a, b](double c) {
                double a_square = silly_square(a);
                double b_square = silly_square(b);
                double c_square = silly_square(c);

                return 0.5 * square_root(2 * (b_square + c_square) - silly_square(a));
            };
        };
    };

int main() {
    double a = 3;
    double b = 4;
    double c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    // Curry the calculate_median function and use it
    auto median_func = calculate_median_curried(a)(b);
    double median_a = median_func(c);

    a = 4;
    b = 3;
    c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    // Curry the calculate_median function again and use it
    median_func = calculate_median_curried(a)(b);
    double median_b = median_func(c);

    a = 5;
    b = 3;
    c = 4;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    // Curry the calculate_median function once more and use it
    median_func = calculate_median_curried(a)(b);
    double median_c = median_func(c);

    std::cout << "Medians:\n";
    std::cout << "Median from vertex A: " << median_a << "\n";
    std::cout << "Median from vertex B: " << median_b << "\n";
    std::cout << "Median from vertex C: " << median_c << "\n";

    return 0;
}
