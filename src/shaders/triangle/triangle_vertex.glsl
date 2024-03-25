#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in vec4 position2;

void main(){
	gl_Position = position2;
}