#include <cstdio>
#include <cmath>


int a[2000000] = {};


inline int ReadIntegerUnsigned()
{
	int x = 0;
	int c = getchar();
	while (c > '9' || c < '0')
	{
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x;
}


void CountingSort(int *st, int length, int base, int offset)
{
	auto temp = (base >> offset);
	auto c = new int[temp + 1];
	auto b = new int[length];
	for (int i = 0; i <= temp; i++)
	{
		c[i] = 0;
	}
	for (int i = 0; i < length; i++)
	{
		c[((st[i]) & base) >> offset] = c[((st[i]) & base) >> offset] + 1;
	}
	for (int i = 1; i <= temp; i++)
	{
		c[i] = c[i - 1] + c[i];
	}
	for (int i = length - 1; i != -1; i--)
	{
		b[c[((st[i]) & base) >> offset] - 1] = st[i];
		c[((st[i]) & base) >> offset] -= 1;
	}
	for (int i = 0; i < length; i++)
	{
		st[i] = b[i];
	}
	delete[] c;
	delete[] b;
}


void RadixSort(int *st, int length, int base, int bit, int maxn)
{
	for (int i = 0; i <= maxn; i += bit, base <<= bit)
	{
		CountingSort(st, length, base, i);
	}
}


int main()
{
	int n = 0;
	double maxn = 0;
	n = ReadIntegerUnsigned();
	for (int i = 0; i < n; i++)
	{
		a[i] = ReadIntegerUnsigned();
		maxn = std::fmax(maxn, a[i]);
	}
	int r = int(ceil(log2(double(n + 1))));
	maxn = ceil(log2(double(maxn + 1)));
	RadixSort(a, n, (1 << r) - 1, r, maxn);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}