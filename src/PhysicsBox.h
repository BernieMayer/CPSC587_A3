/*
 * PhysicsBox.h
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#ifndef PHYSICSBOX_H_
#define PHYSICSBOX_H_

#include <vector>
#include "PhysicsObject.h"

using namespace std;

class PhysicsBox : public PhysicsObject {
public:
	PhysicsBox();
	virtual ~PhysicsBox();

	PhysicsBox(glm::vec3 arg_position, double arg_mass);

	void setLocation(glm::vec3 aLocation);

	double getMass();


private:
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;

	double mass;


};

#endif /* PHYSICSBOX_H_ */
