#include "MyAStar.h"

using namespace MyAStarPath;

MyAstar::MyAstar(MyGraph* graph)
{
	_myGraph = graph;
}

MyAstar::~MyAstar()
{

}

void MyAstar::InitialiseDjGraph(MyNode* startingNode)
{
	_qDjUnchecked.clear();
	for (auto it = _myGraph->Nodes.begin(); it != _myGraph->Nodes.end();++it)
	{
		(*it)->Prev = nullptr;
		(*it)->Checked = false;
		if ((*it) == startingNode)
		{
			(*it)->DistanceFromStart = 0;
			_qDjUnchecked.push_front(*it);
		}
		else
		{
			(*it)->DistanceFromStart = std::numeric_limits<double>::infinity();
			_qDjUnchecked.push_back(*it);
		}

	}
}

std::list<MyNode*> MyAstar::SearchForPath(MyNode* startNode, MyNode* endNode, bool tryReverse, bool breakOnEndNode)
{
	InitialiseDjGraph(startNode);
	auto lastPath = std::list<MyNode*>();

	while (_qDjUnchecked.size() > 0)
	{
		_qDjUnchecked.sort([](MyNode*nodea, MyNode *nodeb) { return nodea->DistanceFromStart < nodeb->DistanceFromStart;});
		MyNode *node = _qDjUnchecked.front();
		_qDjUnchecked.pop_front();

		node->Checked = true;

		if (node == endNode && breakOnEndNode == true)
			break;

		auto connections = _myGraph->GetConnections(node);
		if (connections == nullptr)
			continue;

		for (auto it = (*connections).begin();it != (*connections).end(); ++it)
		{
			if ((*it)->ToNode->Checked)
				continue;

			double alt = node->DistanceFromStart + (*it)->Distance;
			if (alt < (*it)->ToNode->DistanceFromStart)
			{
				(*it)->ToNode->DistanceFromStart = alt;
				(*it)->ToNode->Prev = node;
			}

		}

	}
	auto tnode = endNode->Prev;
	while (tnode != nullptr)
	{
		lastPath.push_front(tnode);
		tnode = tnode->Prev;
	}
	if (lastPath.size() > 0)
	{
		lastPath.push_back(endNode);
	}
	return lastPath;
}
