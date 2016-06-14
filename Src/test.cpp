#include <cstdio>
#include "MyGraph.h"
#include "MyAStar.h"
#include <iostream>
#include <string>
#include <string.h>
#include "json.hpp"

using json = nlohmann::json;


MyAStarPath::MyGraph* GetGraphFromJSON(std::string jsonGraph)
{
	auto toRet = new MyAStarPath::MyGraph();

	json j = json::parse(jsonGraph);

	auto tt = j["MyGraph"]["Nodes"];

	std::cout << tt.size() << std::endl;

	for (int cnt = 0; cnt < tt.size(); cnt++)
	{
		auto tnode = MyAStarPath::MyNode(j["MyGraph"]["Nodes"][cnt]["X"].get<float>(), j["MyGraph"]["Nodes"][cnt]["Y"].get<float>(), j["MyGraph"]["Nodes"][cnt]["Z"].get<float>());
		tnode.Passable = j["MyGraph"]["Nodes"][cnt]["Pass"].get<bool>();
		tnode.Modifier = j["MyGraph"]["Nodes"][cnt]["Mod"].get<double>();

		toRet->AddNode(tnode);
	}


	tt = j["MyGraph"]["Connections"];
	std::cout << tt.size() << std::endl;

	for (int cnt = 0; cnt < tt.size(); cnt++)
	{
		auto fromNode = toRet->NodeExists(j["MyGraph"]["Connections"][cnt]["FromX"].get<float>(), j["MyGraph"]["Connections"][cnt]["FromY"].get<float>(), j["MyGraph"]["Connections"][cnt]["FromZ"].get<float>());
		auto toNode = toRet->NodeExists(j["MyGraph"]["Connections"][cnt]["ToX"].get<float>(), j["MyGraph"]["Connections"][cnt]["ToY"].get<float>(), j["MyGraph"]["Connections"][cnt]["ToZ"].get<float>());
		if (fromNode != nullptr && toNode != nullptr)
		{
			toRet->ConnectNode(fromNode, toNode, false);
		}
	}

	return toRet;
}


std::string GetJSONFromGraph(MyAStarPath::MyGraph& graph)
{
	json j;

	auto Nodes = graph.GetNodes();
	int cnt = 0;
	for (auto it : Nodes)
	{
		j["MyGraph"]["Nodes"][cnt] = {{"X", it->X},{"Y",it->Y},{"Z",it->Z},{"Mod",it->Modifier},{"Pass",it->Passable}};
		cnt++;
	}
	auto Connections = graph.GetConnections();

	cnt = 0;
	for (auto it : Connections)
	{
		for (auto tt = it.second->begin(); tt != it.second->end(); ++tt)
		{
			j["MyGraph"]["Connections"][cnt] = {{"FromX",(*tt)->FromNode->X},{"FromY",(*tt)->FromNode->Y},{"FromZ",(*tt)->FromNode->Z},{"ToX", (*tt)->ToNode->X},{"ToY",(*tt)->ToNode->Y},{"ToZ",(*tt)->ToNode->Z}};
			cnt++;
		}
	}

	return j.dump(1);
}


void main()
{
	std::cout << " test Started " << std::endl;
	auto graph = new MyAStarPath::MyGraph();
	auto nodea = MyAStarPath::MyNode(1, 1, 1);
	auto nodeb = MyAStarPath::MyNode(2, 2, 2);
	auto nodec = MyAStarPath::MyNode(3, 3, 3);
	auto noded = MyAStarPath::MyNode(4, 4, 4);
	auto nodee = MyAStarPath::MyNode(5, 5, 5);
	auto nodef = MyAStarPath::MyNode(6, 6, 6);

	auto a = graph->AddNode(nodea);
	auto b = graph->AddNode(nodeb);
	auto c = graph->AddNode(nodec);
	auto d = graph->AddNode(noded);
	auto e = graph->AddNode(nodee);
	auto f = graph->AddNode(nodef);

	std::cout << "Should Have 6 Nodes: " << graph->GetNodes().size() << std::endl;

	auto tnode = graph->FindClosestNode(1, 1, 1, 10, false);
	std::cout << "Should be nodea: " << static_cast<bool>(tnode == &a) << std::endl;

	graph->ConnectNode(&a, &b, true);
	graph->ConnectNode(&b, &c, true);
	graph->ConnectNode(&b, &f, true);
	graph->ConnectNode(&c, &d, true);
	std::cout << "Should Have 5 Connections: " << graph->GetConnections().size() << std::endl;


	auto tcon = graph->GetConnections(&b);
	std::cout << "Should Have 3 Connections: " << tcon->size() << std::endl;

	std::cout << "Init MyAstar" << std::endl;
	auto astart = MyAStarPath::MyAstar(graph);

	std::cout << "Start First Search" << std::endl;
	auto resultsa = astart.SearchForPath(&a, &d, false, true);
	std::cout << "Should be 4: " << resultsa.size() << std::endl;
	auto resultsb = astart.SearchForPath(&a, &f, false, true);
	std::cout << "Should be 3: " << resultsb.size() << std::endl;
	auto resultsc = astart.SearchForPath(&c, &f, false, true);
	std::cout << "Should be 3: " << resultsc.size() << std::endl;


	/*
		std::cout << "Load with 5,000 nodes" << std::endl;
		for (int cnt = 0;cnt < 5000;cnt++)
		{
			graph->AddNode(MyAStarPath::MyNode(cnt, cnt, cnt));
		}
		*/
	auto tstr = GetJSONFromGraph(*graph);

	std::cout << tstr << std::endl;

	auto tt = GetGraphFromJSON(tstr);

	std::cout << "delete graph" << std::endl;

	delete graph;
	/*
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

	auto res = astart.SearchForPath(na, nb, false, true);
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
*/
	std::cout << "Hit Enter to continue" << std::endl;
	std::cin.get();
}

