#pragma GCC optimize(2)

#include <iostream>
#include <cmath>

#define PI 3.1415926535897932384626

class Complex
{
public:
	double x, y;


	explicit Complex(double a = 0, double b = 0) : x(a), y(b) {}


	void make(double a = 0, double b = 0)
	{
		x = a;
		y = b;
	}


	Complex operator+(Complex b) const
	{
		return Complex(x + b.x, y + b.y);
	}


	Complex operator-(Complex b) const
	{
		return Complex(x - b.x, y - b.y);
	}


	Complex operator*(Complex b) const
	{
		return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
	}
};


inline int ReadInteger()
{
	int x = 0, k = 1;
	int c = getchar();
	while (c > '9' || c < '0')
	{
		if (c == '-')
		{
			k = -1;
		}
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x;
}


void FFT(Complex *t, Complex *ans, int length, int type)
{
	if (length == 1)
	{
		*ans = *t;
		return;
	}
	Complex wn(std::cos(2 * PI / length), type * std::sin(2 * PI / length));
	Complex w(1, 0);
	auto a0 = new Complex[length / 2];
	auto a1 = new Complex[length / 2];
	auto y0 = new Complex[length / 2];
	auto y1 = new Complex[length / 2];
	for (int i = 0; i < length; i += 2)
	{
		a0[i >> 1] = t[i];
		a1[i >> 1] = t[i + 1];
	}
	length >>= 1;
	FFT(a0, y0, length, type);
	FFT(a1, y1, length, type);
	for (int k = 0; k < length; k++)
	{
		ans[k] = y0[k] + w * y1[k];
		ans[k + length] = y0[k] - w * y1[k];
		w = w * wn;
	}
}


int main()
{
	int n = ReadInteger() + 1;

	int length = 1;
	while (length <= n)
	{
		length <<= 1;
	}
	length <<= 1;

	auto a = new Complex[length];
	auto b = new Complex[length];
	auto x = new Complex[length];
	auto y = new Complex[length];
	auto z = new Complex[length];

	for (int i = 0; i < n; i++)
	{
		a[i].make(ReadInteger(), 0);
	}
	for (int i = 0; i < n; i++)
	{
		b[i].make(ReadInteger(), 0);
	}

	FFT(a, x, length, 1);
	FFT(b, y, length, 1);

	for (int i = 0; i < length; i++)
	{
		x[i] = x[i] * y[i];
	}

	FFT(x, z, length, -1);

	int cnt = 2 * n - 1;

	for (int i = 0; i < cnt; i++)
	{
		printf("%d ", int((z[i].x + 0.5)/ length));
	}
	return 0;
}