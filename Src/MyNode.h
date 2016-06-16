#pragma once
#include <map>

namespace MyAStarPath
{
	class MyNode
	{
	private:
		static float LerpF(float from, float to, float amount)
		{
			return (1 - amount) * from + amount * to;
		}


	public:
		MyNode();
		MyNode(float x, float y, float z);
		~MyNode();
		
		double Slope(MyNode *toNode) const;
		double GetDistance3D(MyNode &toNode) const;
		double GetDistance2D(MyNode &toNode) const;
		bool IsNan() const;
		bool IsInfinity() const;
		static MyNode Lerp(MyNode &start, MyNode &end, int maxDistance)
		{
			double distance = start.GetDistance3D(end);
			if (distance < maxDistance)
				return end;

			double ratio = maxDistance / distance;

			float x = LerpF(start.X, end.X, static_cast<float>(ratio));
			float y = LerpF(start.Y, end.Y, static_cast<float>(ratio));
			float z = LerpF(start.Z, end.Z, static_cast<float>(ratio));

			return MyNode(x, y, z);

		}
		
		
		
		
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