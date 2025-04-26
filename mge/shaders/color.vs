////DIFFUSE COLOR VERTEX SHADER
//
//#version 330 // for glsl version (12 is for older versions , say opengl 2.1
//
//in vec3 vertex;
//in vec3 normal;
//in vec2 uv;
//
//uniform	mat4 	projectionMatrix;
//uniform	mat4 	viewMatrix;
//uniform	mat4 	modelMatrix;
//
//void main( void ){
//    	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);
//}
//DIFFUSE COLOR VERTEX SHADER
#version 400
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

uniform float lightIntensity;

void main( void ){
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);
}