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
	void makeSpring(PhysicsMass* aMass, PhysicsMass* aMass2);
	void makeGrid();
	vector<PhysicsMass*> masses;
	vector<PhysicsSpring*> springs;
};

#endif /* WINDSCENE_H_ */
