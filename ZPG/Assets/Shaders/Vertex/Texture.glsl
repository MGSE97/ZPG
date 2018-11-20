#version 410

layout(location=0) in vec3 vertexPos;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPos;
uniform vec3 lightPosition;

out vec3 vecPos;
out vec3 worldPos;
out vec3 normVec;
out vec3 eyeVec;
out vec2 uvCoord;

void main () {
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vertexPos, 1.0);

    vec3 vertexPosWorld = (modelMatrix * vec4(vertexPos, 1.0)).xyz;

    vecPos = vertexPos;

    normVec = normalize(transpose(inverse(mat3(modelMatrix))) * normal);

    worldPos = vertexPosWorld;

    eyeVec = normalize(cameraPos - vertexPosWorld); 

	uvCoord = uv;
}