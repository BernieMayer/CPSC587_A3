/*
 * JellyScene.cpp
 *
 *  Created on: Mar 19, 2017
 *      Author: bemayer
 */

#include "JellyScene.h"

JellyScene::JellyScene() {
	// TODO Auto-generated constructor stub

	makeVoxelGrid();
	/*
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

	return;


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

/*
void JellyScene::makeSpring(PhysicsMass* aMass, PhysicsMass* aMass2)
{
	masses.push_back(aMass);
	masses.push_back(aMass2);

	double x_r0 = 0.2f * length(aMass->getPosition() - aMass2->getPosition());


	PhysicsSpring* spring0 = new PhysicsSpring(aMass->getPosition(),1.5f, x_r0, 0.0f, aMass, aMass2);
	springs.push_back(spring0);



}*/

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

			makeSpringUsingMass(mass, newMass);
			//newMassesToAdd.push_back(newMass);
			//masses.push_back(newMass);
		}
	}

	masses.insert(masses.end(), newMassesToAdd.begin(), newMassesToAdd.end());



	//masses.push_back(newMassesToAdd);



}

void JellyScene::makeVoxelGrid()
{
	vector<PhysicsMass* >currentRow;
	vector<vector<PhysicsMass*>> current_grid;
	vector<vector<vector<PhysicsMass*>>> voxel_grid;


	vec3 initLocation =  vec3(0,0,0);

	float sizeGrid = 0.5;

	float mass = 0.05;
	int n = 5; //number of points in a line in the grid

	vec3 currentLocation = initLocation;


	PhysicsMass* initMass = new PhysicsMass(initLocation, mass);

	masses.push_back(initMass);
	currentRow.push_back(initMass);

	//pre make the first row

	for (int m = 1; m < n; m++)
	{
		currentLocation.y += sizeGrid/(double)n;
		PhysicsMass* newMass = new PhysicsMass(currentLocation, mass);

		makeSpringUsingMass(newMass, currentRow.at(m - 1));
		masses.push_back(newMass);
		currentRow.push_back(newMass);
	}

	current_grid.push_back(currentRow);


	//make the voxel
	for (int i = 0; i < n; i++)
	{

		//making the grids
		for (int j = 1; j < n; j++)
		{
			currentRow.clear();
			currentLocation.y = 0;
			currentLocation.x += sizeGrid/(float)n;
			//making the rows
			for (int k = 0; k < n; k++)
			{

				PhysicsMass* newMass = new PhysicsMass(currentLocation, mass);
				masses.push_back(newMass);
				currentLocation.y += sizeGrid/(double)n;

				if ( k == 0 && i == 0 )
					makeSpringUsingMass(newMass, current_grid.at(j - 1).at(k));


				//makeSpringUsingMass(currentRow.at(j - 1), current_grid.at(k - 1).at(j - 1));
				//makeSpringUsingMass(newMass, current_grid.at(k - 1).at(j - 1));
				//makeSpringUsingMass(newMass, currentRow.at(j - 1));
				currentRow.push_back(newMass);


			}
			current_grid.push_back(currentRow);
			currentRow.clear();
		}
	}
}

void JellyScene::makeSpringUsingMass(PhysicsMass* aMass, PhysicsMass* aMass2)
{
	double x_r0 = 0.9 * length(aMass->getPosition() - aMass2->getPosition());


	PhysicsSpring* spring0 = new PhysicsSpring(aMass->getPosition(), 1000.0f, x_r0, 0.0f, aMass, aMass2);
	springs.push_back(spring0);

}
/*
void JellyScene::makeSpring(vec3 aPoint, vec3 aPoint2)
{

	PhysicsMass* mass0 = new PhysicsMass(aPoint, 0.5f);
	PhysicsMass* mass1 = new PhysicsMass(aPoint2, 0.5f);

	//masses.push_back(mass0);
	//masses.push_back(mass1);


	double x_r0 = 0.2f * length(aPoint - aPoint2);


	PhysicsSpring* spring0 = new PhysicsSpring(aPoint,1.5f, x_r0, 0.0f, mass0, mass1);
	springs.push_back(spring0);

}
*/
