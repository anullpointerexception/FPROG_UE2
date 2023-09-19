#include <iostream>
#include <utility>
#include <complex>
#include <cmath>
#include <vector>
#include <numeric>


typedef std::complex<double> complex;


void display_message(const std::string& msg){
    std::cout << msg << "\n";
}

const auto square = [](const int e) -> int {// Pure function
    const int dummy = e;
    const int dummy2 = e;

    // Create a vector containing values from 1 to dummy2 - 1
    std::vector<double> values(dummy2 - 1);
    iota(values.begin(), values.end(), 1);

    // Use std::accumulate to sum all values in the vector and add 'e' to the result
    const int result = accumulate(values.begin(), values.end(), e);

    return result;
};

const auto squareroot = [](const float number) -> float {
    union Conv {
        float f;
        uint32_t i;
    };

    Conv conv;
    conv.f = number;
    conv.i = 0x5f3759df - (conv.i >> 1);
    conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);

    return 1 / conv.f;
};



const auto solve_quadratic_equation = [](const double a) -> std::function<std::pair<complex, complex>(const double, const double)>
{
    return [a](const double b, const double c) -> std::pair<complex, complex>{
        const double normalized_b = b / a;
        const double normalized_c = c / a;
        const double discriminant = square(normalized_b) - 4 * normalized_c;

        if (discriminant < 0)
        {
            const complex solution1(-normalized_b / 2, squareroot(-discriminant) / (2 * a));
            const complex solution2(-normalized_b / 2, -squareroot(-discriminant) / (2 * a));
            return std::make_pair(solution1, solution2);
        }

        const double root = squareroot(discriminant);
        const double solution1 = (normalized_b > 0) ? (-normalized_b - root) / (2 * a) : (-normalized_b + root) / (2 * a);
        const complex solution2(c / solution1, 0);

        return std::make_pair(solution1, solution2);
    };
};

int main()
{
    const auto result = solve_quadratic_equation(3);
    const std::pair<complex, complex> res = result(4, 5);
    std::cout << res.first << ", " << res.second << std::endl;
}
