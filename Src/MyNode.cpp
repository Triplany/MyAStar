#include "MyNode.h"
#include <math.h>
using namespace MyAStarPath;


MyNode::MyNode()
{
	X = 0;
	Y = 0;
	Z = 0;
	Passable = true;
	Flags = std::map<std::string, std::string>();
}

MyNode::MyNode(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
	Passable = true;
	Flags = std::map<std::string, std::string>();
}


MyNode::~MyNode()
{
}

double MyNode::Slope(MyNode *toNode) const
{
	double xd = X - toNode->X;
	double yd = Y - toNode->Y;
	double zd = Z - toNode->Z;
	double distance = sqrt(xd*xd + yd*yd + zd*zd);
	if (distance == 0)
		return 0;

	return fabs(Z - toNode->Z) / distance;
}

double MyNode::Distance3D(MyNode *toNode) const
{

	double xd = toNode->X - X;
	double yd = toNode->Y - Y;
	double zd = toNode->Z - Z;

	return sqrt(xd*xd + yd*yd + zd*zd);

}

double MyNode::Distance2D(MyNode *toNode) const
{
	double xd = toNode->X - X;
	double yd = toNode->Y - Y;

	return sqrt(xd*xd + yd*yd);

}
