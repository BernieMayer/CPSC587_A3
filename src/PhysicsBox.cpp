/*
 * PhysicsBox.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#include "PhysicsBox.h"

PhysicsBox::PhysicsBox() {
	// TODO Auto-generated constructor stub

}

PhysicsBox::~PhysicsBox() {
	// TODO Auto-generated destructor stub
}

PhysicsBox::PhysicsBox(glm::vec3 arg_position, double arg_mass)
: PhysicsObject(arg_position)
{
	mass = arg_mass;
}



void PhysicsBox::setLocation(glm::vec3 aLocation)
{
	PhysicsObject::position = aLocation;
}


double PhysicsBox::getMass()
{
	return mass;
}
