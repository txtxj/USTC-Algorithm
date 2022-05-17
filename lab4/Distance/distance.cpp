#include <iostream>
#include <vector>

class Graph
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
		~Edge() = default;
	};
	int v;
	int e;
	bool negative;
	int** dis;
public:
	static constexpr int infDis = 0x0fffffff;
	Graph(int vv, int ee)
	{
		v = vv + 1;
		e = ee;
		negative = false;
		dis = new int*[v];
		for (int i = 0; i < v; i++)
		{
			dis[i] = new int[v];
			for (int j = 0; j < v; j++)
			{
				dis[i][j] = infDis;
			}
		}
	}
	~Graph()
	{
		for (int i = 0; i < v; i++)
		{
			delete[] dis[i];
		}
		delete[] dis;
	}
	void AddEdge(int from, int to, int val)
	{
		dis[from][to] = val;
	}
	void SolveDistance()
	{
		for (int k = 1; k < v; k++)
		{
			for (int i = 1; i < v; i++)
			{
				for (int j = 1; j < v; j++)
				{
					dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
				}
			}
		}
		for (int k = 1; k < v; k++)
		{
			for (int i = 1; i < v; i++)
			{
				for (int j = 1; j < v; j++)
				{
					if (dis[i][j] > dis[i][k] + dis[k][j])
					{
						negative = true;
					}
				}
			}
		}
	}
	int Distance(int from, int to)
	{
		return dis[from][to];
	}
	bool IsNegative() const
	{
		return negative;
	}
};

int main()
{
	int n, m, u, v, w, q;
	std::cin >> n >> m;
	Graph graph(n, m);
	for (int i = 0; i < m; i++)
	{
		std::cin >> u >> v >> w;
		graph.AddEdge(u, v, w);
	}
	graph.SolveDistance();
	if (graph.IsNegative())
	{
		std::cout << "negative-weight cycle" << std::endl;
		return 0;
	}
	std::cin >> q;
	for (int i = 0; i < q; i++)
	{
		std::cin >> u >> v;
		std::cout << graph.Distance(u, v) << std::endl;
	}
	return 0;
}