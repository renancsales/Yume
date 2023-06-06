#version 450

layout(location = 0) out vec4 outColor; // output color

layout(location = 0) in vec3 o_color;
layout(location = 1) in vec2 fragTex;
layout(location = 2) in vec3 v_normal;
layout(location = 3) out vec3 v_gazeDirection;

// Different descriptor set 
layout(set = 1, binding = 0) uniform sampler2D textureSampler;

void main()
{
	vec3 lightDirection = normalize(vec3(0.10, 1.0, 1.0));
	float lightIntensity = 1.0;


	// Set the ambience parameters
	vec4 diffuseColor = texture(textureSampler,fragTex);
	vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 ambienceColor = diffuseColor; //texture(textureSampler,fragTex);
	float intensityAmbience = 0.15;

	outColor.rgb = vec3(1, 0, 0);

	// Blinn material model
	float geometricTerm = dot(lightDirection, v_normal);
	if(geometricTerm > 0.0)
	{
		vec3 H = v_gazeDirection + lightDirection;
		H = normalize(H);

		float specularValue = dot(v_normal, H);
		outColor.rgb = lightIntensity * (0*geometricTerm * diffuseColor.rgb + pow(specularValue, 10) * specularColor.rgb);
	}

	// Add ambience
	outColor.rgb += 0*intensityAmbience * ambienceColor.rgb ;
	outColor.a = 1.0;
	// outColor = texture(textureSampler,fragTex);
	//outColor = vec4(v_normal, 1.0);
}