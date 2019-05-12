#include "stdafx.h"
#include <vector>
#include <complex>
#include <cmath>

using namespace std;
#define Complex complex<double>

Complex delta2(double Step, Complex PsiFirst, Complex PsiSecond, Complex PsiThird);
Complex AK(double timeStep, double Step);
Complex BK(double timeStep, double Step);
Complex CK(double timeStep, double Step, double Pot);
Complex DK(double timeStep, Complex Psi, Complex delta2PsiX, Complex delta2PsiY, double Pot);



Complex ak(Complex alfa, Complex A, Complex B, Complex C);
Complex bk(Complex alfa, Complex beta, Complex A, Complex C, Complex D);
void fur(vector <Complex> &data, int is);
