/*
 * JellyScene.h
 *
 *  Created on: Mar 19, 2017
 *      Author: bemayer
 */

#ifndef JELLYSCENE_H_
#define JELLYSCENE_H_

#include "Scene.h"
#include "PhysicsMass.h"
#include <glm/glm.hpp>
#include <vector>

using namespace std;

class JellyScene: public Scene {
public:
	JellyScene();
	virtual ~JellyScene();

	vector<vec3> getGeometry();
	void applyTimeStep(float delta_time);
private:
	vector<vec3> vertices;
	vector<PhysicsMass*> masses;


};

#endif /* JELLYSCENE_H_ */
