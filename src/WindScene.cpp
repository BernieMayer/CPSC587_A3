/*
 * WindScene.cpp
 *
 *  Created on: Mar 22, 2017
 *      Author: bemayer
 */

#include "WindScene.h"

#include "ClothScene.h"
WindScene::WindScene() {
	// TODO Auto-generated constructor stub
	makeGrid();
}

void WindScene::makeSpring(PhysicsMass* aMass, PhysicsMass* aMass2)
{

	double x_r0 = 0.9 * length(aMass->getPosition() - aMass2->getPosition());


	PhysicsSpring* spring0 = new PhysicsSpring(aMass->getPosition(), 1000.0f, x_r0, 0.0f, aMass, aMass2);
	springs.push_back(spring0);
}

void WindScene::makeGrid()
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

WindScene::~WindScene() {
	// TODO Auto-generated destructor stub
}

vector<vec3> WindScene::getGeometry()
{

}

void WindScene::applyTimeStep(float delta_time)
{


}
