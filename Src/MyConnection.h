#pragma once
#include "MyNode.h"

namespace MyAStarPath
{
	class MyConnection
	{
	public:
		MyConnection(MyNode *from, MyNode *to, double weight);
		~MyConnection();

		MyNode *ToNode;
		MyNode *FromNode;
		double Distance;
		double Weight;

	};

}