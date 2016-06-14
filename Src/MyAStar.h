#pragma once
#include "MyGraph.h"
#include "MyHeuristics.h"
#include <list>

namespace MyAStarPath
{
	class MyAstar
	{
	public:
		MyAstar(MyGraph *graph);
		~MyAstar();

		double(*ChosenHeuristic)(MyNode*, MyNode*) = &MyHeuristics::EuclidianDistance;;

		std::list<MyNode*> SearchForPath(MyNode *startNode, MyNode *endNode, bool tryReverse, bool breakOnEndNode);

	private: 
		MyGraph *_myGraph = nullptr;
		std::list<MyNode*> _qDjUnchecked;
		void InitialiseDjGraph(MyNode *startingNode);


		

	};

}