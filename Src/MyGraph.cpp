#include "MyGraph.h"

using namespace MyAStarPath;

MyGraph::MyGraph()
{
}

MyGraph::~MyGraph()
{
	for(auto it = NodeConnections.begin(); it != NodeConnections.end();++it)
	{
		for (auto tt = (*it).second->begin(); tt != (*it).second->end();++tt)
		{
			delete *tt;
		}
	}
	NodeConnections.clear();

	for (auto it = Nodes.begin(); it != Nodes.end();++it)
	{
		delete *it;
	}
	Nodes.clear();
}

std::list<MyConnection*>* MyGraph::GetConnections(MyNode* node)
{
	if (NodeConnections.find(node) == NodeConnections.end())
		return nullptr;

	return NodeConnections[node];
}

void MyGraph::AddNode(MyNode* toAdd)
{
	if (!NodeExists(toAdd->X, toAdd->Y, toAdd->Z))
		Nodes.push_back(toAdd);


}

bool MyGraph::NodeExists(float x, float y, float z)
{
	for (auto it = Nodes.begin(); it != Nodes.end(); ++it)
	{
		if ((*it)->X == x && (*it)->Y == y && (*it)->Z == z)
			return true;
	}

	return false;
}

bool MyGraph::RemoveNodeAndConnection(MyNode* toRemove)
{
	return true;
}

MyNode* MyGraph::FindClosestNode(float x, float y, float z, double maxDistance, bool mustConnect)
{
	MyNode tNode = MyNode(x, y, z);
	MyNode* toRet = nullptr;
	for (auto it = Nodes.begin(); it != Nodes.end(); ++it)
	{
		if ((*it)->Distance3D(&tNode) <= maxDistance && (toRet == nullptr || toRet->Distance3D(&tNode) > (*it)->Distance3D(&tNode)))
			toRet = (*it);
	}

	return toRet;
}

bool MyGraph::ConnectNode(MyNode* startNode, MyNode* endNode, bool biDirectional)
{
	if (startNode == nullptr || endNode == nullptr || startNode == endNode)
		return false;

	auto startFind = NodeConnections.find(startNode);
	if (startFind != NodeConnections.end())
	{
		bool any = false;

		for (auto it = (*startFind).second->begin(); it != (*startFind).second->end();++it)
		{
			if ((*it)->ToNode == endNode)
			{
				any = true;
				break;
			}
		}
		if (!any)
		{
			NodeConnections[startNode]->push_back(new MyConnection(startNode, endNode, 0));
		}
	}
	else
	{
		auto tList = new std::list<MyConnection*>();
		tList->push_back(new MyConnection(startNode, endNode, 0));
		NodeConnections[startNode] = tList;
	}
		return true;
	auto endFind = NodeConnections.find(endNode);
	if (endFind != NodeConnections.end())
	{
		bool any = false;

		for (auto it = (*endFind).second->begin(); it != (*endFind).second->end();++it)
		{
			if ((*it)->ToNode == startNode)
			{
				any = true;
				break;
			}
		}
		if (!any)
		{
			NodeConnections[endNode]->push_back(new MyConnection(endNode, startNode, 0));
		}
	}
	else
	{
		auto tList = new std::list<MyConnection*>();
		tList->push_back(new MyConnection(endNode, startNode, 0));
		NodeConnections[endNode] = tList;
	}
	return true;
}

int MyGraph::ConnectNodesRadius(MyNode* statrNode, double radius, bool biDirectional)
{
	return 0;
}
