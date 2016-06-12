#pragma once
#include <map>

namespace MyAStarPath
{
	class MyNode
	{
	public:
		MyNode();
		MyNode(float x, float y, float z);
		~MyNode();
		
		double Slope(MyNode *toNode) const;
		double Distance3D(MyNode *toNode) const;
		double Distance2D(MyNode *toNode) const;
		float X;
		float Y;
		float Z;
		bool Passable;
		std::map<std::string, std::string> Flags;
		double Modifier = 0;

		double DistanceFromStart = std::numeric_limits<double>::infinity();
		bool Checked = false;
		MyNode *Prev = nullptr;


	};

}