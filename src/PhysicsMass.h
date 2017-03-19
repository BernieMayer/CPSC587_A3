/*
 * PhysicsBox.h
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#ifndef PHYSICSMASS_H_
#define PHYSICSMASS_H_

#include <vector>
#include <iostream>
#include "PhysicsObject.h"

using namespace std;
using namespace glm;

class PhysicsMass : public PhysicsObject {
public:
	PhysicsMass();
	virtual ~PhysicsMass();

	PhysicsMass(glm::vec3 arg_position, float arg_mass);

	void setLocation(glm::vec3 aLocation);

	float getMass();

	vec3 getVelocity();

	void applyForce(glm::vec3 forceVector);
	void zeroOutForce();

	void resolveForces(float dt);

	bool isFixed;


private:
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;

	float mass;

	vec3 total_force;

	vec3 velocity;
};

#endif /* PHYSICSMASS_H_ */
