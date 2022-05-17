// Johnson version
#include <iostream>
#include <vector>
#include <queue>

class Graph
{
private:
	class Edge
	{
	public:
		int to;
		int val;
	public:
		explicit Edge(int _to, int _val = infDis)
		{
			to = _to;
			val = _val;
		}
		~Edge() = default;
	};
	int v;
	bool negative;
	int** dis;
	std::vector<Edge>* edge;
public:
	static constexpr int infDis = 0x0fffffff;
private:
	void BellmanFord()
	{
		dis[0][0] = 0;
		for (int i = 1; i < v; i++)
		{
			for (int j = 0; j < v; j++)
			{
				for (auto& e : edge[j])
				{
					dis[0][e.to] = std::min(dis[0][e.to], dis[0][j] + e.val);
				}
			}
		}
		for (int j = 0; j < v; j++)
		{
			for (auto& e : edge[j])
			{
				if (dis[0][e.to] > dis[0][j] + e.val)
				{
					negative = true;
					return;
				}
			}
		}
	}
	void Dijkstra(int u)
	{
		dis[u][u] = 0;
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> q;
		q.push(std::make_pair(0, u));
		while (!q.empty())
		{
			int p = q.top().second;
			q.pop();
			for (auto& e : edge[p])
			{
				if(dis[u][e.to] > dis[u][p] + e.val)
				{
					dis[u][e.to] = dis[u][p] + e.val;
					q.emplace(dis[u][e.to], e.to);
				}
			}
		}
	}
public:
	explicit Graph(int vv)
	{
		v = vv + 1;
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
		edge = new std::vector<Edge>[v];
	}
	~Graph()
	{
		for (int i = 0; i < v; i++)
		{
			delete[] dis[i];
		}
		delete[] dis;
		delete[] edge;
	}
	void AddEdge(int from, int to, int val)
	{
		edge[from].emplace_back(to, val);
	}
	void SolveDistance()
	{
		for (int i = 1; i < v; i++)
		{
			AddEdge(0, i, 0);
		}
		BellmanFord();
		if (negative)
		{
			return;
		}
		for (int i = 0; i < v; i++)
		{
			for (auto& e : edge[i])
			{
				e.val = e.val + dis[0][i] - dis[0][e.to];
			}
		}
		for (int i = 1; i < v; i++)
		{
			Dijkstra(i);
			for (int j = 1; j < v; j++)
			{
				dis[i][j] = dis[i][j] + dis[0][j] - dis[0][i];
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
	Graph graph(n);
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