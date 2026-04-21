#pragma once
#include <mat4x4.hpp>

namespace engine::renderer
{
	class Camera
	{
	public: 
		virtual ~Camera();

		virtual const glm::mat4& view() const = 0;
		virtual const glm::mat4& proj() const = 0;
		virtual const glm::mat4& viewProj() const = 0;
		virtual const glm::vec3& position() const = 0;

	protected: 
		Camera() = default;

		// Non-copyable/non-movable
		Camera(const Camera&) = delete;						// Copy constructor.
		Camera& operator=(const Camera&) = delete;			// Copy assignment operator.
		Camera(Camera&&) noexcept = delete;					// Move constructor.
		Camera& operator=(Camera&&) noexcept = delete;		// Move assignment operator.
	};
}