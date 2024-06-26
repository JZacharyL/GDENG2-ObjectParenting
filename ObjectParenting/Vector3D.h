#pragma once

class Vector3D
{
public:
	Vector3D() : x(0), y(0), z(0)
	{
		
	}
	Vector3D(float x, float y, float z) : x(x), y(y), z(z)
	{

	}
	Vector3D(const Vector3D& vector) : x(vector.x), y(vector.y), z(vector.z)
	{

	}

	~Vector3D()
	{
		
	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;

		v.x = start.x * (1.0f - delta) + end.x * delta;
		v.y = start.y * (1.0f - delta) + end.y * delta;
		v.z = start.z * (1.0f - delta) + end.z * delta;

		return v;
	}

	static Vector3D zeros()
	{
		Vector3D v;

		v.x = 0;
		v.y = 0;
		v.z = 0;

		return v;
	}

	static Vector3D ones()
	{
		Vector3D v;

		v.x = 1;
		v.y = 1;
		v.z = 1;

		return v;
	}

	float getX() const
	{
		return x;
	}

	float getY() const
	{
		return y;
	}

	float getZ() const
	{
		return z;
	}

	Vector3D operator *(float num)
	{
		return Vector3D(x * num, y * num, z * num);
	}

	Vector3D operator +(Vector3D vec)
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}
	
	float x, y, z;
};