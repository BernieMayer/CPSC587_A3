/*
 * Scene.h
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <glm/glm.hpp>

enum SceneType
{
	MASS_SPRING_SCENE,
	PENDULUM_SCENE
};


using namespace glm;
using namespace std;
class Scene {
public:
	Scene();
	virtual ~Scene();

	virtual vector<vec3> getGeometry()         = 0;
	virtual void applyTimeStep(float delta_time)= 0;
};

#endif /* SCENE_H_ */
