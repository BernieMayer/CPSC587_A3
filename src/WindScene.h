/*
 * WindScene.h
 *
 *  Created on: Mar 22, 2017
 *      Author: bemayer
 */

#ifndef WINDSCENE_H_
#define WINDSCENE_H_

#include <vector>

#include "Scene.h"

#include "PhysicsMass.h"
#include "PhysicsSpring.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class WindScene: public Scene {
public:
	WindScene();
	virtual ~WindScene();


	vector<vec3> getGeometry();
	void applyTimeStep(float delta_time);

private:

	vec3 windVelocity;

	float calculateAreaOfTriangle(vec3 tri1, vec3 tri2, vec3 tri3);
	void makeSpring(PhysicsMass* aMass, PhysicsMass* aMass2);
	void makeMasses_Indices(float distance);
	void makeGrid();
	vector<PhysicsMass*> masses;
	vector<PhysicsSpring*> springs;

	vector<int> masses_Indices;	//Should be of size divisible by 3


	const float M_PI_1 = 3.14159265358979323846;
};

#endif /* WINDSCENE_H_ */
