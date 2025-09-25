#pragma once
#include <optional>
#include <glad/glad.h>

namespace engine::graphics
{
	struct TextureParams
	{
		GLint wrapS = GL_CLAMP_TO_EDGE;
		GLint wrapT = GL_CLAMP_TO_EDGE;
		GLint minFilter = GL_NEAREST;
		GLint magFilter = GL_NEAREST;
		bool generateMipmaps = false;
		bool srgb = false;
		bool flipVertical = true;
	};

	class Texture2D
	{
	public:
		Texture2D() = default;
		~Texture2D();

		Texture2D(const Texture2D&) = delete;				// Copy constructor.
		Texture2D& operator=(const Texture2D&) = delete;	// Copy assignment operator.
		Texture2D(Texture2D&&) noexcept;					// Move constructor
		Texture2D& operator=(Texture2D&&) noexcept;			// Move assignment operator.

		static std::optional<Texture2D> fromFile(const std::string& path, const TextureParams& params = {});

		void bind(GLenum unit = 0) const;
		GLuint id() const { return _id; }
		GLsizei width() const { return _w; }
		GLsizei height() const { return _h; }

	private:
		Texture2D(GLuint id, GLsizei w, GLsizei h, GLenum internal, GLenum src);

		GLuint _id = 0;
		GLsizei _w = 0, _h = 0;
		GLenum _internal = GL_RGBA8;
		GLenum _src = GL_RGBA;
	};
}