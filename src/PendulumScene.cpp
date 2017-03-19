/*
 * PendulumScene.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: bemayer
 */

#include "PendulumScene.h"

PendulumScene::PendulumScene() {
	// TODO Auto-generated constructor stub


	vec3 initLocation = vec3(0.0f, 0.8f, 0.0f);
	float currentMass = 0.05f;
	PhysicsMass* initialMass = new PhysicsMass(initLocation,currentMass);
	initialMass->isFixed = false;


	vec3 currentLocation = initLocation;


	PhysicsMass* previousMass = initialMass;
	if (previousMass->isFixed)
		printf("Expected \n");
	else
		printf("Not expected \n");

	masses.push_back(previousMass);
	//make n masses based on the initial location of the mass
	for (int i = 0; i < 1; i++)
	{

		currentLocation.x += 0.1;
		PhysicsMass* aMass = new PhysicsMass(currentLocation, currentMass);




		//add this and the previous mass to a spring

		vec3 springLocation = currentLocation - vec3(0.1f, 0.0f, 0.0f);

		vec3 vecBetweenSpringAndMass = initLocation - currentLocation;

		double x_r = 0.8f * length(vecBetweenSpringAndMass);

		double x_c = 0;

		PhysicsSpring* spring = new PhysicsSpring(springLocation, 1.0f, x_r, x_c, previousMass, aMass);
		previousMass = aMass;

		//add this mass to the mass list

		masses.push_back(aMass);




		//add the spring to the spring list
		springs.push_back(spring);
	}



}

void PendulumScene::test()
{
	std::cout << "test \n";
}


//NOTE: This method assumes that the vector of masses is in order
//Since they are in order at the start and wont change order
vector<vec3> PendulumScene::getGeometry()
{
	vector<vec3> verts;
	for (PhysicsSpring* spring:springs)
	{
		verts.push_back(spring->getMassA_Location());
		verts.push_back(spring->getMassB_Location());

	}


	return verts;


}

//not currently implemented..
void PendulumScene::applyTimeStep(float delta_time)
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

			mass->applyForce(mass->getMass() * vec3(0, gravity, 0));


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
			mass->resolveForces((float) delta_time);
		}

}

PendulumScene::~PendulumScene() {
	// TODO Auto-generated destructor stub
}

