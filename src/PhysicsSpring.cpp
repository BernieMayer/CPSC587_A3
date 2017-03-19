/*
 * PhysicsSpring.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#include "PhysicsSpring.h"

PhysicsSpring::PhysicsSpring() {
	// TODO Auto-generated constructor stub

}

PhysicsSpring::~PhysicsSpring() {
	// TODO Auto-generated destructor stub
}
/*
PhysicsSpring::PhysicsSpring(glm::vec3 argPos, double arg_k, glm::vec3 arg_x_r, glm::vec3 arg_x_c)
	: PhysicsObject(argPos)
{
	k = arg_k;
	x_r = arg_x_r;
	x_c = arg_x_c;

}

*/

vec3 PhysicsSpring::getMassA_Location()
{
	return massA->getPostion();
}

vec3 PhysicsSpring::getMassB_Location()
{
	return massB->getPostion();
}

PhysicsSpring::PhysicsSpring(glm::vec3 argPos,
		double arg_k, double arg_x_r, double arg_x_c, PhysicsMass* arg_massA, PhysicsMass* arg_massB )
	: PhysicsObject(argPos)
{
	k = arg_k;
	x_r = arg_x_r;
	x_c = arg_x_c;

	massA = arg_massA;
	massB = arg_massB;

}



void PhysicsSpring::applyForce()
{
	vec3 locA = massA->getPostion();
	vec3 locB = massB->getPostion();


	double x = length(locA - locB); //get the length between A and B


	float forceScalar = -k * (x - x_r);

	vec3 forceVectorOnA = forceScalar * (locB - locA) * (1.0f/length(locB - locA));
	vec3 forceVectorOnB = -1.0f * forceVectorOnB;


	massA->applyForce(forceVectorOnA);
	massB->applyForce(forceVectorOnB);

}

