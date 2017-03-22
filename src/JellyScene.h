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
#include "PhysicsSpring.h"
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

class JellyScene: public Scene {
public:
	JellyScene();
	virtual ~JellyScene();

	vector<vec3> getGeometry();
	void applyTimeStep(float delta_time);
private:

	void makeVoxelGrid();
	void subdivideJellyCube();
	void makeSpringUsingMass(PhysicsMass* aMass, PhysicsMass* aMass2);
    //void makeSpring(vec3 aPoint, vec3 aPoint2); //This is just an easy function to make springs
	vector<PhysicsMass*> masses;
	vector<PhysicsSpring*> springs;


};

#endif /* JELLYSCENE_H_ */
