#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

#include "EngineCore/Graphics/Texture2D.hpp"

namespace engine::graphics
{
	Texture2D::~Texture2D()
	{
		if (_id) glDeleteTextures(1, &_id);
	}

	Texture2D::Texture2D(Texture2D&& o) noexcept { *this = std::move(o); }

	Texture2D& Texture2D::operator=(Texture2D&& o) noexcept
	{
		if (this != &o)
		{
			if (_id) glDeleteTextures(1, &_id);
			_id = o._id; _w = o._w; _h = o._h; _internal = o._internal; _src = o._src;
			o._id = 0;
		}
		return *this;
	}

	Texture2D::Texture2D(GLuint id, GLsizei w, GLsizei h, GLenum internal, GLenum src)
		: _id(id), _w(w), _h(h), _internal(internal), _src(src) {}

	std::optional<Texture2D> Texture2D::fromFile(const std::string& path, const TextureParams& p)
	{
		stbi_set_flip_vertically_on_load(p.flipVertical);
		int w = 0, h = 0, ch = 0;
		stbi_uc* bytes = stbi_load(path.c_str(), &w, &h, &ch, 0);
		if (!bytes)
		{
			std::cerr << "ERROR::TEXTURE2D::STBI_LOAD_FAILED: " << path << "\n";
			return std::nullopt;
		}

		GLenum src = GL_RGBA;
		GLenum internal = GL_RGBA8;
		if (ch == 4) { src = GL_RGBA; internal = p.srgb ? GL_SRGB8_ALPHA8 : GL_RGBA8; }
		else if (ch == 3) { src = GL_RGB; internal = p.srgb ? GL_SRGB8 : GL_RGB8; }
		else if (ch == 1) { src = GL_RED; internal = GL_R8; } // grayscale fallback
		else { std::cerr << "ERROR::TEXTURE2D::UNSUPPORTED_CHANNEL_COUNT: " << ch << "\n"; }

		GLuint id = 0;
		glGenTextures(1, &id);

		// Save and restore state to avoid leaking global GL state.
		GLint prevTex = 0, prevUnpack = 4;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &prevTex);
		glGetIntegerv(GL_UNPACK_ALIGNMENT, &prevUnpack);

		glBindTexture(GL_TEXTURE_2D, id);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, internal, w, h, 0, src, GL_UNSIGNED_BYTE, bytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, p.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, p.wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, p.minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, p.magFilter);

		if (p.generateMipmaps) glGenerateMipmap(GL_TEXTURE_2D);

		glPixelStorei(GL_UNPACK_ALIGNMENT, prevUnpack);
		glBindTexture(GL_TEXTURE_2D, (GLuint)prevTex);

		stbi_image_free(bytes);
		return Texture2D{ id, (GLsizei)w, (GLsizei)h, internal, src };
	}

	void Texture2D::bind(GLenum unit) const
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, _id);
	}
}