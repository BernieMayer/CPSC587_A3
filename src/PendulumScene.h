/*
 * PendulumScene.h
 *
 *  Created on: Mar 16, 2017
 *      Author: bemayer
 */

#ifndef PENDULUMSCENE_H_
#define PENDULUMSCENE_H_


#include <vector>
#include "PhysicsSpring.h"
#include "PhysicsObject.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include "PhysicsMass.h"


using namespace std;
using namespace glm;

class PendulumScene : public Scene {
public:
	PendulumScene();
	virtual ~PendulumScene();

	void applyTimeStep(float delta_time);
	vector<vec3> getGeometry();

	void test();



private:
	vector<vec3> vertices;
	vector<PhysicsMass*> masses;
	vector<PhysicsSpring*> springs;
};

#endif /* PENDULUMSCENE_H_ */
