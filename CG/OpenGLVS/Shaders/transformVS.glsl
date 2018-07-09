#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexColor;

//Send data to the fragment shader
out vec2 UV;
out vec3 vcolor;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

	// Computes the vertex position
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
	
	UV = vertexUV;

	vcolor = vertexColor;
}

