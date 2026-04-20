#include "src/core/GciCalculator.h"
#include <iostream>
#include <iomanip>

int main() {
    GciInput in;
    // Test values:
    in.h1 = 1.0; in.phi1 = 6.063;
    in.h2 = 2.0; in.phi2 = 5.972;
    in.h3 = 4.0; in.phi3 = 5.863;

    GciOutput out = GciCalculator::calculate(in);

    if (!out.success) {
        std::cerr << "Calc failed: " << out.message << std::endl;
        return 1;
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "r21: " << out.r21 << "\n";
    std::cout << "r32: " << out.r32 << "\n";
    std::cout << "p:   " << out.p << "\n";
    std::cout << "phi21ext: " << out.phi21ext << "\n";
    std::cout << "phi32ext: " << out.phi32ext << "\n";
    std::cout << "e21a: " << out.e21a * 100 << "%\n";
    std::cout << "e21ext: " << out.e21ext * 100 << "%\n";
    std::cout << "GCI21: " << out.GCI21 * 100 << "%\n";

    return 0;
}
