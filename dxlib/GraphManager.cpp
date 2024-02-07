#include "GraphManager.h"

struct Graph
{
private:
	string GraphName = "";
	int GraphPath;
public:
	void Set(std::string name, std::string path)
	{
		GraphName = name;
		GraphPath = LoadGraph(path.c_str());
	}
	std::string GetName()const
	{
		return GraphName;
	}

	int GetHandle()const
	{
		return GraphPath;
	}

	void Delete()
	{
		DeleteGraph(GraphPath);
	}
};

GraphManager::GraphManager()
{
	graph.resize(0);
}

GraphManager::~GraphManager()
{
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i])
		{
			graph[i]->Delete();
			delete graph[i];
			graph[i] = nullptr;
		}
	}
}

void GraphManager::Load(string name, string path)
{
	graph.resize(graph.size() + 1);

	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i])
		{
			if (graph[i]->GetName() == name)
			{
				graph.pop_back();
				return;
			}
		}
		else if (!graph[i])
		{
			graph[i] = new Graph;
			graph[i]->Set(name, path);
		}
	}
}

void GraphManager::Draw(float x, float y, float exRate, float angle, string name)
{
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i])
		{
			if (graph[i]->GetName() == name)
			{
				DrawRotaGraph(static_cast<int>(x), static_cast<int>(y), exRate, angle, graph[i]->GetHandle(), true);
				return;
			}
		}
	}
	return;
}

int GraphManager::GetHandle(string name)
{
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i])
		{
			if (graph[i]->GetName() == name)
			{
				return graph[i]->GetHandle();
			}
		}
	}
}
