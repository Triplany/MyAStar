#include "MyGraph.h"
#include <ostream>
#include <iostream>

using namespace MyAStarPath;

MyGraph::MyGraph()
{
}

MyGraph::~MyGraph()
{
	for (auto it = NodeConnections.begin(); it != NodeConnections.end();++it)
	{
		for (auto tt = (*it).second->begin(); tt != (*it).second->end();++tt)
		{
			delete (*tt);
		}
		delete (*it).second;
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

MyNode*  MyGraph::AddNode(MyNode toAdd)
{
	auto tNode = NodeExists(toAdd.X, toAdd.Y, toAdd.Z);
	if (tNode == nullptr)
	{
		tNode = new MyNode(toAdd.X, toAdd.Y, toAdd.Z);
		tNode->Modifier = toAdd.Modifier;
		tNode->Passable = toAdd.Passable;

		Nodes.push_back(tNode);
	}
	return tNode;
}

MyNode* MyGraph::NodeExists(float x, float y, float z)
{
	for (auto it : Nodes)
	{
		if (it->X == x && it->Y == y && it->Z == z)
			return it;
	}

	return nullptr;
}

bool MyGraph::RemoveNodeAndConnection(MyNode* toRemove)
{
	bool found = false;

	// Delete from Connections

	auto it = NodeConnections.begin();

	while (it != NodeConnections.end())
	{
		auto tt = it->second->begin();
		while (tt != it->second->end())
		{
			if ((*tt)->ToNode == toRemove || (*tt)->FromNode == toRemove)
			{
				auto toErase = tt;
				++tt;
				delete (*toErase);
				it->second->erase(toErase);
			}
			else
				++tt;
		}
		if ((*it).first == toRemove)
		{
			auto toErase = it;
			++it;
			delete toErase->second;
			NodeConnections.erase(toErase);
		}
		else
			++it;

	}


	// Delete From Node List
	Nodes.remove(toRemove);
	delete toRemove;

	return false;
}

void MyGraph::RemoveNodesConnectionsInRadius(float x, float y, float z, double radius)
{
	auto it = Nodes.begin();
	auto startPoint = MyNode(x, y, z);

	while (it != Nodes.end())
	{
		if ((*it)->GetDistance3D(startPoint) <= radius)
		{
			auto toRemove = (*it);
			++it;
			RemoveNodeAndConnection(toRemove);
		}
		else
			++it;
	}
}

MyNode* MyGraph::FindClosestNode(float x, float y, float z, double maxDistance, bool mustConnect)
{
	MyNode tNode = MyNode(x, y, z);
	MyNode* toRet = nullptr;
	for (auto it : Nodes)
	{
		if (it->GetDistance3D(tNode) <= maxDistance && (toRet == nullptr || toRet->GetDistance3D(tNode) > it->GetDistance3D(tNode)))
			toRet = it;
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

	if (biDirectional)
		return ConnectNode(endNode,startNode,false);
	
	return true;
}

int MyGraph::ConnectNodesRadius(MyNode* startNode, double radius, bool biDirectional)
{
	int cnt = 0;
	for (auto it: Nodes)
	{
		if (it == startNode)
			continue;

		if (it->GetDistance3D(*startNode) <= radius)
		{
			ConnectNode(startNode, it, biDirectional);
			cnt++;
		}
	}
	return cnt;
}

std::list<MyConnection*> MyGraph::GetConnectionsList()
{
	auto toRet = std::list<MyConnection*>();

	for (auto it = NodeConnections.begin(); it != NodeConnections.end();++it)
	{
		for (auto tt = (*it).second->begin(); tt != (*it).second->end();++tt)
		{
			toRet.push_back((*tt));
		}
	}

	return toRet;
}
