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

PhysicsSpring::PhysicsSpring(glm::vec3 argPos, double arg_k, glm::vec3 arg_x_r, glm::vec3 arg_x_c)
	: PhysicsObject(argPos)
{
	k = arg_k;
	x_r = arg_x_r;
	x_c = arg_x_c;

}

