#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = default;
	Camera(float verticalFOV, float nearClip, float farClip);
	~Camera() = default;


	bool OnUpdate(float ts);
	void OnResize(uint32_t width, uint32_t height);

	void SetProjectionMatrix(glm::mat4& projection) { m_Projection = projection; }
	void SetViewMatrix(glm::mat4& view) { m_View = view; }
	void SetCameraPositionAndDirection(glm::vec3& position, glm::vec3& fwdDirection) { m_Position = position; m_ForwardDirection = fwdDirection; }

	glm::mat4& GetProjectionViewMatrix() { return m_Projection * m_View; }

private:
	void RecalculateProjection();
	void RecalculateView();

private:
	glm::mat4 m_Projection{ 1.0f };
	glm::mat4 m_View{ 1.0f };
	glm::mat4 m_InverseProjection{ 1.0f };
	glm::mat4 m_InverseView{ 1.0f };

	float m_VerticalFOV = 45.0f;
	float m_NearClip = 0.1f;
	float m_FarClip = 100.0f;

	glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_ForwardDirection{ 0.0f, 0.0f, 0.0f };

	glm::vec2 m_LastMousePosition{ 0.0f, 0.0f };

	float m_CameraSpeed = 1.0f;
	float m_CameraRotationSpeed = 0.25f;

	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

};

