/*
 * MassSpringScene.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#include "MassSpringScene.h"

MassSpringScene::MassSpringScene() {
	// TODO Auto-generated constructor stub

	//set up the physics Objects

	//mass = new PhysicsBox()
}

MassSpringScene::MassSpringScene(vec3 massLocation, vec3 springLocation)
{
	mass = new PhysicsBox(massLocation, 100.0f);

	vec3 vecBetweenSpringAndMass = springLocation - massLocation;

	vec3 x_r = springLocation + 0.5f * vecBetweenSpringAndMass;

	vec3 x_c = massLocation;

	spring = new PhysicsSpring(springLocation, 0.5f, x_r, x_c);

	v_t = vec3(0,0,0);
}

MassSpringScene::~MassSpringScene() {
	// TODO Auto-generated destructor stub
}

glm::vec3 MassSpringScene::getLocationOfMass()
{
	return mass->getPostion();
}


//Not actually functional currently
void MassSpringScene::applyTimeStep(double deltaTime)
{
	vec3 massLocation =  mass->getPostion();
	vec3 springLocation = spring->getPostion();

	double k  = spring->k;
//	/double mass = mass->getMass();

	vec3 x_r = spring->x_r;



	vec3 gravity = vec3(0, 9.81, 0);

	//vec3 newPos = massLocation + v_t * deltaTime;

	//v_t = v_t + [ -k ]

	//v_t = v_t [ ]


}

