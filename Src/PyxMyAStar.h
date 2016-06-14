#pragma once
#include "Pyx/Scripting/Script.h"
#include "MyGraph.h"

namespace PyxMyAStarLib
{
	class PyxMyAStar
	{
	public:
	
	static void BindWithScript(Pyx::Scripting::Script* script);
		static MyAStarPath::MyGraph* LoadGraphFromJSON(std::string jsonGraph) ;
		static std::string GetJSONFromGraph(MyAStarPath::MyGraph &graph);
		//	PyxMyAStar();
//	~PyxMyAStar();
	};
}
