#include "MyHeuristics.h"
#include <math.h>

using namespace MyAStarPath;

double MyHeuristics::EuclidianDistance(MyNode* nodeA, MyNode* nodeB)
{
	return sqrt(MyHeuristics::SquareEuclidianDistance(nodeA, nodeB));
}

double MyHeuristics::SquareEuclidianDistance(MyNode* nodeA, MyNode* nodeB)
{
	double dx = nodeA->X - nodeB->X;
	double dy = nodeA->Y - nodeB->Y;
	double dz = nodeA->Z - nodeB->Z;

	return dx*dx + dy*dy + dz*dz;
}
