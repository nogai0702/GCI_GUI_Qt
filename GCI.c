/******************************************************************************
*
* GCI.c
*
* Program de calcul al indicelui de convergență al unei rețele utilizate
* pentru simularea numerică a unui proces de transfer de căldură și masă.
* Programul mai calculează eroarea relativă aproximativă și eroarea relativă
* extrapolată.
*
* Procedura de calcul este cea prezentată de Celik ș.a. (2008).
*
* Autor: Andrei Dragomirescu
*
******************************************************************************/

#include "GCI.h"
#include <math.h>
#include <stdio.h>

// Dimensiune buffer pentru intrări de la tastatură:
#define BUF_SIZE 256

// Numărul maxim de iterații pentru calculul ordinului aparent al metodei:
#define N_MAX_ITER 100

// Diferența relativă maximă admisă între ordinul aparent de la iterația curentă
// și cel de la iterația anterioară:
#define TOL 1e-8

//================================================================== FUNCȚII ===

double get_double(const char *prompt)
{
/*
* Citește de la tastatură și returnează o valoare double.
*
* Argumente:
* ~~~~~~~~~
* prompt: char*
* Mesajul afișat pentru introducerea valorii.
*
* Returnează:
* ~~~~~~~~~~
* double:
* Valoarea citită.
*/

char str_buf[BUF_SIZE + 1];
double val;
int ok;

do
{
printf("%s", prompt);
fgets(str_buf, BUF_SIZE, stdin);
ok = (sscanf(str_buf, "%lf", &val) == 1);
if (!ok)
puts("EROARE: Valoare introdusă greșit.");
}
while (!ok);

return val;
}


short sgn(double x)
{
/*
* Funcția sgn(x).
*
* Argumente:
* ~~~~~~~~~
* x: double
* Valoarea pentru care se determină semnul.
*
* Returnează:
* ~~~~~~~~~~
* short:
* Semnul lui x.
*/

return (x > 0) - (x < 0);
}


double apparent_order(double r21, double r32, double eps21, double eps32)
{
/*
* Calculează ordinul aparent al metodei.
*
* Argumente:
* ~~~~~~~~~
* r21: double
* Raportul h_2/h_1.
* r32: double
* Raportul h_3/h_2.
* eps21: double
* Diferența ϕ_2 - ϕ_1.
* eps32: double
* Diferența ϕ_3 - ϕ_2.
*
* Returnează:
* ~~~~~~~~~~
* double:
* Ordinul aparent al metodei.
*/

double A = log(r21);
double B = log(fabs(eps32/eps21));
double p = fabs(B)/A;
double s = sgn(eps32/eps21);

double qp;
double p_new;

double eps_p = 1;
unsigned i;

for (i = 1; (eps_p > TOL) && (i <= N_MAX_ITER); i++)
{
qp = log((pow(r21, p) - s)/(pow(r32, p) - s));
p_new = fabs(B + qp)/A;
eps_p = fabs((p_new - p)/p_new);
p = p_new;
}

if (i > N_MAX_ITER)
{
puts("");
puts("ATENȚIE!");
puts(" S-a depășit numărul maxim de iterații");
puts(" la calcularea ordinului aparent p.");
}

return p;
}

//===================================================================== MAIN ===

int main()
{
puts("");
puts("CALCULUL INDICELUI DE CONVERGENȚĂ AL REȚELEI DE CALCUL");

puts("");
puts("1. Datele rețelei FINE");
puts("");
puts("Dimensiunea reprezentativă:");
double h1 = get_double(" h_1 = ");
puts("Valoarea parametrului de interes:");
double phi1 = get_double(" ϕ_1 = ");

puts("");
puts("2. Datele rețelei MEDII");
puts("");
puts("Dimensiunea reprezentativă:");
double h2 = get_double(" h_2 = ");
puts("Valoarea parametrului de interes:");
double phi2 = get_double(" ϕ_2 = ");

puts("");
puts("3. Datele rețelei GROSIERE");
puts("");
puts("Dimensiunea reprezentativă:");
double h3 = get_double(" h_3 = ");
puts("Valoarea parametrului de interes:");
double phi3 = get_double(" ϕ_3 = ");

double r21 = h2/h1;
double eps21 = phi2 - phi1;

double r32 = h3/h2;
double eps32 = phi3 - phi2;

double p = apparent_order(r21, r32, eps21, eps32);

double phi21ext = (pow(r21, p)*phi1 - phi2)/(pow(r21, p) - 1);
double phi32ext = (pow(r32, p)*phi2 - phi3)/(pow(r32, p) - 1);

double e21a = fabs((phi1 - phi2)/phi1);
double e21ext = fabs((phi21ext - phi1)/phi21ext);
double GCI21 = 1.25*e21a/(pow(r21, p) - 1);

puts("");
puts("REZULTATE");
puts("");
puts("Factorii de rafinare ai rețelelor:");
printf(" r_21 = %.4g\n", r21);
printf(" r_32 = %.4g\n", r32);
puts("");
puts("Ordinul aparent al metodei:");
printf(" p = %.4g\n", p);
puts("");
puts("Valorile extrapolate ale parametrului de interes:");
printf(" ϕ²¹_ext = %.4g\n", phi21ext);
printf(" ϕ³²_ext = %.4g\n", phi32ext);
puts("");
puts("Eroarea relativă aproximativă:");
printf(" e²¹_a = %.2f%%\n", e21a*100);
puts("");
puts("Eroarea relativă extrapolată:");
printf(" e²¹_ext = %.2f%%\n", e21ext*100);
puts("");
puts("Indicele de convergență al rețelei fine:");
printf(" GCI²¹ = %.2f%%\n", GCI21*100);

return 0;
}
