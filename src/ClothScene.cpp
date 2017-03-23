/*
 * ClothScene.cpp
 *
 *  Created on: Mar 20, 2017
 *      Author: bemayer
 */

#include "ClothScene.h"



ClothScene::ClothScene() {
	// TODO Auto-generated constructor stub


	makeGrid();

}

ClothScene::~ClothScene() {
	// TODO Auto-generated destructor stub

	masses.clear();
	springs.clear();


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

//This method is the method that the conrstructor will call to make the grid
// of the cloth

void ClothScene::makeGrid()
{
	vector<vector<PhysicsMass*>> grid;
	vector<PhysicsMass*> currentRow;

	vec3 initLocation =  vec3(0,0,0);

	float sizeGrid = 0.5;

	float mass = 0.05;
	int n = 20; //number of points in a line in the grid


	//Note the first row is sorta made manually since the
	//cloth needs two fixed points
	PhysicsMass* mass0 = new PhysicsMass(initLocation, mass);
	masses.push_back(mass0);
	mass0->isFixed = true;
	currentRow.push_back(mass0);


	PhysicsMass* prevMass = mass0;


	vec3 currentLocation = initLocation;
	for (int r = 0; r < (n - 2); r++){
		currentLocation =  currentLocation + vec3(0, sizeGrid/(double)n ,0.0);


		PhysicsMass* newMass = new PhysicsMass(currentLocation, mass);
		masses.push_back(newMass);
		//newMass->isFixed = true; //allows for making the first line
		makeSpring(prevMass, newMass);
		currentRow.push_back(newMass);
		prevMass = newMass;
	}


	currentLocation.y += sizeGrid/(double)n;
	PhysicsMass* finalMass = new PhysicsMass(currentLocation, mass);
	masses.push_back(finalMass);
	finalMass->isFixed = true;

	currentRow.push_back(finalMass);

	makeSpring(prevMass, finalMass);

	grid.push_back(currentRow);

	currentLocation = initLocation;


	for (int i = 1; i < n; i++)
	{

		currentRow.clear();
		currentLocation.x += sizeGrid/(float)n;
		currentLocation.y = 0;
		//make the new row
		for (int j = 0; j < n; j++)
		{

			PhysicsMass* newMass = new PhysicsMass(currentLocation, mass);
			masses.push_back(newMass);
			currentLocation.y += sizeGrid/(float)n;

			if (j == 0) {
				makeSpring(newMass, grid.at(i - 1).at(j));
			} else {
				makeSpring(newMass, grid.at(i - 1).at(j));
				makeSpring(currentRow.at(j - 1), grid.at(i - 1).at(j - 1));
				makeSpring(newMass, grid.at(i - 1).at(j - 1));
				makeSpring(newMass, currentRow.at(j -1));
			}
			currentRow.push_back(newMass);
		}

		grid.push_back(currentRow);
	}

}

void ClothScene::makeSpring(PhysicsMass* aMass, PhysicsMass* aMass2)
{
	double x_r0 = 0.9 * length(aMass->getPosition() - aMass2->getPosition());


	PhysicsSpring* spring0 = new PhysicsSpring(aMass->getPosition(), 1000.0f, x_r0, 0.0f, aMass, aMass2);
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
	float dampeningFactor = 0.8f;

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


