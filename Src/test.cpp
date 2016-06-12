#include <cstdio>
#include "MyGraph.h"
#include "MyAStar.h"
#include <iostream>

void main()
{
	std::cout << " test Started " << std::endl;
	auto graph = new MyAStarPath::MyGraph();
	auto nodea = new MyAStarPath::MyNode(1, 1, 1);
    auto nodeb = new MyAStarPath::MyNode(2, 2, 2);
	auto nodec = new MyAStarPath::MyNode(3, 3, 3);
	auto noded = new MyAStarPath::MyNode(4, 4, 4);
	auto nodee = new MyAStarPath::MyNode(5, 5, 5);
	auto nodef = new MyAStarPath::MyNode(6, 6, 6);

	graph->AddNode(nodea);
	graph->AddNode(nodeb);
	graph->AddNode(nodec);
	graph->AddNode(noded);
	graph->AddNode(nodee);
	graph->AddNode(nodef);

	std::cout << "Should Have 6 Nodes: " << graph->Nodes.size() << std::endl;

	auto tnode = graph->FindClosestNode(1, 1, 1,10,false);
	std::cout << "Should be nodea: " << static_cast<bool>(tnode == nodea)<< std::endl;

	graph->ConnectNode(nodea, nodeb, true);
	graph->ConnectNode(nodeb, nodec, true);
	graph->ConnectNode(nodeb, nodef, true);
	graph->ConnectNode(nodec, noded, true);
	std::cout << "Should Have 5 Connections: " << graph->NodeConnections.size() << std::endl;


	auto tcon = graph->GetConnections(nodeb);
	std::cout << "Should Have 3 Connections: " << tcon->size() << std::endl;

	auto astart = MyAStarPath::MyAstar(graph);

	auto resultsa = astart.SearchForPath(nodea, noded);
	std::cout << "Should be 4: " << resultsa.size() << std::endl;
	auto resultsb = astart.SearchForPath(nodea, nodef);
	std::cout << "Should be 3: " << resultsb.size() << std::endl;
	auto resultsc = astart.SearchForPath(nodec, nodef);
	std::cout << "Should be 3: " << resultsc.size() << std::endl;

	std::cout << "Hit Enter to continue" << std::endl;

	delete graph;
	std::cin.get();
}
