/*
 * MassSpringScene.h
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#ifndef MASSSPRINGSCENE_H_
#define MASSSPRINGSCENE_H_

#include "PhysicsBox.h"
#include "PhysicsSpring.h"
#include "PhysicsObject.h"
#include <glm/glm.hpp>

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
	PhysicsBox* mass;
	PhysicsSpring* spring;
};

#endif /* MASSSPRINGSCENE_H_ */
