#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Input.h"

Camera::Camera(float verticalFOV, float nearClip, float farClip)
	:m_VerticalFOV(verticalFOV), m_NearClip(nearClip), m_FarClip(farClip)
{
	m_ForwardDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Position = glm::vec3(0.0f, 0.0f, 2.0f);

}

bool Camera::OnUpdate(float ts)
{
	glm::vec2 mousePosition;
	Input::GetMousePosition(mousePosition.x, mousePosition.y);
	glm::vec2 delta = (mousePosition - m_LastMousePosition) * 0.002f;
	m_LastMousePosition = mousePosition;

	if (!Input::IsMouseButtonPressed(MouseButton::Right))
	{
		Input::SetCursorMode(CursorMode::Normal);
		return false;
	}

	Input::SetCursorMode(CursorMode::Locked);

	bool IsMoved = false;

	constexpr glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
	glm::vec3 rightDirection = glm::cross(m_ForwardDirection, upDirection);

	
	// Camera movements
	if (Input::IsKeyPressed(KeyCode::W))
	{
		m_Position += ts * m_CameraSpeed * m_ForwardDirection;
		IsMoved = true;
		std::cout << "Pressed W\n";
	}

	if (Input::IsKeyPressed(KeyCode::S))
	{
		m_Position -= ts * m_CameraSpeed * m_ForwardDirection;
		IsMoved = true;
		std::cout << "Pressed S\n";
	}

	if (Input::IsKeyPressed(KeyCode::D))
	{
		m_Position += ts * m_CameraSpeed * rightDirection;
		IsMoved = true;
	}

	if (Input::IsKeyPressed(KeyCode::A))
	{
		m_Position -= ts * m_CameraSpeed * rightDirection;
		IsMoved = true;
	}

	if (Input::IsKeyPressed(KeyCode::Q))
	{
		m_Position -= ts * m_CameraSpeed * upDirection;
		IsMoved = true;
	}

	if (Input::IsKeyPressed(KeyCode::E))
	{
		m_Position += ts * m_CameraSpeed * upDirection;
		IsMoved = true;
	}

	// Rotation 
	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		float pitchDelta = delta.y * m_CameraRotationSpeed;
		float yawDelta = delta.x * m_CameraRotationSpeed * (float)m_ViewportWidth / (float)m_ViewportHeight;

		glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
			glm::angleAxis(-yawDelta, glm::vec3(0.0f, 1.0f, 0.0f))));

		m_ForwardDirection = glm::rotate(q, m_ForwardDirection);

		IsMoved = true;
	}

	if (IsMoved)
	{
		RecalculateView();
		RecalculateProjection();
	}

	return IsMoved;
}

void Camera::OnResize(uint32_t width, uint32_t height)
{
	if (width == m_ViewportWidth && height == m_ViewportHeight)
		return;

	m_ViewportWidth = width; 
	m_ViewportHeight = height;

	RecalculateProjection();
	RecalculateView();
}

void Camera::RecalculateProjection()
{
	m_Projection = glm::perspective(glm::radians(m_VerticalFOV),
		(float)m_ViewportWidth / (float)m_ViewportHeight, m_NearClip, m_FarClip);
	m_Projection[1][1] *= -1;
	m_InverseProjection = glm::inverse(m_Projection);

}

void Camera::RecalculateView()
{
	m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0.0f, 1.0f, 0.0f));
	m_InverseView = glm::inverse(m_View);
}
