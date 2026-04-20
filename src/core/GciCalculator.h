#ifndef GCI_CALCULATOR_H
#define GCI_CALCULATOR_H

#include <string>

struct GciInput {
    double h1;
    double phi1;
    double h2;
    double phi2;
    double h3;
    double phi3;
};

struct GciOutput {
    double r21;
    double r32;
    double p;
    double phi21ext;
    double phi32ext;
    double e21a;
    double e21ext;
    double GCI21;
    bool success;
    std::string message;
};

class GciCalculator {
public:
    static GciOutput calculate(const GciInput& input);

private:
    static double apparent_order(double r21, double r32, double eps21, double eps32, std::string& warning);
    static short sgn(double x);
};

#endif // GCI_CALCULATOR_H
