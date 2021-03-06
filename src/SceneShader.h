/*
 * SceneShader.h
 *
 *  Created on: Nov 17, 2015
 *      Author: acarocha
 */

#ifndef SCENESHADER_H_
#define SCENESHADER_H_

#include "Shader.h"
#include <vector>

#define GLM_FORCE_RADIANS

#include "TriMesh.h"
#include "MassSpringScene.h"
#include "PendulumScene.h"
#include "JellyScene.h"
#include "ClothScene.h"
#include "WindScene.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>





class SceneShader : public Shader
{
public:

	SceneShader();
	SceneShader(SceneType type);

	~SceneShader();

	void startup ();
	void shutdown ();
	void render();

	void switchScene(SceneType type);

	void renderPlane();
	void renderMesh();
	void renderLight();
	void renderLines();


	void setAspectRatio( float ratio );
	void setZTranslation(float z);
	void setRotationX( float x );
	void setRotationY( float y );

	void updateLightPositionX( float x );
	void updateLightPositionY( float y );
	void updateLightPositionZ( float z );

private:

	/*methods*/

	void readMesh( std::string filename );
	void createVertexBuffer();


	/*variables*/
	GLuint _programLight;
	GLuint _programPlane;
	GLuint _programMesh;
	GLuint _programBasic;

	GLuint _planeVertexArray;
	GLuint _planeVertexBuffer;

	GLuint _meshVertexArray;
	GLuint _meshVertexBuffer;
	GLuint _meshNormalBuffer;
	GLuint _meshIndicesBuffer;

	GLuint _linesVertexArray;
	GLuint _linesVertexBuffer;
	GLuint _linesColorBuffer;

    GLint _mvUniform, _projUniform;

	/* Matrices */
	glm::mat4 _modelview;
	glm::mat4 _projection;

	float _zTranslation;
	float _xRot;
	float _yRot;
	float _aspectRatio;

	float model_scale;
	float model_y_position;


	glm::vec3 meshLocation;
	glm::vec3 pointLocation;
	glm::vec3 model_pos;
	MassSpringScene* springScene;



	trimesh::TriMesh* _mesh;
	std::vector<unsigned int> _triangleIndices;

	std::vector<glm::vec3> springLine;
	std::vector<glm::vec3> springColors;

	glm::vec3 lightPosition;

	SceneType scene_Type;
	Scene* scene;

};

#endif /* SCENESHADER_H_ */
