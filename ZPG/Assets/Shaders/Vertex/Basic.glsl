﻿#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vertNormal;

uniform mat4 modelMatrix;

void main() {
	gl_Position = modelMatrix * vec4 (vp, 1.0);
}