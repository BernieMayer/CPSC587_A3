/*
 * PhysicsObject.h
 *
 *  Created on: Mar 12, 2017
 *      Author: bemayer
 */

#ifndef PHYSICSOBJECT_H_
#define PHYSICSOBJECT_H_

#include <glm/glm.hpp>

class PhysicsObject {
public:
	PhysicsObject();
	PhysicsObject(glm::vec3 arg_Position);
	virtual ~PhysicsObject();

	glm::vec3 getPostion();

protected:
	glm::vec3 position;
};

#endif /* PHYSICSOBJECT_H_ */
