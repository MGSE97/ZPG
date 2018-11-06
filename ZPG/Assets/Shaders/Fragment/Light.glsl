#version 410

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
	LightConfiguration lightConfiguration;
};

struct Light {
	LightConfiguration configuration;
};

uniform Material material;// = Material(vec4(1,1,1,1), LightConfiguration(vec3(1,1,1), 1, vec3(1,1,1), 1, vec3(1,1,1), 1, 8, 1, false));

uniform Light light;

out vec4 frag_colour;

in vec3 normVec;
in vec3 lightVec;
in vec3 eyeVec;
in vec3 worldPos;

void main () {
	/*float ambientStrength = 0.2;
	float diffuseStrength = 0.5;
	float specularStrength = 0.5;
	vec3 lightAmbient = vec3(1.0, 1.0, 1.0);
	vec3 lightDiffuse = vec3(1.0, 1.0, 1.0);
	vec3 lightSpecular = vec3(1.0, 1.0, 1.0);*/

	if(!material.lightConfiguration.useLighting)
		frag_colour = material.color;
	else
	{
		// Ambient part
		vec3 ambient = material.lightConfiguration.ambientColor * material.lightConfiguration.ambientStrength;

		// Diffuse part
		float dotDiff = max(dot(normVec, lightVec), 0.0);
		vec3 diffuse = dotDiff * material.lightConfiguration.diffuseColor * material.lightConfiguration.diffuseStrength;

		// Specular part
		vec3 reflVector = reflect(-lightVec, normVec);
		float allowed = dot(normalize(reflVector), normalize(normVec));
		float dotSpec = allowed > -0.4 ? pow(max(dot(reflVector, eyeVec), 0.0), material.lightConfiguration.specularSize) : 0.0;
		vec3 specular = dotSpec * material.lightConfiguration.specularColor * material.lightConfiguration.specularStrength;
		//allowed = allowed>0.9?allowed:0;
		frag_colour = vec4(
			(
				(ambient  * (light.configuration.ambientColor  * light.configuration.ambientStrength)) + 
				(diffuse  * (light.configuration.diffuseColor  * light.configuration.diffuseStrength)) + 
				(specular * (light.configuration.specularColor * light.configuration.specularStrength))
			) * material.lightConfiguration.globalStrength
		, 1.0) * material.color;
		
//		if(allowed <= -0.4)
//			frag_colour = vec4(1); 
//		else
//		{
//			float dp = dotDiff*material.lightConfiguration.diffuseStrength, 
//				  sp = dotSpec*material.lightConfiguration.specularStrength;
//			frag_colour = vec4(dp == sp && dp == 0, dp > sp ? 1.0 : 0.0 , sp > dp ? 1.0 : 0.0 , 1.0);
//			
//			if(dp == sp && dp == 0)
//				frag_colour = vec4(material.lightConfiguration.ambientStrength, 1, 1, 1);
//			else if(dp > sp)
//				frag_colour = vec4(1, material.lightConfiguration.diffuseStrength, 1, 1); 
//			else 
//				frag_colour = vec4(1, 1, material.lightConfiguration.specularStrength, 1);
//		//	frag_colour = vec4(0, dotDiff, dotSpec, 1);
//		}

		//frag_colour = normalize(vec4(material.lightConfiguration.specularSize));
		//frag_colour = vec4(material.lightConfiguration.ambientColor, 1.0);
		//frag_colour = vec4(material.lightConfiguration.diffuseColor, 1.0);
		//frag_colour = vec4(material.lightConfiguration.specularColor, 1.0);
		//frag_colour = vec4((ambient + diffuse + specular), 1.0) * color;
		//frag_colour = vec4(specular, 1.0);
		//frag_colour = vec4(allowed);
		//frag_colour = vec4(worldPos, 1.0);
		//frag_colour = vec4(normVec, 1.0);
		//frag_colour = vec4(ambient, 1.0)*material.color;
		//frag_colour = vec4(diffuse, 1.0)*material.color;
		//frag_colour = vec4(specular, 1.0)*material.color;
		//frag_colour = vec4 (color, 1.0-color, 0.0, 1.0);
	}
}