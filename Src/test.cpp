#include <cstdio>
#include "MyGraph.h"
#include "MyAStar.h"
#include <iostream>

void main()
{
	std::cout << " test Started " << std::endl;
	auto graph = new MyAStarPath::MyGraph();
	auto nodea = MyAStarPath::MyNode(1, 1, 1);
    auto nodeb = MyAStarPath::MyNode(2, 2, 2);
	auto nodec = MyAStarPath::MyNode(3, 3, 3);
	auto noded =  MyAStarPath::MyNode(4, 4, 4);
	auto nodee = MyAStarPath::MyNode(5, 5, 5);
	auto nodef = MyAStarPath::MyNode(6, 6, 6);

	auto a = graph->AddNode(nodea);
	auto b = graph->AddNode(nodeb);
	auto c = graph->AddNode(nodec);
	auto d = graph->AddNode(noded);
	auto e = graph->AddNode(nodee);
	auto f = graph->AddNode(nodef);

	std::cout << "Should Have 6 Nodes: " << graph->GetNodes().size() << std::endl;

	auto tnode = graph->FindClosestNode(1, 1, 1,10,false);
	std::cout << "Should be nodea: " << static_cast<bool>(tnode == a)<< std::endl;

	graph->ConnectNode(a, b, true);
	graph->ConnectNode(b, c, true);
	graph->ConnectNode(b, f, true);
	graph->ConnectNode(c, d, true);
	std::cout << "Should Have 5 Connections: " << graph->GetConnections().size() << std::endl;


	auto tcon = graph->GetConnections(b);
	std::cout << "Should Have 3 Connections: " << tcon->size() << std::endl;

	std::cout << "Init MyAstar" << std::endl;
	auto astart = MyAStarPath::MyAstar(graph);

	std::cout << "Start First Search" << std::endl;
	auto resultsa = astart.SearchForPath(a, d);
	std::cout << "Should be 4: " << resultsa.size() << std::endl;
	auto resultsb = astart.SearchForPath(a, f);
	std::cout << "Should be 3: " << resultsb.size() << std::endl;
	auto resultsc = astart.SearchForPath(c, f);
	std::cout << "Should be 3: " << resultsc.size() << std::endl;


		std::cout << "Load with 5,000 nodes" << std::endl;
		for (int cnt = 0;cnt < 5000;cnt++)
		{
			graph->AddNode(MyAStarPath::MyNode(cnt, cnt, cnt));
		}
		std::cout << "delete graph" << std::endl;
		delete graph;

		for (int i = 0; i < 100; i++)
		{
		graph = new MyAStarPath::MyGraph();
		std::cout << "Load with 5,000 nodes and connections" << std::endl;
		MyAStarPath::MyNode *lastNode = nullptr;
		for (int cnt = 0;cnt < 5000;cnt++)
		{
			auto cNode = graph->AddNode(MyAStarPath::MyNode(cnt, cnt, cnt));
			if (cNode != nullptr && lastNode != nullptr)
			{
				graph->ConnectNode(lastNode, cNode, true);
			}
			lastNode = cNode;
		}
		std::cout << "Init AStar" << std::endl;
		astart = MyAStarPath::MyAstar(graph);
		std::cout << "check path 0 to 4000 " << std::endl;
		auto na = graph->NodeExists(0, 0, 0);
		auto nb = graph->NodeExists(4000, 4000, 4000);

		auto res = astart.SearchForPath(na, nb);
		std::cout << "Should be 4001: " << res.size() << std::endl;

		std::cout << "Delete 4000 nodes and connections" << std::endl;
		for (int cnt = 0;cnt < 4000;cnt++)
		{
			auto dnode = graph->FindClosestNode(cnt, cnt, cnt,100,false);
			graph->RemoveNodeAndConnection(dnode);
		}

		std::cout << "delete graph" << std::endl;
		delete graph;
	}
	std::cout << "Hit Enter to continue" << std::endl;
	std::cin.get();
}
