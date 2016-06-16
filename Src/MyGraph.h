#pragma once
#include <list>
#include <map>
#include "MyConnection.h"

namespace MyAStarPath
{
	class MyGraph
	{
	private:
		std::list<MyNode*> Nodes;
		std::map < MyNode*, std::list<MyConnection*>*> NodeConnections;

	public:

		MyGraph();
		~MyGraph();

		std::list<MyConnection*>* GetConnections(MyNode *node);
		MyNode* AddNode(MyNode toAdd);
		MyNode*  NodeExists(float x, float y, float z);
		bool RemoveNodeAndConnection(MyNode *toRemove);
		void RemoveNodesConnectionsInRadius(float x, float y, float z, double radius);

		MyNode* FindClosestNode(float x, float y, float z, double maxDistance, bool mustConnect);
		bool ConnectNode(MyNode *statrNode, MyNode *endNode, bool biDirectional);
		int ConnectNodesRadius(MyNode *startNode, double radius, bool biDirectional);
		std::list<MyNode*> GetNodes() const
		{ return Nodes; }
		std::map < MyNode*, std::list<MyConnection*>*> GetConnections() const
		{ return NodeConnections; }
		std::list<MyConnection*> GetConnectionsList();


	};

}
