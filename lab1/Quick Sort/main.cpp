#pragma GCC optimize(2)

#include <cstdio>
#include <random>

class MyClass
{
private:
	int x, y, z;

public:
	explicit MyClass(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {};


	MyClass(MyClass &p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}


	void Swap(MyClass &p)
	{
		std::swap(x, p.x);
		std::swap(y, p.y);
		std::swap(z, p.z);
	}


	void Make(int a, int b, int c)
	{
		x = a;
		y = b;
		z = c;
	}


	void Print() const
	{
		printf("%d %d %d\n", x, y, z);
	}


	bool operator<(MyClass &b) const
	{
		return (x < b.x) || (x == b.x && y < b.y) || (x == b.x && y == b.y && z < b.z);
	}
};


std::random_device rd;
std::default_random_engine rng {rd()};


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
	return x * k;
}


MyClass *Partition(MyClass *st, MyClass *ed)
{
	auto x = new MyClass(*ed);
	auto i = st - 1;
	for (auto p = st; p != ed; p++)
	{
		if (*p < *x)
		{
			i += 1;
			i->Swap(*p);
		}
	}
	i += 1;
	i->Swap(*ed);
	delete x;
	return i;
}


MyClass *RandomPartition(MyClass *st, MyClass *ed)
{
	long k = ed - st;
	std::uniform_int_distribution<long> r(0, k);
	auto i = st + r(rng);
	i->Swap(*ed);
	return Partition(st, ed);
}


void QuickSort(MyClass *st, MyClass *ed)
{
	if (st < ed)
	{
		auto p = RandomPartition(st, ed);
		QuickSort(st, p - 1);
		QuickSort(p + 1, ed);
	}
}


int main()
{
	int n;
	int a, b, c;
	n = ReadInteger();
	auto t = new MyClass[n];
	for (int i = 0; i < n; i++)
	{
		a = ReadInteger();
		b = ReadInteger();
		c = ReadInteger();
		t[i].Make(a, b, c);
	}
	QuickSort(t, t + n - 1);
	for (int i = 0; i < n; i++)
	{
		t[i].Print();
	}
	delete[] t;
	return 0;
}