/*
 * SceneShader.cpp
 *
 *  Created on: Nov 17, 2015
 *      Author: acarocha
 */

#include "SceneShader.h"
static float PI = 3.14159265359;


SceneShader::SceneShader(): Shader()
{
	_programPlane = 0;
	_programMesh = 0;
	_planeVertexArray = -1;
	_planeVertexArray = -1;
	_mvUniform = -1;
	_projUniform = -1;
	_zTranslation = 1.0;
	_aspectRatio = 1.0;
	_xRot = 0.0;
	_yRot = 0.0;
	lightPosition = glm::vec3(0.5, 0.5, 0.5);


	pointLocation = glm::vec3(0.0, 0.8, 0.0);

	springScene = new MassSpringScene();

	springLine.push_back(glm::vec3(0, 0.2, 0));
	springLine.push_back(glm::vec3(0, 0.8, 0.0));



	scene_Type = SceneType::MASS_SPRING_SCENE;

	springColors.push_back(glm::vec3(1.0,0.0,0));
	springColors.push_back(glm::vec3(1.0,0.0,0));




	scene = new PendulumScene();

	springLine = scene->getGeometry();


	//setting up the colors right
	for (auto a: springLine)
	{
		springColors.push_back(glm::vec3(1.0,0.0, 0.0));
	}





}

SceneShader::SceneShader(SceneType type) : SceneShader()
{


	if (type == SceneType::PENDULUM_SCENE)
	{
		//set up the scene for

		springLine.clear();


		PendulumScene* aScene = new PendulumScene();


		//scene = aScene;


		springLine = aScene->getGeometry();


		//set up the springColors..

	}

}


//This method is used to switch scenes
// TODO: Rename a so that is it better named
void SceneShader::switchScene(SceneType type)
{
	if (type == SceneType::MASS_SPRING_SCENE)
	{
		//switch the scene to the mass_spring_scene

		scene = new MassSpringScene();

		springLine = scene->getGeometry();

		springColors.clear();


		//setting up the colors right
		for (auto a: springLine)
		{
			springColors.push_back(glm::vec3(1.0,0.0, 0.0));
		}


		scene_Type = SceneType::MASS_SPRING_SCENE;



	} else if (type == SceneType::PENDULUM_SCENE)
	{
		//set up the pendulum scene
		scene = new PendulumScene();

		springLine = scene->getGeometry();

		springColors.clear();


		//setting up the colors right
		for (auto a: springLine)
		{
			springColors.push_back(glm::vec3(1.0,0.0, 0.0));
		}
		scene_Type = SceneType::PENDULUM_SCENE;
	} else if (type == SceneType::JELLY_SCENE)
	{
		scene = new JellyScene();

		springLine = scene->getGeometry();

		springColors.clear();

		for (auto a: springLine)
		{
			springColors.push_back(glm::vec3(1.0, 0.0, 0.0));
		}
		scene_Type = SceneType::JELLY_SCENE;
	} else if (type == SceneType::CLOTH_SCENE)
	{
		delete scene;
		scene = new ClothScene();

		springLine = scene->getGeometry();

		springColors.clear();

		for (auto a: springLine)
		{
			springColors.push_back(glm::vec3(1.0,0.0,0.0));
		}
		scene_Type = SceneType::CLOTH_SCENE;
	}


}


void SceneShader::readMesh( std::string filename )
{
	_mesh = trimesh::TriMesh::read(filename);

	_mesh->need_bbox();
	_mesh->need_faces();
	_mesh->need_normals();
	_mesh->need_bsphere();

	for(unsigned int i = 0; i < _mesh->faces.size(); i++)
	{
   	_triangleIndices.push_back(_mesh->faces[i][0]);
		_triangleIndices.push_back(_mesh->faces[i][1]);
		_triangleIndices.push_back(_mesh->faces[i][2]);
	}
}



