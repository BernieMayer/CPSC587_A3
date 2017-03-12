/*
 * PhysicsObject.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() {
	// TODO Auto-generated constructor stub

}

PhysicsObject::~PhysicsObject() {
	// TODO Auto-generated destructor stub
}


PhysicsObject::PhysicsObject(glm::vec3 arg_Position)
{
	position = arg_Position;
}

glm::vec3 PhysicsObject::getPostion()
{
	return position;
}
