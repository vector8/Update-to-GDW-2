#version 420

uniform vec4 lightPos;

// color
uniform vec4 objectColor;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;

// scalars
uniform float lightSpecularExponent;
uniform float attenuationConstant;
uniform float attenuationLinear;
uniform float attenuationQuadratic;

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec4 outColor;

void main()
{
	outColor.rgb = lightAmbient;

	// account for rasterizer interpolating
	vec3 norm = normalize(normal);

	vec3 lightVec = lightPos.xyz - position;
	float dist = length(lightVec);
	vec3 lightDir = lightVec / dist;
	
	float NdotL = dot(norm, lightDir);
	
	if(NdotL > 0.0)
	{
		// the light contributes to this surface

		// Calculate the attenuation (falloff)
		float attenuation = 1.0 / (attenuationConstant + (attenuationLinear * dist) + (attenuationQuadratic * dist * dist));

		// Calculate the diffuse contribution
		outColor.rgb += lightDiffuse * NdotL * attenuation;

		// Blinn-Phong half vector
		float NdotHV = max(dot(norm, normalize(lightDir + normalize(-position))), 0.0);

		// Calculate the specular contribution
		outColor.rgb += lightSpecular * pow(NdotHV, lightSpecularExponent) * attenuation;
	}

	outColor.rgb *= objectColor.rgb;
	outColor.a = objectColor.a;
}