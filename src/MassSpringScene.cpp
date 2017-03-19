/*
 * MassSpringScene.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#include "MassSpringScene.h"

/*
MassSpringScene::MassSpringScene() {
	// TODO Auto-generated constructor stub

	//set up the physics Objects

	//mass = new PhysicsBox()
}
*/

MassSpringScene::MassSpringScene(vec3 massLocation, vec3 springLocation) :Scene()
{

	massA = new PhysicsMass(massLocation, 0.05f);
	massB = new PhysicsMass(springLocation, 1.0f);

	massB->isFixed = true;



	vec3 vecBetweenSpringAndMass = springLocation - massLocation;

	double x_r =  0.8 * length(vecBetweenSpringAndMass);

	double x_c = length(massLocation - springLocation);

	spring = new PhysicsSpring(springLocation, 5.0f, x_r, x_c, massA, massB);

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


vector<vec3> MassSpringScene::getGeometry()
{
	vector<vec3> locations;

	for (auto mass:masses)
		locations.push_back(mass->getPostion());

	return locations;
}
//Now is functional
void MassSpringScene::applyTimeStep(float deltaTime)
{



	float gravity = -9.8196f;
	float dampeningFactor = 0.05f;

	//zero out all the forces on the masses
		for (PhysicsMass* mass:masses)
		{
			mass->zeroOutForce();
		}

		for (PhysicsMass* mass:masses)
		{
			//apply gravity

			//mass->applyForce(mass->getMass() * vec3(0, gravity, 0));


			//apply damping

			vec3 dampeningForce =  -dampeningFactor * mass->getVelocity();
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

