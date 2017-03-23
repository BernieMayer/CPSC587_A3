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
	float sizeGrid = 0.5;

	int n = 20; //number of points in a line in the grid
	makeMasses_Indices(sizeGrid/((double) n));

	windVelocity = vec3(10, 10, 0);

}

void WindScene::makeSpring(PhysicsMass* aMass, PhysicsMass* aMass2)
{



	double x_r0 = 1.2 * length(aMass->getPosition() - aMass2->getPosition());


	PhysicsSpring* spring0 = new PhysicsSpring(aMass->getPosition(), 2000.0f, x_r0, 0.0f, aMass, aMass2);
	springs.push_back(spring0);
}

void WindScene::makeMasses_Indices(float distance)
{
	for (int i = 0; i < masses.size(); i++)
	{
		PhysicsMass* mass_i = masses.at(i);
		for (int j = (i + 1); (j < masses.size() && (j > i)); j++)
		{
			PhysicsMass* mass_j = masses.at(j);

			float d  = length((mass_i)->getPosition() - mass_j->getPosition());

			if (d <= (distance + 0.001))
			{
				//printf("Added a mass to the indicies \n");


				for (int k = (i + 1); (k < masses.size() && (k > i) ); k++)
				{
					PhysicsMass* mass_k = masses.at(k);

					float d_1 = length(mass_i->getPosition() - mass_k->getPosition());
					float d_2 = length(mass_k->getPosition() - mass_j->getPosition());

					if (d_1 < (distance + 0.001) && j!= k)
					{

						masses_Indices.push_back(i);
						masses_Indices.push_back(j);
						masses_Indices.push_back(k);
					} else if (d_2 < (distance + 0.001) && j!=k)
					{
						masses_Indices.push_back(i);
						masses_Indices.push_back(j);
						masses_Indices.push_back(k);
					}

				}

			}
		}


			/*
			for (int k = 0; (k < masses.size() && ( k > i && j > i)); k++)
			{
				PhysicsMass* mass_k = masses.at(k);

				float distance_hyp = sqrt( pow(distance, 2) + pow(distance, 2));

				float i_j_distance = length(mass_i->getPosition() - mass_j->getPosition());
				float i_k_distance = length(mass_i->getPosition() - mass_k->getPosition());
				float j_k_distance = length(mass_j->getPosition() - mass_k->getPosition());

				if ( (i_j_distance <= (distance + 0.01)))
				{
					printf("Added a mass to the indicies \n");
					masses_Indices.push_back(i);
					masses_Indices.push_back(j);
					masses_Indices.push_back(k);
				}
			}
			*/
		}

}


//This method will use the location of the vertices
// of a triangle to get the area of it
float WindScene::calculateAreaOfTriangle(vec3 tri1, vec3 tri2, vec3 tri3)
{
	vec3 AB = (tri2 - tri1);
	vec3 AC = (tri3 - tri1);


	float area = 0.5 * length(cross(AB, AC));
	return area;
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


	vector<vec3> verts;

	/*
	 *
	 * Old algorthm
	for (PhysicsSpring* spring:springs)
	{
		verts.push_back(spring->getMassA_Location());
		verts.push_back(spring->getMassB_Location());

	}*/

	//new algorithm

	for (int i = 0 ; i < masses_Indices.size(); i+=3)
	{
		verts.push_back(masses.at(masses_Indices.at(i    ))->getPosition());
		verts.push_back(masses.at(masses_Indices.at(i + 1))->getPosition());
		verts.push_back(masses.at(masses_Indices.at(i + 2))->getPosition());

	}


	return verts;

}

void WindScene::applyTimeStep(float delta_time)
{


	float alpha = 0.6f;
	float gravity = -9.8196f;
	float dampeningFactor = 0.6f;
	vec3 p = vec3(0.2, 0.2, 0.2); //density
	float area = (0.5f) * (0.5f);

	float viscosity = 0.1;
	float radius = 0.01;
//zero out all the forces on the masses
	for (PhysicsMass* mass:masses)
	{
		mass->zeroOutForce();
	}

	vec3 windForce = p * area * (windVelocity * windVelocity);

	for (PhysicsMass* mass:masses)
	{
		//apply gravity

		mass->applyForce(mass->getMass() * vec3(0, gravity, 0));

		//This is the difference between the mass velocity and the wind velocity

		/* Old code to make the windForce

		vec3 v_t = mass->getVelocity() - windVelocity;


		vec3 wind_Force = (float) (6.0f * M_PI_1 * viscosity * radius)  * v_t;
		//mass->applyForce(v_t * alpha);
		mass->applyForce(windForce);
		*/
		//apply damping

		vec3 dampeningForce =  -dampeningFactor * mass->getVelocity();
		mass->applyForce(dampeningForce);



	}


	for (int i = 0; i < masses_Indices.size(); i+=3)
	{
		PhysicsMass* mass0 = masses.at(masses_Indices.at(i    ));
		PhysicsMass* mass1 = masses.at(masses_Indices.at(i + 1));
		PhysicsMass* mass2 = masses.at(masses_Indices.at(i + 2));

		//we need the area of this triangle
		float area = calculateAreaOfTriangle(mass0->getPosition(),mass1->getPosition(), mass2->getPosition());

		vec3 v0 = mass0->getVelocity();
		vec3 v1 = mass1->getVelocity();
		vec3 v2 = mass2->getVelocity();

		vec3 avgVel = (1/3.0f) * (v0 + v1 + v2);

		vec3 v_n = avgVel - windVelocity;

		vec3 p = vec3(0.8, 0.8, 0.8);

		float alpha = 0.5;	//We will only have forces facing the wind (Assumption)

		vec3 forceVec = (area) * (windVelocity * windVelocity) * p;

		mass0->applyForce(forceVec);
		mass1->applyForce(forceVec);
		mass2->applyForce(forceVec);



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
