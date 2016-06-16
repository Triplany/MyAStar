#include "PyxMyAStar.h"
#include "Pyx/pyx.h"
#include "MyAStar.h"
#include "json.hpp"


using namespace PyxMyAStarLib;
using json = nlohmann::json;

namespace LuaIntf
{
	LUA_USING_LIST_TYPE(std::list)
}

void PyxMyAStar::BindWithScript(Pyx::Scripting::Script* script)
{
	using namespace LuaIntf;
	
	// Bind MyNode
	LuaBinding(script->GetLuaState())
		.beginClass<MyAStarPath::MyNode>("MyNode")
		.addConstructor(LUA_ARGS(_opt<float>, _opt<float>, _opt<float>))
		.addVariable("X", &MyAStarPath::MyNode::X)
		.addVariable("Y", &MyAStarPath::MyNode::Y)
		.addVariable("Z", &MyAStarPath::MyNode::Z)
		.addFunction("GetDistance2D", &MyAStarPath::MyNode::GetDistance2D)
		.addFunction("GetDistance3D", &MyAStarPath::MyNode::GetDistance3D)
		.addPropertyReadOnly("IsNan", &MyAStarPath::MyNode::IsNan)
		.addPropertyReadOnly("IsInfinity", &MyAStarPath::MyNode::IsInfinity)
		.endClass();


	LuaBinding(script->GetLuaState())
		.beginClass<MyAStarPath::MyConnection>("MyConnection")
		.addConstructor(LUA_ARGS(MyAStarPath::MyNode *, MyAStarPath::MyNode *, double))
		.addVariable("ToNode", &MyAStarPath::MyConnection::ToNode)
		.addVariable("FromNode", &MyAStarPath::MyConnection::FromNode)
		.addVariable("Distance", &MyAStarPath::MyConnection::Distance)
		.addVariable("Weight", &MyAStarPath::MyConnection::Weight)
		.endClass();


	// Bind MyGraph
	LuaBinding(script->GetLuaState())
		.beginClass<MyAStarPath::MyGraph>("MyGraph")
		.addConstructor(LUA_ARGS())
		.addFunction("AddNode", &MyAStarPath::MyGraph::AddNode)
		.addFunction("NodeExists", &MyAStarPath::MyGraph::NodeExists)
		.addFunction("RemoveNodeAndConnection", &MyAStarPath::MyGraph::RemoveNodeAndConnection)
		.addFunction("RemoveNodesConnectionsInRadius", &MyAStarPath::MyGraph::RemoveNodesConnectionsInRadius)
		.addFunction("FindClosestNode", &MyAStarPath::MyGraph::FindClosestNode)
		.addFunction("ConnectNode", &MyAStarPath::MyGraph::ConnectNode)
		.addFunction("ConnectNodeRadius", &MyAStarPath::MyGraph::ConnectNodesRadius)
		.addFunction("GetNodes", &MyAStarPath::MyGraph::GetNodes)
		.addFunction("GetConnectionsList", &MyAStarPath::MyGraph::GetConnectionsList)
		.addStaticFunction("LoadGraphFromJSON",&PyxMyAStar::LoadGraphFromJSON)
		.addStaticFunction("GetJSONFromGraph", &PyxMyAStar::GetJSONFromGraph)
		.endClass();

	//Bind MyAStar
	LuaBinding(script->GetLuaState())
		.beginClass<MyAStarPath::MyAstar>("MyAStar")
		.addConstructor(LUA_ARGS(MyAStarPath::MyGraph*))
		.addFunction("SearchForPath", &MyAStarPath::MyAstar::SearchForPath)
		.addStaticFunction("OptimizeStart", &MyAStarPath::MyAstar::OptimizeStart)
		.endClass();

}

MyAStarPath::MyGraph* PyxMyAStar::LoadGraphFromJSON(std::string jsonGraph)
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

std::string PyxMyAStar::GetJSONFromGraph(MyAStarPath::MyGraph &graph)
{
	json j;

	auto Nodes = graph.GetNodes();
	int cnt = 0;
	for (auto it : Nodes)
	{
		j["MyGraph"]["Nodes"][cnt] = { { "X", it->X },{ "Y",it->Y },{ "Z",it->Z },{ "Mod",it->Modifier },{ "Pass",it->Passable } };
		cnt++;
	}
	auto Connections = graph.GetConnections();

	cnt = 0;
	for (auto it : Connections)
	{
		for (auto tt = it.second->begin(); tt != it.second->end(); ++tt)
		{
			j["MyGraph"]["Connections"][cnt] = { { "FromX",(*tt)->FromNode->X },{ "FromY",(*tt)->FromNode->Y },{ "FromZ",(*tt)->FromNode->Z },{ "ToX", (*tt)->ToNode->X },{ "ToY",(*tt)->ToNode->Y },{ "ToZ",(*tt)->ToNode->Z } };
			cnt++;
		}
	}

	return j.dump(1);
}
