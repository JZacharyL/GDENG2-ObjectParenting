#pragma once
#include "Vector4D.h"
#include "Matrix4x4.h"
#include <cmath>

class Quaternion : public Vector4D
{
public:
	//Iden Quaternion
	Quaternion() : Vector4D(0, 0, 0, 1) {

	}

	//Generate quaterion based on static vals
	Quaternion(float x, float y, float z, float w) : Vector4D(x, y, z, w) {

	}

	//Generate quaternion based on angle-axis
	Quaternion(Vector3D axis, float angle) : Vector4D() { /*Blank instructor call will ensure no null fuckery happens*/
		
		//Generate angle halves
		float sinHalf = sin(angle / 2);
		float cosHalf = cos(angle / 2);

		//Set values of the axis of rotation via the normalized (by sin or cos) values of the "axis" passed as a vector3
		x = axis.getX() * sinHalf;
		y = axis.getY() * sinHalf;
		z = axis.getZ() * sinHalf;

		//Set the magnitude of the quaternion based on the "opposing angle metric" (whatever the normalization did not use)
		w = cosHalf;

		//Logic here is that when you yeet the object into the 4th dimension, the magnitude value will remain the same and will allow the
		//recalculation of the correct angle vals by virtue of the amount of difference from the old sinHalf and the new sinHalf (in ratio to cosHalf)
		//TL;DR cosHalf makes sure that sinHalf doesn't malfunction
	}

	//Normalizing a quaternion basically means reducing all values by the ratio of all values
	Quaternion Normalized(Quaternion Initial) {

		//Get initial quaternions' length
		float length = Initial.getLength();

		//use as rationalizer for all elements of the quaternion
		Quaternion Normal = Quaternion(Initial.x / length, Initial.y / length, Initial.z / length, Initial.w / length);

		return Normal;
	}

	//P.S. Fuck you Prof. Heavyside
	// Inital ----------->
	// Conjugate <---------
	static Quaternion Conjugate(Quaternion Initial) { /*Returns the inverse of the given quaternion with the same angle magnitude*/
		Quaternion Conjugate = Quaternion(-Initial.x, -Initial.y, -Initial.z, Initial.w);

		return Conjugate;
	}

	//Give new rotated position by quaternion
	static Vector3D Rotate(Vector3D* base, Quaternion rotate) {
		
		Vector3D newVector((rotate.y * base->z) - (rotate.z * base->y), (rotate.z * base->x) - (rotate.x * base->z), (rotate.x * base->y) - (rotate.y * base->x));

		Vector3D FinalVector((rotate.y * newVector.z) - (rotate.z * newVector.y), (rotate.z * newVector.x) - (rotate.x * newVector.z), (rotate.x * newVector.y) - (rotate.y * newVector.x));

		Vector3D rebase = *base;

		Vector3D FinalDisplacement = rebase + (newVector * (2 * rotate.w) + FinalVector * 2);

		return FinalDisplacement;
		
		/*
		Quaternion conjugate = Quaternion::Conjugate(rotate);

		Quaternion finalRotation = rotate * base;

		finalRotation = finalRotation * conjugate;

		return Vector3D(finalRotation.x, finalRotation.y, finalRotation.z);
		*/
	}

	//Mutiply by ...
	//Number
	Quaternion operator *(float num)
	{
		return Quaternion(x * num, y * num, z * num, w * num);
	}
	//Other quaternion
	Quaternion operator *(Quaternion other)
	{
		//Behold the 4th dimension fuckery

		//Calculate new angle magnitude
		float newW = w * other.w - (x * other.x + y * other.y + z * other.z);

		//Calculate new unit vector vals
		float newX = (w * other.x) + (other.w * x) + (y * other.z - z * other.y);
		float newY = (w * other.y) + (other.w * y) + (z * other.x - x * other.z);
		float newZ = (w * other.z) + (other.w * z) + (x * other.y - y * other.x);

		return Quaternion(newX, newY, newZ, newW);
	}

