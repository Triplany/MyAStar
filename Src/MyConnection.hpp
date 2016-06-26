#pragma once
#include "MyNode.hpp"

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