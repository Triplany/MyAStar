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
	auto nodes = _myGraph->GetNodes();
	for (auto it = nodes.begin(); it != nodes.end();++it)
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

std::list<MyNode> MyAstar::SearchForPath(MyNode* startNode, MyNode* endNode, bool tryReverse, bool breakOnEndNode)
{
	InitialiseDjGraph(startNode);
	auto lastPath = std::list<MyNode>();
	if (startNode == nullptr || endNode == nullptr)
		return lastPath;

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
		lastPath.push_front(MyNode(tnode->X, tnode->Y, tnode->Z));
		tnode = tnode->Prev;
	}
	if (lastPath.size() > 0)
	{
		lastPath.push_back(MyNode(endNode->X,endNode->Y,endNode->Z));
	}
	return lastPath;
}

void MyAstar::OptimizeStart(std::list<MyNode>* currentPath, MyNode startPoisition)
{
	auto it = currentPath->begin();
	auto currentIt = it;

	while (it != currentPath->end())
	{
		if ((*it).GetDistance3D(startPoisition) < (*currentIt).GetDistance3D(startPoisition))
		{
			currentIt = it;
		}
		else
			break;

		++it;
	}

	auto nextIt = ++currentIt;

	if (it != currentPath->end() && nextIt != currentPath->end())
	{
		MyNode newStart = (*it);
		auto totalDistance = (*it).GetDistance3D((*nextIt));
		for (auto cnt=0.1;cnt < 1;cnt=cnt+0.1)
		{
			auto toTest = MyNode::Lerp((*it), (*nextIt), totalDistance*cnt);

			if (toTest.GetDistance3D(startPoisition) < newStart.GetDistance3D(startPoisition))
			{
				newStart = toTest;
			}
		}
		currentPath->erase(it);
		currentPath->insert(nextIt, newStart);

	}
}
