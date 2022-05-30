#include <iostream>
#include <iomanip>
#include <vector>

class Solution
{
private:
	class Edge
	{
	public:
		int to;
		int val;
	public:
		Edge(int _to, int _val)
		{
			to = _to;
			val = _val;
		}
	};
	int v;
	std::vector<Edge>* edge;

public:
	explicit Solution(int n)
	{
		v = n;
		edge = new std::vector<Edge>[v + 1];
	}
	~Solution()
	{
		delete[] edge;
	}
	void AddEdge(int from, int to, int val)
	{
		edge[from].emplace_back(to, val);
	}
	float Solve()
	{
		return (float)edge[0][0].val / (float)v;
	}
};

int main()
{
	int n, e, u, v, w;
	std::cin >> n >> e;
	Solution solution(n);
	for (int i = 0; i < e; i++)
	{
		std::cin >> u >> v >> w;
		solution.AddEdge(u, v, w);
	}
	std::cout << std::fixed << std::setprecision(3) << solution.Solve();
	return 0;
}