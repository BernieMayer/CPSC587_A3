/*
 * PhysicsBox.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#include "PhysicsMass.h"

PhysicsMass::PhysicsMass() {
	// TODO Auto-generated constructor stub

}

PhysicsMass::~PhysicsMass() {
	// TODO Auto-generated destructor stub
}

PhysicsMass::PhysicsMass(glm::vec3 arg_position, float arg_mass)
: PhysicsObject(arg_position)
{
	mass = arg_mass;
	isFixed = false;

}



void PhysicsMass::setLocation(glm::vec3 aLocation)
{
	PhysicsObject::position = aLocation;
}


float PhysicsMass::getMass()
{
	return mass;
}


void PhysicsMass::applyForce(glm::vec3 forceVector)
{

	if (! isFixed)
		total_force = total_force + forceVector;
	//printf("The total force is now (%f, %f, %f) \n", total_force.x, total_force.y, total_force.z);

}

vec3  PhysicsMass::getVelocity()
{
	return velocity;
}

void PhysicsMass::resolveForces(float dt)
{
	if ( ! isFixed) {
	vec3 acceleration =  total_force * (1.0f/(float)mass);

	velocity = velocity + acceleration * dt;

	PhysicsObject::position = position + velocity * dt;

	/*
	printf("The total force is now (%f, %f, %f) \n", total_force.x, total_force.y, total_force.z);
	printf("The location is now (%f, %f, %f) \n", position.x, position.y, position.z);
	printf("The acceleration is now (%f, %f, %f) \n", acceleration.x, acceleration.y, acceleration.z);
	*/
	}
}

void PhysicsMass::zeroOutForce()
{
	total_force = vec3(0,0,0);
}
