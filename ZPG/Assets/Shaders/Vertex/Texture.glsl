#version 410

layout(location=0) in vec3 vertexPos;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;
layout(location=3) in vec3 t;
layout(location=4) in vec3 b;

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
out mat3 TBN;

void main () {
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vertexPos, 1.0);

    vec3 vertexPosWorld = (modelMatrix * vec4(vertexPos, 1.0)).xyz;

    vecPos = vertexPos;

    normVec = normalize(transpose(inverse(mat3(modelMatrix))) * normal);

    worldPos = vertexPosWorld;
	
	vec3 T = normalize(vec3(modelMatrix * vec4(t, 0.0)));
	vec3 B = normalize(vec3(modelMatrix * vec4(b, 0.0)));
	vec3 N = normalize(vec3(modelMatrix * vec4(normal, 0.0)));
	TBN = mat3(T, B, N);

	eyeVec = normalize(cameraPos - vertexPosWorld); 

	uvCoord = uv;

}