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
	massA = new PhysicsMass(massLocation, 2.0f);
	massB = new PhysicsMass(springLocation, 2.0f);

	massB->isFixed = true;



	vec3 vecBetweenSpringAndMass = springLocation - massLocation;

	double x_r = length( springLocation + 0.5f * vecBetweenSpringAndMass);

	double x_c = length(massLocation - springLocation);

	spring = new PhysicsSpring(springLocation, 1000.0f, x_r, x_c, massA, massB);

	v_t = vec3(0,0,0);

	masses.push_back( massA);
	masses.push_back( massB);

	springs.push_back(spring);




}

MassSpringScene::~MassSpringScene() {
	// TODO Auto-generated destructor stub
}

glm::vec3 MassSpringScene::getLocationOfMass()
{
	return massA->getPostion();
}

glm::vec3 MassSpringScene::getLocationOfSpring()
{
	return massB->getPostion();
}


//Not actually functional currently
void MassSpringScene::applyTimeStep(double deltaTime)
{
	vec3 massLocation =  massA->getPostion();
	vec3 springLocation = spring->getPostion();

	double k  = spring->k;
//	/double mass = mass->getMass();

	double x_r = spring->x_r;



	double gravity = -9.81f;

	//zero out all the forces on the masses
		for (PhysicsMass* mass:masses)
		{
			mass->zeroOutForce();
		}

		for (PhysicsMass* mass:masses)
		{
			//apply gravity

			mass->applyForce(vec3(0, -9.81, 0));


			//apply damping

			vec3 dampeningForce = - 0.5f * mass->getVelocity();
			mass->applyForce(dampeningForce);



		}

		//iterate through springs applying

		for (PhysicsSpring* s : springs)
		{
			s->applyForce();
		}

		for (PhysicsMass* mass:masses)
		{
			mass->resolveForces((float) deltaTime);
		}


}

