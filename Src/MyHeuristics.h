#pragma once
#include "MyNode.h"

namespace MyAStarPath
{
	class MyHeuristics
	{
	public:
		static double EuclidianDistance(MyNode *nodeA, MyNode *nodeB);
		static double SquareEuclidianDistance(MyNode *nodeA, MyNode *nodeB);
		static double AllEqual(MyNode *nodeA, MyNode *nodeB)
		{
			return 1;
		}

	};

}