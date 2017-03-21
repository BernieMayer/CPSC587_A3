/*
 * ClothScene.h
 *
 *  Created on: Mar 20, 2017
 *      Author: bemayer
 */

#ifndef CLOTHSCENE_H_
#define CLOTHSCENE_H_

#include <vector>

#include "PhysicsMass.h"
#include "PhysicsSpring.h"
#include "Scene.h"

using namespace std;
using namespace glm;

class ClothScene: public Scene {
public:
	ClothScene();
	virtual ~ClothScene();


	vector<vec3> getGeometry();
	void applyTimeStep(float delta_time);
private:

	void makeGrid();
	void subdivideJellyCube();
	void makeSpring(PhysicsMass* aMass, PhysicsMass* aMass2);

	vector<PhysicsMass*> masses;
	vector<PhysicsSpring*> springs;
};


#endif /* CLOTHSCENE_H_ */
