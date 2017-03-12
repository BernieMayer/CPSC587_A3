/*
 * PhysicsSpring.h
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#ifndef PHYSICSSPRING_H_
#define PHYSICSSPRING_H_

#include "PhysicsObject.h"

class PhysicsSpring: public PhysicsObject {
public:
	PhysicsSpring();
	virtual ~PhysicsSpring();

	PhysicsSpring(glm::vec3 argPos, double arg_k, glm::vec3 arg_x_r, glm::vec3 arg_x_c);

	double k;

	glm::vec3 x_r;
	glm::vec3 x_c;

private:

};

#endif /* PHYSICSSPRING_H_ */
