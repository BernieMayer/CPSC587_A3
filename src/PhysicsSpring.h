/*
 * PhysicsSpring.h
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#ifndef PHYSICSSPRING_H_
#define PHYSICSSPRING_H_

#include "PhysicsObject.h"
#include "PhysicsMass.h"

using namespace glm;

class PhysicsSpring: public PhysicsObject {
public:
	PhysicsSpring();
	virtual ~PhysicsSpring();

	PhysicsMass* massA;
	PhysicsMass* massB;


	//PhysicsSpring(glm::vec3 argPos, double arg_k, glm::vec3 arg_x_r, glm::vec3 arg_x_c);
	PhysicsSpring(glm::vec3 argPos,double arg_k, double arg_x_r, double arg_x_c, PhysicsMass* arg_massA, PhysicsMass* arg_massB );
	double k;

	double x_r;
	double x_c;

	void applyForce();

private:

};

#endif /* PHYSICSSPRING_H_ */
