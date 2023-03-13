#pragma once

#include "MeshModel.h"
#include "Camera.h"

struct Scene
{
	Camera Camera;

	// Components
	std::vector<MeshModel> ModelList;

	Scene() = default;
	Scene(const Scene&) = default;
};