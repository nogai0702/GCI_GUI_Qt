#include "GciCalculator.h"
#include <cmath>

#define N_MAX_ITER 100
#define TOL 1e-8

short GciCalculator::sgn(double x) {
    return (x > 0) - (x < 0);
}

double GciCalculator::apparent_order(double r21, double r32, double eps21, double eps32, std::string& warning) {
    double A = std::log(r21);
    double B = std::log(std::abs(eps32 / eps21));
    double p = std::abs(B) / A;
    double s = sgn(eps32 / eps21);

    double qp;
    double p_new;
    double eps_p = 1;
    unsigned i;

    for (i = 1; (eps_p > TOL) && (i <= N_MAX_ITER); i++) {
        qp = std::log((std::pow(r21, p) - s) / (std::pow(r32, p) - s));
        p_new = std::abs(B + qp) / A;
        eps_p = std::abs((p_new - p) / p_new);
        p = p_new;
    }

    if (i > N_MAX_ITER) {
        warning = "Attention! Maximum iterations reached when calculating apparent order p.";
    }

    return p;
}

GciOutput GciCalculator::calculate(const GciInput& input) {
    GciOutput out;
    out.success = false;

    if (input.h1 <= 0 || input.h2 <= 0 || input.h3 <= 0) {
        out.message = "Error: Representative dimensions (h) must be greater than zero.";
        return out;
    }

    if (std::abs(input.phi2 - input.phi1) < 1e-15) {
        out.message = "Error: Division by zero in apparent order calculation (phi2 - phi1 is zero).";
        return out;
    }

    out.r21 = input.h2 / input.h1;
    double eps21 = input.phi2 - input.phi1;

    out.r32 = input.h3 / input.h2;
    double eps32 = input.phi3 - input.phi2;

    std::string warning;
    out.p = apparent_order(out.r21, out.r32, eps21, eps32, warning);
    out.message = warning;

    double p21 = std::pow(out.r21, out.p);
    double p32 = std::pow(out.r32, out.p);

    if (std::abs(p21 - 1) < 1e-15 || std::abs(p32 - 1) < 1e-15) {
        out.message = "Error: Refinement ratio power resulted in division by zero.";
        return out;
    }

    out.phi21ext = (p21 * input.phi1 - input.phi2) / (p21 - 1);
    out.phi32ext = (p32 * input.phi2 - input.phi3) / (p32 - 1);

    if (std::abs(input.phi1) < 1e-15 || std::abs(out.phi21ext) < 1e-15) {
        out.message = "Error: Division by zero in error calculation.";
        return out;
    }

    out.e21a = std::abs((input.phi1 - input.phi2) / input.phi1);
    out.e21ext = std::abs((out.phi21ext - input.phi1) / out.phi21ext);
    out.GCI21 = 1.25 * out.e21a / (p21 - 1);

    out.success = true;
    return out;
}
