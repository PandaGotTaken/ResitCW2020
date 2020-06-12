/** \file OpenGLTexture.h
*/
#pragma once

#include <string>

namespace IMAT3905 {

	class OpenGLTexture
	{
	public:
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData); //!< Currently only load single channel bitmaps
		~OpenGLTexture();
		inline unsigned int getWidth() const { return m_width; } //!< Get the width of the texture
		inline unsigned int getHeight() const { return m_height; }; //!< Get the height of the texture
		inline unsigned int getChannels() const { return m_channels; }	//!< Get the number of channels of the texture (1 = Greyscale, 3 = RGB, 4 = RGBA)
		inline unsigned int getSlot() const { return m_TextureSlot; }	//!< Get the memory slot in the GPU where the texture resides
		inline unsigned int getID() const { return m_OpenGL_ID; };
		void bind();
	private:
		unsigned int m_OpenGL_ID; //!< Texture id
		unsigned int m_TextureSlot; //!< GPU slot where texture resides
		unsigned int m_width; //!< Width of the texture in pixels
		unsigned int m_height; //!< Height of the texture in pixels
		unsigned int m_channels; //!< Number of channels (1 = Greyscale, 3 = RGB, 4 = RGBA)

		static unsigned int s_TextureSlot; //!< Next free GPU texture slot 
	};
}