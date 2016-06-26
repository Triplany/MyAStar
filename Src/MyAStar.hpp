#pragma once
#include "MyGraph.hpp"
#include "MyHeuristics.hpp"
#include <list>

namespace MyAStarPath
{
	class MyAstar
	{
	public:
		MyAstar(MyGraph *graph);
		~MyAstar();

		double(*ChosenHeuristic)(MyNode*, MyNode*) = &MyHeuristics::EuclidianDistance;;

		std::list<MyNode> SearchForPath(MyNode *startNode, MyNode *endNode, bool tryReverse, bool breakOnEndNode);
		static void OptimizeStart(std::list<MyNode> *currentPath, MyNode startPoisition);


	private: 
		MyGraph *_myGraph = nullptr;
		std::list<MyNode*> _qDjUnchecked;
		void InitialiseDjGraph(MyNode *startingNode);


		

	};

}