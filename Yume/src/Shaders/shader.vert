#version 450 

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 normalCoords;


layout(set = 0, binding = 0) uniform cameraComponent {
	mat4 projectionViewMtx;
	mat3 inverseTransposeViewMatrix;
	vec3 gazeDirection;
} camera;

// not in use, left for reference
layout(set = 0, binding = 1) uniform uboModel {
	mat4 model;
} modelMtx;

layout(push_constant) uniform PushModel {
	mat4 model;
} pushModel;

layout(location = 0) out vec3 out_color;
layout(location = 1) out vec2 fragTex;
layout(location = 2) out vec3 v_normal;
layout(location = 3) out vec3 v_gazeDirection;

void main()
{
	gl_Position = camera.projectionViewMtx * modelMtx.model *vec4(position, 1.0);
	out_color = color;
	fragTex = texCoords;
	mat3 MVI = camera.inverseTransposeViewMatrix*transpose(inverse(mat3(modelMtx.model)));
	v_normal = normalize(MVI*normalCoords);
	v_gazeDirection = normalize(MVI*camera.gazeDirection);
}