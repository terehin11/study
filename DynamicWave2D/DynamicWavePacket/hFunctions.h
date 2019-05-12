#include "stdafx.h"
#include <vector>
#include <complex>
#include <cmath>

using namespace std;
#define Complex complex<double>

//Complex delta1(double Step, Complex PsiFirst, Complex PsiSecond);
Complex proizv(double Step, Complex PsiFirst, Complex PsiSecond, Complex PsiThird);
Complex A(double timeStep, double Step);
Complex B(double timeStep, double Step);
Complex C(double timeStep, double Step, double Pot);
Complex D(double timeStep, double Step, Complex Psi, Complex delta2Psi, double Pot);
Complex ak(Complex alfa, Complex A, Complex B, Complex C);
Complex bk(Complex alfa, Complex beta, Complex A, Complex C, Complex D);
void fur(vector <Complex> &data, int is, int size);