void SceneShader::createVertexBuffer()
{
	//create plane geometry
	static const GLfloat quadData[] =
	{
                        -1.0f, 0.0f, -1.0f,
                        -1.0f, 0.0f, 1.0f,
                        1.0f, 0.0f, -1.0f,
                        1.0f, 0.0f, 1.0f,
	};

	//passing model attributes to the GPU
	//plane
	glGenVertexArrays(1, &_planeVertexArray);
	glBindVertexArray(_planeVertexArray);

	glGenBuffers(1, &_planeVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _planeVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof (quadData), quadData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);



	//read and create mesh geometry
	readMesh("./models/cube.obj");
	model_scale = 0.05;
	model_y_position = 0.2;

	model_pos = glm::vec3(0, model_y_position, 0);


	//triangle mesh
	glGenVertexArrays(1, &_meshVertexArray);
	glBindVertexArray(_meshVertexArray);

	glGenBuffers(1, &_meshVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _meshVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,  _mesh->vertices.size() * sizeof (trimesh::point), _mesh->vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	//TODO normals


        glGenBuffers(1, &_meshNormalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _meshNormalBuffer);
        glBufferData(GL_ARRAY_BUFFER,  _mesh->normals.size() * sizeof (trimesh::vec), _mesh->normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);








	glGenBuffers(1, &_meshIndicesBuffer );
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _meshIndicesBuffer );
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _triangleIndices.size()*sizeof(unsigned int), _triangleIndices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	 glGenVertexArrays(1, &_linesVertexArray);
	    glBindVertexArray(_linesVertexArray);


	    glGenBuffers(1, &_linesVertexBuffer);
	    glBindBuffer(GL_ARRAY_BUFFER, _linesVertexBuffer);
	    glBufferData(GL_ARRAY_BUFFER, springLine.size() * sizeof(glm::vec3), springLine.data(), GL_STATIC_DRAW);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	    glEnableVertexAttribArray(0);

	    glGenBuffers(1, &_linesColorBuffer);
	    glBindBuffer(GL_ARRAY_BUFFER, _linesColorBuffer);
	    glBufferData(GL_ARRAY_BUFFER, springColors.size() * sizeof(glm::vec3), springColors.data(), GL_STATIC_DRAW);
	    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	    glEnableVertexAttribArray(1);

}


void SceneShader::startup()
{
	_programPlane = compile_shaders("./shaders/plane.vert", "./shaders/plane.frag");

	_programMesh = compile_shaders("./shaders/mesh.vert", "./shaders/mesh.frag");

	_programLight = compile_shaders("./shaders/light.vert", "./shaders/light.frag");

	_programBasic = compile_shaders("./shaders/simple.vert", "./shaders/simple.frag");

	createVertexBuffer();

}

