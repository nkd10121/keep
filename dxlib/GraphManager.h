#pragma once
#include "DxLib.h"
#include <string>
#include <vector>

using namespace std;

struct Graph;

class GraphManager
{
public:
	GraphManager();
	~GraphManager();

	void Init(){ };

	void Load(string name, string path);

	void Draw(float x, float y, float exRate, float angle, string name);

	int GetHandle(string name);

private:
	vector<Graph*> graph;
};

