#pragma once

#include "MeshModel.h"
#include "Camera.h"

struct CameraComponent
{
	glm::mat4 ViewProjectionMatrix;
	glm::mat3 InverseTransposeViewMatrix;
	glm::vec3 GazeDirection;
};

struct Scene
{
	Camera Camera;

	// Components
	std::vector<MeshModel> ModelList;

	Scene() = default;
	Scene(const Scene&) = default;
};