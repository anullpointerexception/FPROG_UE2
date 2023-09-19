#include <iostream>

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

// Curry function for area and radii calculation
auto calculate_area_and_radii_curried = [](double a) {
    return [a](double b) {
        return [a, b](double c) {
            double s = (a + b + c) / 2;
            double area = square_root(s * (s - a) * (s - b) * (s - c));
            double inradius = area / s;
            double circumradius = (a * b * c) / (4 * area);
            return std::make_tuple(area, inradius, circumradius);
        };
    };
};


// Curry function for distance calculation
auto calculate_distance_curried = [](double circumradius) {
    return [circumradius](double inradius) {
        double distance = square_root(circumradius * circumradius - 2 * circumradius * inradius);
        return distance;
    };
};

int main() {
    double a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    // Curry the calculate_area_and_radii_curried function and use it
    auto area_radii_func = calculate_area_and_radii_curried(a)(b);
    auto result = area_radii_func(c);
    double area = std::get<0>(result);
    double inradius = std::get<1>(result);
    double circumradius = std::get<2>(result);

    std::cout << "Inradius: " << inradius << "\n";
    std::cout << "Circumradius: " << circumradius << "\n";

    // Curry the calculate_distance_curried function and use it
    auto distance_func = calculate_distance_curried(circumradius)(inradius);
    double distance = distance_func;

    std::cout << "Distance between circumcenter and incenter: " << distance << "\n";

    return 0;
}
