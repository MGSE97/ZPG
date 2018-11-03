#version 410

uniform vec4 color;
uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform float lightStrength;
uniform int specularSize;

uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform bool useLighting;

out vec4 frag_colour;

in vec3 normVec;
in vec3 lightVec;
in vec3 eyeVec;
in vec3 worldPos;

void main () {
/*
	float ambientStrength = 0.2;
	float diffuseStrength = 0.5;
	float specularStrength = 0.5;
	vec3 lightAmbient = vec3(1.0, 1.0, 1.0);
	vec3 lightDiffuse = vec3(1.0, 1.0, 1.0);
	vec3 lightSpecular = vec3(1.0, 1.0, 1.0);*/

	if(!useLighting)
		frag_colour = color;
	else
	{
		// Ambient part
		vec3 ambient = ambientColor * ambientStrength;

		// Diffuse part
		float dotDiff = max(dot(normVec, lightVec), 0.0);
		vec3 diffuse = dotDiff * diffuseColor * diffuseStrength;

		// Specular part
		vec3 reflVector = reflect(-lightVec, normVec);
		float allowed = dot(normalize(reflVector), normalize(normVec));
		float dotSpec = allowed > -0.4 ? pow(max(dot(reflVector, eyeVec), 0.0), specularSize) : 0.0;
		vec3 specular = dotSpec * specularColor * specularStrength;
		//allowed = allowed>0.9?allowed:0;
		frag_colour = vec4((ambient + diffuse + specular)*lightColor*lightStrength, 1.0)*color;
		//frag_colour = vec4((ambient + diffuse + specular), 1.0) * color;
		//frag_colour = vec4(specular, 1.0);
		//frag_colour = vec4(allowed);
		//frag_colour = vec4(worldPos, 1.0);
		//frag_colour = vec4(normVec, 1.0);
		//frag_colour = vec4(ambient*color, 1.0);
		//frag_colour = vec4(diffuse*color, 1.0);
		//frag_colour = vec4(specular*color, 1.0);
		//frag_colour = vec4 (color, 1.0-color, 0.0, 1.0);
	}
}