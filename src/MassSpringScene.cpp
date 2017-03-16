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
	massA = new PhysicsMass(massLocation, 5.0f);
	massB = new PhysicsMass(springLocation, 2.0f);

	massB->isFixed = true;



	vec3 vecBetweenSpringAndMass = springLocation - massLocation;

	double x_r = length( springLocation + 0.2f * vecBetweenSpringAndMass);

	double x_c = length(massLocation - springLocation);

	spring = new PhysicsSpring(springLocation, 500.0f, x_r, x_c, massA, massB);

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


//Now is functional
void MassSpringScene::applyTimeStep(double deltaTime)
{



	float gravity = -9.8196f;
	float dampeningFactor = 0.5f;

	//zero out all the forces on the masses
		for (PhysicsMass* mass:masses)
		{
			mass->zeroOutForce();
		}

		for (PhysicsMass* mass:masses)
		{
			//apply gravity

			mass->applyForce(mass->getMass() * vec3(0, gravity, 0));


			//apply damping

			vec3 dampeningForce = - dampeningFactor * mass->getVelocity();
			mass->applyForce(dampeningForce);



		}

		//iterate through springs applying

		for (PhysicsSpring* s : springs)
		{
			s->applyForce();
		}


		//Change the velocites and the positions of the masses
		for (PhysicsMass* mass:masses)
		{
			mass->resolveForces((float) deltaTime);
		}


}

