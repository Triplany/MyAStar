#include "MyConnection.h"

using namespace MyAStarPath;

MyConnection::MyConnection(MyNode* from, MyNode* to, double weight = 0)
{
	FromNode = from;
	ToNode = to;
	Distance = to->Distance3D(from);
	Weight = weight;
}

MyConnection::~MyConnection()
{
}
