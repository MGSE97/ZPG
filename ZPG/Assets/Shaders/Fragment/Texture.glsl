#version 400

struct LightConfiguration {
	vec3 ambientColor;
	float ambientStrength;

	vec3 diffuseColor;
	float diffuseStrength;

	vec3 specularColor;
	float specularStrength;
	int specularSize;

	float globalStrength;
	bool useLighting;
};

struct Material {
	vec4 color;
	sampler2D baseTexture;
	bool hasTexture;
	LightConfiguration lightConfiguration;
};

struct Light {
	vec3 position;
	LightConfiguration configuration;
};

#define M_PI 3.1415926535897932384626433832795
#define MAX_DISTANCE 20.0

uniform Material material;// = Material(vec4(1,1,1,1), LightConfiguration(vec3(1,1,1), 1, vec3(1,1,1), 1, vec3(1,1,1), 1, 8, 1, false));

#define MAX_LIGHTS 10
uniform int lightCount;
uniform Light light[MAX_LIGHTS];

out vec4 frag_colour;

in vec3 verPos;
in vec3 normVec;
in vec3 eyeVec;
in vec3 worldPos;
in vec2 uvCoord;

vec3 CalculateLight(Light light, vec3 ambient);

void main () {
	/*float r = sqrt(verPos.x*verPos.x + verPos.y*verPos.y + verPos.z*verPos.z);
	vec2 nUV = normalize(vec2(atan(verPos.z,verPos.x)/M_PI/2.0,acos(verPos.y/r)/M_PI));*/
	if(!material.lightConfiguration.useLighting)
		frag_colour = material.color;
	else
	{
		int usedLightsCount = lightCount > MAX_LIGHTS ? MAX_LIGHTS : lightCount;
		vec3 result = vec3(0.0);
		// Ambient part
		vec3 ambient = material.lightConfiguration.ambientColor * material.lightConfiguration.ambientStrength;

		// Calculate lights
		for(int i = 0; i < usedLightsCount; i++)
			if(distance(light[i].position, worldPos) < MAX_DISTANCE)
				result += CalculateLight(light[i], ambient);

		frag_colour = vec4(result+ambient, 1.0) * material.color;
	}
	if(material.hasTexture)
		frag_colour = frag_colour * texture(material.baseTexture, uvCoord);
	//frag_colour = vec4(uvCoord, 1, 1);
}

vec3 CalculateLight(Light light, vec3 ambient)
{
	// Get position
	vec3 lightVec = normalize(light.position - worldPos);

	// Diffuse part
	float dotDiff = max(dot(normVec, lightVec), 0.0);
	vec3 diffuse = dotDiff * material.lightConfiguration.diffuseColor * material.lightConfiguration.diffuseStrength;

	// Specular part
	vec3 reflVector = reflect(-lightVec, normVec);
	float allowed = dot(normalize(reflVector), normalize(normVec));
	float dotSpec = allowed > -0.4 ? pow(max(dot(reflVector, eyeVec), 0.0), material.lightConfiguration.specularSize) : 0.0;
	vec3 specular = dotSpec * material.lightConfiguration.specularColor * material.lightConfiguration.specularStrength;
	//allowed = allowed>0.9?allowed:0;
	return
		(
			(ambient  * (light.configuration.ambientColor  * light.configuration.ambientStrength)) + 
			(diffuse  * (light.configuration.diffuseColor  * light.configuration.diffuseStrength)) + 
			(specular * (light.configuration.specularColor * light.configuration.specularStrength))
		) * material.lightConfiguration.globalStrength * light.configuration.globalStrength * ((MAX_DISTANCE - distance(light.position, worldPos))/MAX_DISTANCE);
}