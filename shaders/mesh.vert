#version 430 core

uniform mat4 modelview;
uniform mat4 projection;
uniform vec3 lightPosition;

uniform float model_scale;

uniform vec3 model_position;
//uniform float model_y_position;

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
//attributes in camera coordinates

out vec3 N;
out vec3 L;
out vec3 V;

void main(void)
{

    vec4 lightCameraSpace = modelview * vec4(lightPosition, 1.0);
    lightCameraSpace.xyz /= lightCameraSpace.w;

    mat3 normalMatrix  = transpose( inverse( mat3(modelview)));



    N = normalize(normalMatrix * normal);
    float scale = model_scale;
    vec3 positionModelSpace = vertex*scale + model_position;
    vec4 positionCameraSpace = modelview * vec4(positionModelSpace, 1.0);

    positionCameraSpace.xyz /= positionCameraSpace.w;

    V = normalize( -positionCameraSpace.xyz);

    L = normalize(lightCameraSpace.xyz - positionCameraSpace.xyz);



    gl_Position = projection * positionCameraSpace;
}
