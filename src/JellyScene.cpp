/*
 * JellyScene.cpp
 *
 *  Created on: Mar 19, 2017
 *      Author: bemayer
 */

#include "JellyScene.h"

JellyScene::JellyScene() {
	// TODO Auto-generated constructor stub

	float scalingFactor = 0.5;

	vec3 p0 = scalingFactor * vec3(0.0, 0.0, 0.0);
	vec3 p1 = scalingFactor * vec3(1.0, 0.0, 0.0);
	vec3 p2 = scalingFactor * vec3(0.0, 1.0, 0.0);
	vec3 p3 = scalingFactor * vec3(1.0, 1.0, 0.0);


	vec3 p4 = scalingFactor * vec3(0.0, 0.0, -1.0);
	vec3 p5 = scalingFactor * vec3(1.0, 0.0, -1.0);
	vec3 p6 = scalingFactor * vec3(0.0, 1.0, -1.0);
	vec3 p7 = scalingFactor * vec3(1.0, 1.0, -1.0);


	PhysicsMass* m0 = new PhysicsMass(p0, 0.5f);
	PhysicsMass* m1 = new PhysicsMass(p1, 0.5f);
	PhysicsMass* m2 = new PhysicsMass(p2, 0.5f);
	PhysicsMass* m3 = new PhysicsMass(p3, 0.5f);



	PhysicsMass* m4 = new PhysicsMass(p4, 0.5f);
	PhysicsMass* m5 = new PhysicsMass(p5, 0.5f);
	PhysicsMass* m6 = new PhysicsMass(p6, 0.5f);
	PhysicsMass* m7 = new PhysicsMass(p7, 0.5f);



	makeSpring(m0, m1);
	makeSpring(m1, m3);
	makeSpring(m3, m2);
	makeSpring(m2, m0);

	makeSpring(m0, m4);
	makeSpring(m1, m5);
	makeSpring(m2, m6);
	makeSpring(m3, m7);



	makeSpring(m4, m5);
	makeSpring(m5, m7);
	makeSpring(m7, m6);
	makeSpring(m6, m4);

	//subdivideJellyCube();


	/*
	makeSpring(p0, p1);
	makeSpring(p1, p3);
	makeSpring(p3, p2);
	makeSpring(p2, p0);
	*/

	/*
	makeSpring(p4, p5);
	makeSpring(p5, p6);
	makeSpring(p6, p7);
	makeSpring(p7, p4);
	*/


}

JellyScene::~JellyScene() {
	// TODO Auto-generated destructor stub
}



//Semi implemented
void JellyScene::applyTimeStep(float delta_time)
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


			//Collision detection with the ground plane
			if (mass->getPosition().y < -0.3)
			{
				vec3 pos = mass->getPosition();
				pos.y = -0.3;
				mass->setLocation(pos);
			}

		}

}

vector<vec3> JellyScene::getGeometry()
{
	vector<vec3> verts;

	for (auto spring: springs)
	{
		verts.push_back(spring->getMassA_Location());
		verts.push_back(spring->getMassB_Location());
	}
	return verts;
}

void JellyScene::makeSpring(PhysicsMass* aMass, PhysicsMass* aMass2)
{
	masses.push_back(aMass);
	masses.push_back(aMass2);

	double x_r0 = 0.2f * length(aMass->getPosition() - aMass2->getPosition());


	PhysicsSpring* spring0 = new PhysicsSpring(aMass->getPosition(),1.5f, x_r0, 0.0f, aMass, aMass2);
	springs.push_back(spring0);



}

void JellyScene::subdivideJellyCube()
{
	int i = 0;
	vec3 initPos = vec3(0,0,0);

	vector<PhysicsMass*> newMassesToAdd;

	for (auto mass: masses)
	{
		//check against every other mass to see if it has a neighbour that is 0.5/4 away in the x

		vec3 pos  = mass->getPosition();
		bool check = false;
		for (auto mass2: masses)
		{


			vec3 pos2 = mass2->getPosition();

			double dist = pos.x - pos2.x;

			if (abs(dist) >= 0.20000 && !check )
			{

				check = true;

			}
		}

		if (check)
		{
			printf("Make a new mass \n");
			vec3 new_pos = pos + vec3(0.2, 0.0, 0.0);
			PhysicsMass* newMass = new PhysicsMass(new_pos, 0.5f);

			makeSpring(mass, newMass);
			newMassesToAdd.push_back(newMass);
		}
	}

	masses.insert(masses.end(), newMassesToAdd.begin(), newMassesToAdd.end());



	//masses.push_back(newMassesToAdd);



}

void JellyScene::makeSpring(vec3 aPoint, vec3 aPoint2)
{

	PhysicsMass* mass0 = new PhysicsMass(aPoint, 0.5f);
	PhysicsMass* mass1 = new PhysicsMass(aPoint2, 0.5f);

	masses.push_back(mass0);
	masses.push_back(mass1);


	double x_r0 = 0.2f * length(aPoint - aPoint2);


	PhysicsSpring* spring0 = new PhysicsSpring(aPoint,1.5f, x_r0, 0.0f, mass0, mass1);
	springs.push_back(spring0);

}
