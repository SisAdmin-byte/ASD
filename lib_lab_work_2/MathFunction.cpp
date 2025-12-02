#include "MathFunction.h"
double pi = 3.141592653589;
namespace MathFunctions {

    double Sin(double x) { return sin(x * pi / 180); }
    double Cos(double x) { return cos(x * pi / 180); }
    double tg(double x) { return tan(x * pi / 180); }
    double ln(double x) { return log(x); }
    double Exp(double x) { return exp(x); }
    double ABS(double x) { return fabs(x); }
    double Sqrt(double x) { return sqrt(x); }

}