void SceneShader::renderPlane()
{
	glBindVertexArray(_planeVertexArray);

	glUseProgram(_programPlane);

	//scene matrices and camera setup
	glm::vec3 eye(0.0f,0.3f, 2.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);

	_modelview = glm::lookAt( eye, center, up);

	glm::mat4 identity(1.0f);
	_projection = glm::perspective( 45.0f, _aspectRatio, 0.01f, 100.0f);

	glm::mat4 rotationX = glm::rotate(identity, _yRot  * PI/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

   _modelview *=  rotationX;
	
	//Uniform variables
	glUniformMatrix4fv(glGetUniformLocation(_programPlane, "modelview"), 1, GL_FALSE, glm::value_ptr(_modelview));
	glUniformMatrix4fv(glGetUniformLocation(_programPlane, "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

	glUniform3fv(glGetUniformLocation(_programPlane, "lightPosition"), 1, glm::value_ptr(lightPosition) );

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
}

void SceneShader::renderMesh()
{
	glBindVertexArray(_meshVertexArray);

	glUseProgram(_programMesh);

	springScene->applyTimeStep(0.0025f);

	if (scene_Type == SceneType::MASS_SPRING_SCENE)
		meshLocation = springScene->getLocationOfMass();


	//scene matrices and camera setup
	glm::vec3 eye(0.0f, 0.3f, 2.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);

	_modelview = glm::lookAt( eye, center, up);

	_projection = glm::perspective( 45.0f, _aspectRatio, 0.01f, 100.0f);

	glm::mat4 identity(1.0f);

	glm::mat4 rotationX = glm::rotate(identity, _yRot  * PI/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

   _modelview *=  rotationX;

	//uniform variables
	glUniformMatrix4fv(glGetUniformLocation(_programMesh, "modelview"), 1, GL_FALSE, glm::value_ptr(_modelview));
	glUniformMatrix4fv(glGetUniformLocation(_programMesh, "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

	glUniform1f(glGetUniformLocation(_programMesh, "model_scale"), model_scale);
	//glUniform1f(glGetUniformLocation(_programMesh, "model_y_position"), model_y_position);
	glUniform3fv(glGetUniformLocation(_programMesh, "model_position"), 1, glm::value_ptr(meshLocation));

	glUniform3fv(glGetUniformLocation(_programMesh, "lightPosition"), 1, glm::value_ptr(lightPosition) );

	glDrawElements( GL_TRIANGLES, _mesh->faces.size()*3, GL_UNSIGNED_INT, 0 );

	glBindVertexArray(0);
}


void SceneShader::renderLines()
{

	//change this to be a line between the top of the spring location and the bottom
	//spring


	glBindVertexArray(_linesVertexArray);
	glUseProgram(_programBasic);


	//scene matrices and camera setup
	glm::vec3 eye(0.0f, 0.3f, 2.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);

	_modelview = glm::lookAt( eye, center, up);

	_projection = glm::perspective( 45.0f, _aspectRatio, 0.01f, 100.0f);

	glm::mat4 identity(1.0f);

	glm::mat4 rotationX = glm::rotate(identity, _yRot  * PI/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    _modelview *=  rotationX;

	//uniform variables
	glUniformMatrix4fv(glGetUniformLocation(_programBasic, "modelviewMatrix"), 1, GL_FALSE, glm::value_ptr(_modelview));
	glUniformMatrix4fv(glGetUniformLocation(_programBasic, "perspectiveMatrix"), 1, GL_FALSE, glm::value_ptr(_projection));



	scene->applyTimeStep(0.0025f);
	springLine = scene->getGeometry();
	/*
	springLine.clear();

	springLine.push_back(meshLocation);
	springLine.push_back(pointLocation);
	*/
	glBindBuffer(GL_ARRAY_BUFFER, _linesVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,  springLine.size() * sizeof (glm::vec3), springLine.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _linesColorBuffer);
	glBufferData(GL_ARRAY_BUFFER,  springColors.size() * sizeof (glm::vec3), springColors.data(), GL_STATIC_DRAW);

	if (scene_Type == SceneType::CLOTH_SCENE)
		glPointSize(3.0f);
	else
		glPointSize(15.0f);

	glDrawArrays(GL_LINE_STRIP, 0, springLine.size());
	glDrawArrays(GL_POINTS, 0, springLine.size());


	glBindVertexArray(0);



}

void SceneShader::renderLight()
{
	glUseProgram(_programLight);

	//scene matrices and camera setup
	glm::vec3 eye(0.0f, 0.3f, 2.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);

	_modelview = glm::lookAt( eye, center, up);

	_projection = glm::perspective( 45.0f, _aspectRatio, 0.01f, 100.0f);

	glm::mat4 identity(1.0f);

	glm::mat4 rotationX = glm::rotate(identity, _yRot  * PI/180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

   _modelview *=  rotationX;

	//uniform variables
	glUniformMatrix4fv(glGetUniformLocation(_programLight, "modelview"), 1, GL_FALSE, glm::value_ptr(_modelview));
	glUniformMatrix4fv(glGetUniformLocation(_programLight, "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

	glUniform3fv(glGetUniformLocation(_programLight, "lightPosition"), 1, glm::value_ptr(lightPosition) );

	glPointSize(30.0f);
	glDrawArrays( GL_POINTS, 0, 1);

}

void SceneShader::render()
{
	renderPlane();
	//renderMesh();
	renderLines();
	renderLight();
}

void SceneShader::setZTranslation(float z)
{
	_zTranslation = z;
}

void SceneShader::setAspectRatio(float ratio)
{
	_aspectRatio = ratio;
}

void SceneShader::setRotationX( float x )
{
	_xRot = x;
}

void SceneShader::setRotationY( float y )
{
	_yRot = y;
}

void SceneShader::shutdown()
{
	glDeleteBuffers(1, &_meshVertexBuffer);
	glDeleteBuffers(1, &_meshNormalBuffer);
	glDeleteBuffers(1, &_meshIndicesBuffer );
	glDeleteVertexArrays(1, &_meshVertexArray);
	glDeleteVertexArrays(1, &_planeVertexArray);
}

void SceneShader::updateLightPositionX(float x)
{
	lightPosition.x += x;
}

void SceneShader::updateLightPositionY(float y)
{
	lightPosition.y += y;
}

void SceneShader::updateLightPositionZ(float z)
{
	lightPosition.z += z;
}

SceneShader::~SceneShader()
{
	shutdown();
}
