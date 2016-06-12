#pragma once
#include <list>
#include <map>
#include "MyConnection.h"

namespace MyAStarPath
{
	class MyGraph
	{
	public:
		std::list<MyNode*> Nodes;
		std::map < MyNode*, std::list<MyConnection*>*> NodeConnections;

		MyGraph();
		~MyGraph();

		std::list<MyConnection*>* GetConnections(MyNode *node);
		void AddNode(MyNode *toAdd);
		bool NodeExists(float x, float y, float z);
		bool RemoveNodeAndConnection(MyNode *toRemove);

		MyNode* FindClosestNode(float x, float y, float z, double maxDistance, bool mustConnect);
		bool ConnectNode(MyNode *statrNode, MyNode *endNode, bool biDirectional);
		int ConnectNodesRadius(MyNode *statrNode, double radius, bool biDirectional);

	};

}
