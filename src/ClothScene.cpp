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

	PhysicsMass* m1 = new PhysicsMass(p1, 0.05f);
	PhysicsMass* m2 = new PhysicsMass(p2, 0.05f);

	m2->isFixed = true;

	PhysicsMass* m3 = new PhysicsMass(p3, 0.05f);

	makeSpring(m0, m1);
	makeSpring(m1, m3);
	makeSpring(m3, m2);
	makeSpring(m2, m0);

}

ClothScene::~ClothScene() {
	// TODO Auto-generated destructor stub
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


