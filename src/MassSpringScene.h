/*
 * MassSpringScene.h
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#ifndef MASSSPRINGSCENE_H_
#define MASSSPRINGSCENE_H_

#include "PhysicsSpring.h"
#include "PhysicsObject.h"
#include <glm/glm.hpp>
#include "PhysicsMass.h"

using namespace glm;

class MassSpringScene {
public:
	MassSpringScene();

	MassSpringScene(vec3 massLocation, vec3 springLocation);
	virtual ~MassSpringScene();

	void applyTimeStep(double delta_time);
	glm::vec3 getLocationOfMass();

	vec3 v_t;



private:
	PhysicsMass* massA;
	PhysicsMass* massB;

	vector<PhysicsMass*> masses;
	vector<PhysicsSpring*> springs;
	PhysicsSpring* spring;
};

#endif /* MASSSPRINGSCENE_H_ */
