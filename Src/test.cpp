#include <cstdio>
#include "MyGraph.h"
#include "MyAStar.h"

void main()
{
	printf("test");
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

	auto tnode = graph->FindClosestNode(1, 1, 1,10,false);
	graph->ConnectNode(nodea, nodeb, true);
	graph->ConnectNode(nodeb, nodec, true);
	graph->ConnectNode(nodeb, nodef, true);
	graph->ConnectNode(nodec, noded, true);

	auto tcon = graph->GetConnections(nodea);

	auto astart = MyAStarPath::MyAstar(graph);

	auto resultsa = astart.SearchForPath(nodea, noded);
	auto resultsb = astart.SearchForPath(nodea, nodef);
	auto resultsc = astart.SearchForPath(nodec, nodef);


	delete graph;
}
