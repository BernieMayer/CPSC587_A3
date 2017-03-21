/*
 * ClothScene.cpp
 *
 *  Created on: Mar 20, 2017
 *      Author: bemayer
 */

#include "ClothScene.h"



ClothScene::ClothScene() {
	// TODO Auto-generated constructor stub

	float scalingFactor = 0.5;

	vec3 p0 = scalingFactor * vec3(0.0, 0.0, 0.0);
	vec3 p1 = scalingFactor * vec3(1.0, 0.0, 0.0);
	vec3 p2 = scalingFactor * vec3(0.0, 1.0, 0.0);
	vec3 p3 = scalingFactor * vec3(1.0, 1.0, 0.0);




	PhysicsMass* m0 = new PhysicsMass(p0, 0.05f);
	m0->isFixed = true;

/*
	int n = 4;
	double delta_x = 0.5/((double) n);


	PhysicsMass* prevMass = m0;
	vec3 currentLocation = p0;
	//make n masses based on the initial location of the mass
	for (int i = 0; i < 5; i++)
	{

		//currentMass += 0.001;
		vec3 nextLocation = currentLocation + vec3(0.1, 0.0, 0.0);

		PhysicsMass* tmpMass = new PhysicsMass(nextLocation, 0.05f);

		makeSpring(prevMass, tmpMass);
		prevMass = tmpMass;
		currentLocation.x += 0.1;

	}
*/
	PhysicsMass* m1 = new PhysicsMass(p1, 0.05f);

	/*
	currentLocation = p1;
	for (int i = 0; i < 5; i++)
		{

			//currentMass += 0.001;
			vec3 nextLocation = currentLocation + vec3(0.0, 0.1, 0.0);

			PhysicsMass* tmpMass = new PhysicsMass(nextLocation, 0.05f);

			makeSpring(prevMass, tmpMass);
			prevMass = tmpMass;
			currentLocation.y += 0.1;

		}
*/
	PhysicsMass* m2 = new PhysicsMass(p2, 0.05f);

	m2->isFixed = true;

	PhysicsMass* m3 = new PhysicsMass(p3, 0.05f);

	masses.push_back(m0);
	masses.push_back(m1);
	masses.push_back(m2);
	masses.push_back(m3);


	subdivideJellyCube();
/*
	makeSpring(m0, m1);
	makeSpring(m1, m3);
	makeSpring(m3, m2);
	makeSpring(m2, m0);
	*/
}

ClothScene::~ClothScene() {
	// TODO Auto-generated destructor stub
}

void ClothScene::subdivideJellyCube()
{

	for (auto mass0:masses)
	{
		vec3 pos0 = mass0->getPosition();
		//check against every other mass
		bool check = false;


		for (auto mass1:masses)
		{
			vec3 pos1 = mass1->getPosition();

			double distance = pos0.x - pos1.x;

			if ( distance < 0.1 )
			{
				check = true;
			}
		}
		if (check)
		{
			vec3 newPos = pos0 + vec3(0.1, 0, 0);
			PhysicsMass* tmp = new PhysicsMass(newPos, 0.05f);

			makeSpring(mass0, tmp);
		}

		check = false;
		for (auto mass1:masses)
		{
			vec3 pos1 = mass1->getPosition();

			double distance = pos0.y - pos1.y;

			if ( distance < 0.1 )
			{
				check = true;
			}
		}

		if (check)
		{
			vec3 newPos = pos0 + vec3(0.0, -0.1, 0);
			PhysicsMass* tmp = new PhysicsMass(newPos, 0.05f);

			makeSpring(mass0, tmp);
		}




	}
}

void ClothScene::makeGrid()
{
	vector<PhysicsMass*> row_current;
	vector<PhysicsMass*> row_previous;

	float x;
	float y;
	x = 0.0;
	y = 0.0;

	PhysicsMass* mass0 = new PhysicsMass(vec3(0, 0, 0));


	PhysicsMass* prevMass = mass0;



	while( x < 0.4)
	{
		x += 0.5/4;

		int i = masses.size();
		//PhysicsMass* newMass =
	}





}

void ClothScene::makeSpring(PhysicsMass* aMass, PhysicsMass* aMass2)
{
	masses.push_back(aMass);
	masses.push_back(aMass2);

	double x_r0 = 0.2f * length(aMass->getPosition() - aMass2->getPosition());


	PhysicsSpring* spring0 = new PhysicsSpring(aMass->getPosition(), 6.0f, x_r0, 0.0f, aMass, aMass2);
	springs.push_back(spring0);



}

vector<vec3> ClothScene::getGeometry()
{
	vector<vec3> verts;
	for (PhysicsSpring* spring:springs)
	{
		verts.push_back(spring->getMassA_Location());
		verts.push_back(spring->getMassB_Location());

	}


	return verts;
}

void ClothScene::applyTimeStep(float delta_time)
{

	float gravity = -9.8196f;
	float dampeningFactor = 0.02f;

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

	//iterate through springs applying spring force where need

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