	Quaternion operator *=(Quaternion other)
	{
		//Behold the 4th dimension fuckery

		//Calculate new angle magnitude
		float newW = w * other.w - (x * other.x + y * other.y + z * other.z);

		//Calculate new unit vector vals
		float newX = (w * other.x) + (other.w * x) + (y * other.z - z * other.y);
		float newY = (w * other.y) + (other.w * y) + (z * other.x - x * other.z);
		float newZ = (w * other.z) + (other.w * z) + (x * other.y - y * other.x);

		return Quaternion(newX, newY, newZ, newW);
	}

	//Vector3D
	Quaternion operator *(Vector3D* vector) {
		//More 4th dimension fuckery
		float newW = (-x * vector->x) - (y * vector->y) - (z * vector->z); //Using x as a forced Euler axis

		float newX = w * vector->x + (y * vector->z) - (z * vector->y); //use w as Euler axis

		float newY = w * vector->y + (z * vector->x) - (x * vector->z); //use w as Euler axis

		float newZ = w * vector->z + (x * vector->y) - (y * vector->x); //use w as Euler axis

		return Quaternion(newX, newY, newZ, newW);
	}

	Quaternion operator *=(Vector3D* vector) {
		//More 4th dimension fuckery
		float newW = (-x * vector->x) - (y * vector->y) - (z * vector->z); //Using x as a forced Euler axis

		float newX = w * vector->x + (y * vector->z) - (z * vector->y); //use w as Euler axis

		float newY = w * vector->y + (z * vector->x) - (x * vector->z); //use w as Euler axis

		float newZ = w * vector->z + (x * vector->y) - (y * vector->x); //use w as Euler axis

		return Quaternion(newX, newY, newZ, newW);
	}

	//Subtract by ... other quaternion
	Quaternion operator -(Quaternion other)
	{
		//Simply subtract all relevant items
		return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	//Add ... other quaternion
	Quaternion operator +(Quaternion other)
	{
		//Simply add all relevant items
		return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	//The meat and potatoes
	//THIS Quaternion to Rotation Matrix 
	Matrix4x4 ToRotationMatrix() {
		Vector3D forwardRot; // Holds the rotation around Z
		Vector3D upwardRot; //Holds the rotation around the Y
		Vector3D rightwardRot; //Holds the rotation around the X

		//As influenced by the x - z plane --> Dir1
		float forwardX = 2 * (x * z) - (w * y);
		//As influenced by the y + z plane --> Dir2
		float forwardY = 2 * (y * z) + (w * x);
		//As influenced by the unit vector value --> Euler Mag
		float forwardZ = 1 - (2 * (x * x) + (y * y));

		forwardRot = Vector3D(forwardX, forwardY, forwardZ);

		//As influenced by the x - y plane --> Dir1
		float upwardX = 2 * ((x * y) + (w * z));
		//As influenced by the unit vector value --> Euler Mag
		float upwardY = 1 - (2 * ((x * x) + (z * z)));
		//As influenced by the y - z --> Dir2
		float upwardZ = 2 * ((y * z) - (w * x));

		upwardRot = Vector3D(upwardX, upwardY, upwardZ);

		//As influenced by the unit vector value --> Euler Mag
		float rightwardX = 1 - (2 * (y * y) + (z * z));
		//As influenced by the x - y plane --> Dir1
		float rightwardY = 2 * ((x * y) - (w * z));
		//As influenced by the x - z --> Dir2
		float rightwardZ = 2 * ((x * z) + (w * y));

		rightwardRot = Vector3D(rightwardX, rightwardY, rightwardZ);

		//Finally, return the matrix of rotation
		Matrix4x4 rotationMatrix;
		rotationMatrix.SetRotationMatrixByQuaternion(forwardRot, upwardRot, rightwardRot);
		return rotationMatrix;
	}
	//if the function above fails then this will all not work



private:
};
