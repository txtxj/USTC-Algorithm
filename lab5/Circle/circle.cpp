#include <iostream>
#include <iomanip>
#include <vector>

class Graph
{
private:
	class Edge
	{
	public:
		int to;
		int val;
		static constexpr int maxVal = 0x3fffffff;
	public:
		Edge(int _to, int _val)
		{
			to = _to;
			val = _val;
		}
	};
	int v;
	std::vector<Edge>* edge;
	int** dp;
private:
	void CalPath()
	{
		for (int i = 1; i < v; i++)
		{
			AddEdge(0, i, 0);
		}
		for (int i = 0; i < v; i++)
		{
			for (int j = 0; j < v; j++)
			{
				dp[i][j] = Edge::maxVal;
			}
		}
		dp[0][0] = 0;
		for (int i = 1; i < v; i++)
		{
			for (int j = 0; j < v; j++)
			{
				for (auto& e : edge[j])
				{
					dp[i][e.to] = std::min(dp[i - 1][j] + e.val, dp[i][e.to]);
				}
			}
		}
	}
public:
	explicit Graph(int n)
	{
		v = n + 1;
		edge = new std::vector<Edge>[v];
		dp = new int*[v];
		for (int i = 0; i < v; i++)
		{
			dp[i] = new int[v];
		}
	}
	~Graph()
	{
		delete[] edge;
		for (int i = 0; i < v; i++)
		{
			delete[] dp[i];
		}
		delete[] dp;
	}
	void AddEdge(int from, int to, int val)
	{
		edge[from].emplace_back(to, val);
	}
	float MinAvgCircle()
	{
		CalPath();
		#ifdef DEBUG
		std::cout << "/******************/" << std::endl << "\t";
		for (int i = 0; i < v; i++)
		{
			std::cout << i << "\t";
		}
		std::cout << std::endl;
		for (int i = 0; i < v; i++)
		{
			std::cout << i << "\t";
			for (int j = 0; j < v; j++)
			{
				std::cout << (dp[i][j] == Edge::maxVal ? -1 : dp[i][j]) << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << "/******************/" << std::endl;
		#endif
		auto ans = (float)Edge::maxVal;
		float avg = 0;
		for (int i = 0; i < v; i++)
		{
			if (dp[v - 1][i] == Edge::maxVal)
			{
				continue;
			}
			for (int j = 0; j < v; j++)
			{
				avg = std::max(avg, (float)(dp[v - 1][i] - dp[j][i]) / (float)(v - j - 1));
			}
			ans = std::min(ans, avg);
			avg = 0;
		}
		return ans;
	}
};

int main()
{
	int n, e, u, v, w;
	std::cin >> n >> e;
	Graph g(n);
	for (int i = 0; i < e; i++)
	{
		std::cin >> u >> v >> w;
		g.AddEdge(u, v, w);
	}
	std::cout << std::fixed << std::setprecision(3) << g.MinAvgCircle();
	return 0;
}