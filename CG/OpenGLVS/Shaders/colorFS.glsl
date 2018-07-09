#version 330 core

// Interpolated values from the vertex shaders
//in vec2 UV;
in vec3 vcolor;

// Ouput data
out vec4 color;

void main(){
	color = vec4(vcolor, 1.0f);
}