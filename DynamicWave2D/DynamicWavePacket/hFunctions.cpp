#include "stdafx.h"
#include "hFunctions.h"
using namespace std;


Complex proizv(double Step, Complex PsiFirst, Complex PsiSecond, Complex PsiThird)
{
	return (1.0 / Step / Step)*(PsiThird - 2.0*PsiSecond + PsiFirst);
}

Complex A(double timeStep, double Step)
{
	return -Complex(0, 1)*timeStep / (2 * Step*Step);
}
Complex B(double timeStep, double Step)
{
	/*Complex X;
	X.real = 0;
	X.image = -timeStep / (2 * Step*Step);
	return X;*/
	return -Complex(0, 1) * timeStep / (2 * Step * Step);
}
Complex C(double timeStep, double Step, double Pot)
{

	return (1. + Complex(0, 1)*timeStep*Pot / 2. + Complex(0, 1)*(timeStep / (2 * Step))*(2. / Step));
}
Complex D(double timeStep, double Step, Complex Psi, Complex delta2Psi, double Pot)
{

	return Psi + Complex(0, 1)*(timeStep / 2)*(delta2Psi - Pot * Psi);;
}

Complex ak(Complex alfa, Complex A, Complex B, Complex C)
{
	
	if (C + A * alfa == 0.) return 0.;
	else return -(B / (C + A*alfa));

}
Complex bk(Complex alfa, Complex beta, Complex A, Complex C, Complex D)
{
	if (C + A * alfa == 0.) return 0.;
	else return (D - A * beta) / (C + A * alfa);
}
void fur(vector <Complex> &data, int is, int size)
{

	int i, j, istep, n;
	n = size;
	int m, mmax;
	double r, r1, theta, w_r, w_i, temp_r, temp_i;
	double pi = 3.1415926f;

	r = pi * is;
	j = 0;
	for (i = 0; i < n; i++)
	{
		if (i < j)
		{

			temp_r = data[j].real();
			temp_i = data[j].imag();
			data[j] = data[i];
			data[i] = temp_r + Complex(0, 1) * temp_i;
		}
		m = n >> 1;
		while (j >= m) { j -= m; m = (m + 1) / 2; }
		j += m;
	}
	mmax = 1;
	while (mmax < n)
	{
		istep = mmax << 1;
		r1 = r / (double)mmax;
		for (m = 0; m < mmax; m++)
		{
			theta = r1 * m;
			w_r = (double)cos((double)theta);
			w_i = (double)sin((double)theta);
			for (i = m; i < n; i += istep)
			{
				j = i + mmax;
				temp_r = w_r * data[j].real() - w_i * data[j].imag();
				temp_i = w_r * data[j].imag() + w_i * data[j].real();
				data[j] = (data[i].real() - temp_r) + Complex(0, 1)*(data[i].imag() - temp_i);
				data[i] += (temp_r) + Complex(0, 1)*(temp_i);
			}
		}
		mmax = istep;
	}
	if (is > 0)
	for (i = 0; i < n; i++)
	{
		data[i] /= (double)n;
	}
}
