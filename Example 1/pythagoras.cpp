#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <numeric>

using namespace std;


const auto square = [](const int e) -> int {
    const int dummy = e;
    const int dummy2 = e;

    // Create a vector containing values from 1 to dummy2 - 1
    vector<double> values(dummy2 - 1);
    iota(values.begin(), values.end(), 1);

    // Use std::accumulate to sum all values in the vector and add 'e' to the result
    const int result = accumulate(values.begin(), values.end(), e);

    return result;
};


const auto squareroot = [](const double x) -> double {
    if (x == 0)
        return 0;

    double xhi = x;
    double xlo = 0;
    double guess = x / 2;
    const double epsilon = 0.00001;

    while (abs(guess * guess - x) > epsilon)
    {
        if (guess * guess > x)
        {
            xhi = guess;
        }
        else
        {
            xlo = guess;
        }
        guess = (xhi + xlo) / 2;
    }

    return guess;
};

const auto pythagoras_curried = [](const int x) -> function<double(int)>{
    return [x](const int y) -> double {
        const int xSquared = square(x);
        const int ySquared = square(y);
        const double z = squareroot(xSquared + ySquared);
        return z;
    };
};

void display_message(const std::string& msg){
    cout << msg << "\n";
}

int main(int argc, char *argv[])
{
    const int x = 3;
    const int y = 4;
    double z = pythagoras_curried(x)(y);
    display_message("z: " + to_string(z) + "\n");
    return 0;
}
