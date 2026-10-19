// In geometry, a point is a position in space. We can define a point in 3d-space as the set of coordinates x, y, and z. For example, Point { 2.0, 1.0, 0.0 } would be the point at coordinate space x=2.0, y=1.0, and z=0.0.

// In physics, a vector is a quantity that has a magnitude (length) and a direction (but no position). We can define a vector in 3d-space as an x, y, and z value representing the direction of the vector along the x, y, and z axis (the length can be derived from these). For example, Vector { 2.0, 0.0, 0.0 } would be a vector representing a direction along the positive x-axis (only), with length 2.0.

// A Vector can be applied to a Point to move the Point to a new position. This is done by adding the vector’s direction to the point’s position to yield a new position. For example, Point { 2.0, 1.0, 0.0 } + Vector { 2.0, 0.0, 0.0 } would yield Point { 4.0, 1.0, 0.0 }.

// Such points and vectors are often used in computer graphics (with points representing the vertices of a shape, and vectors represent movement of the shape).

#include <iostream>

class Vector3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Vector3d(double x, double y, double z)
		: m_x{x}, m_y{y}, m_z{z}
	{
	}

	void print() const
	{
		std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
	}

    friend class Point3d; 
};

class Point3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Point3d(double x, double y, double z)
		: m_x{x}, m_y{y}, m_z{z}
	{ }

	void print() const
	{
		std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
	}

	void moveByVector(const Vector3d& v)
	{
		m_x += v.m_x;
        m_y += v.m_y; 
        m_z += v.m_z; 
	}
};

int main()
{
	Point3d p { 1.0, 2.0, 3.0 };
	Vector3d v { 2.0, 2.0, -3.0 };

	p.print();
	p.moveByVector(v);
	p.print();

	return 0;
}