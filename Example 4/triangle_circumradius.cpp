#include <iostream>
#include <functional>

// Global variables


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

// Curry function for circumradius calculation
auto calculate_circumradius_curried = [](double a) {
    return [a](double b) {
        return [a, b](double c) {
            double s = (a + b + c) / 2;
            double area = square_root(s * (s - a) * (s - b) * (s - c));
            return (a * b * c) / (4 * area);
        };
    };
};

int main() {
    double a = 3;
    double b = 4;
    double c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    auto circumradius_func = calculate_circumradius_curried(a)(b);
    double circumradius = circumradius_func(c);

    std::cout << "Circumradius: " << circumradius << "\n";

    return 0;
}
