#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

#include "Math.h"

using AStarMap = std::unordered_map<const WeightedGraphNode*, AStarScratch>;
using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;
using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;

struct AStarScratch
{
	const WeightedEdge* mParentEdge = nullptr;

	float mActualFromStart = 0.0f;
	float mHeuristic = 0.0f;

	bool mInOpenSet = false;
	bool mInClosedSet = false;
};

struct GBFSScratch
{
	const WeightedEdge* mParentEdge = nullptr;

	float mHeuristic = 0.0f;

	bool mInOpenSet = false;
	bool mInClosedSet = false;
};

struct GraphNode
{
	std::vector<GraphNode*> mAdjacent;
};

struct Graph
{
	std::vector<GraphNode*> mNodes;
};

struct WeightedEdge
{
	struct WeightedGraphNode* mFrom;
	struct WeightedGraphNode* mTo;

	float mWeight;
};

struct WeightedGraphNode
{
	std::vector<WeightedEdge*> mEdges;
};

struct WeightedGraph
{
	std::vector<WeightedGraphNode*> mNodes;
};

bool AStar(const WeightedGraph& g, const WeightedGraphNode* start, const WeightedGraphNode* goal, AStarMap& outMap)
{
	std::vector<const WeightedGraphNode*> openSet;

	const WeightedGraphNode* current = start;
	outMap[current].mInClosedSet = true;

	do
	{
		for (const WeightedEdge* edge : current->mEdges)
		{
			const WeightedGraphNode* neighbor = edge->mTo;

			AStarScratch& data = outMap[neighbor];

			if (!data.mInClosedSet)
			{
				data.mParentEdge = edge;
				data.mHeuristic = ComputeHeuristic(neighbor, goal);
				data.mActualFromStart = outMap[current].mActualFromStart + edge->mWeight;
				data.mInOpenSet = true;

				openSet.emplace_back(neighbor)
			}
			else
			{
				float newG = outMap[current].mActualFromStart + edge->mWeight;
				if (newG < data.mActualFromStart)
				{
					data.mParentEdge = edge;
					data.mActualFromStart = newG;
				}
			}
		}

		if (openSet.empty())
		{
			break;
		}

		auto iter = std::min_element(openSet.begin(), openSet.end(), [&outMap](const WeightedGraphNode* a, const WeightedGraphNode b)
			{
				float fOfA = outMap[a].mHeuristic + outMap[a].mActualFromStart;
				float fOfB = outMap[b].mHeuristic + outMap[b].mActualFromStart;

				return fOfA < fOfB;
			});

		current = *iter;

		openSet.erase(iter);
		outMap[current].mInOpenSet = false;
		outMap[current].mInClosedSet = true;

	} while (current != goal);

	return (current == goal) ? true : false;
}

bool BFS(const Graph& graph, const GraphNode* start, const GraphNode* goal, NodeToParentMap& outMap)
{
	bool pathFound = false;

	std::queue<const GraphNode*> q;
	q.emplace(start);

	while (!q.empty())
	{
		const GraphNode* current = q.front();
		q.pop();

		if (current == goal)
		{
			pathFound = true;
			break;
		}

		for (const GraphNode* node : current->mAdjacent)
		{
			const GraphNode* parent = outMap[node];
			if (parent == nullptr && node != start)
			{
				outMap[node] = current;
				q.emplace(node);
			}
		}
	}

	return pathFound;
}

float ComputeHeuristic(const WeightedGraphNode* start, const WeightedGraphNode* end)
{
	return 0.0f; // @TODO : Figure out why returning 0.0f does the trick... Shouldn't it return something else ?
}

bool GBFS(const WeightedGraph& g, const WeightedGraphNode* start, const WeightedGraphNode* goal, GBFSMap& outMap)
{
	std::vector<const WeightedGraphNode*> openSet;

	const WeightedGraphNode* current = start;
	outMap[current].mInClosedSet = true;

	do
	{
		for (const WeightedEdge* edge : current->mEdges)
		{
			GBFSScratch& data = outMap[edge->mTo];

			if (!data.mInClosedSet)
			{
				data.mParentEdge = edge;
				if (!data.mInOpenSet)
				{
					data.mHeuristic = ComputeHeuristic(edge->mTo, goal);
					data.mInOpenSet = true;
					
					openSet.emplace_back(edge->mTo);
				}
			}
		}

		if (openSet.empty())
		{
			break;
		}

		auto iter = std::min_element(openSet.begin(), openSet.end(), [&outMap](const WeightedGraphNode* a, const WeightedGraphNode b)
			{
				return outMap[a].mHeuristic < outMap[b].mHeuristic;
			});

		current = *iter;

		openSet.erase(iter);
		outMap[current].mInOpenSet = false;
		outMap[current].mInClosedSet = true;

	} while (current != goal);

	return (current == goal) ? true : false;
}
