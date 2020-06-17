#pragma once

#include "core/log.h"
#include "camera.h"
#include "openGL/OpenGLUniformBuffer.h"
#include "openGL/OpenGLShader.h"
#include "openGL/OpenGLVertexArray.h"
#include "openGL/OpenGLTexture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <unordered_map>


namespace IMAT3905
{
	using SceneData = std::unordered_map<std::shared_ptr<OpenGLUniformBuffer>, std::vector<void*>>;

	/**
	* \class Renderer 
	* 3D renderer
	*/
	
	class Renderer {
	public:
		
		static void init(); //!< Initialise the renderer
		static void shutdown(); //!< Shutdown the renderer
		static void beginScene(); //!< Begin the rendering a new scene
		static void endScene(); //!< End the current scene

		static void cameraForward(); //!< Move the camera towards the origin
		static void cameraBack(); //!< Move the camera away from the origin
		static void cameraLeft(); //!< Rotate the camera around the origin
		static void cameraRight(); //!< Rotate the camera around the origin
		static void cameraUp(); //!< Rotate the camera around the origin
		static void cameraDown(); //!< Rotate the camera around the origin

		static void drawCube(const glm::mat4& model, const glm::vec3& halfExtents, const glm::vec3& colour); //!< Draw a cube using and model matrix supplied and an RGB colour
		static void drawSphere(const glm::mat4& model, float radius, const glm::vec3& colour); //!< Draw a sphere using and model matrix supplied and an RGB colour
		static void drawCapsule(const glm::mat4& model, float radius, float height, const glm::vec3& colour); //!< Draw a sphere using and model matrix supplied and an RGB colour

		static unsigned int getFramebufferTextureID(); //!< Get the OpenGL renderer ID of the texture which is rendered to in the final render pass
	private:
	/**
	* \struct RenderData
	* Data internal to the renderer
	*/
		struct RenderData
		{
			SceneData perSceneUniforms;

			glm::vec3 lightPosition;
			glm::vec3 viewPosition;
			glm::vec3 lightColour;

			Camera camera;

			std::shared_ptr<OpenGLUniformBuffer> UBOMatrices;
			std::shared_ptr<OpenGLUniformBuffer> UBOLights;

			std::shared_ptr<OpenGLShader> firstPassShader;
			std::shared_ptr<OpenGLShader> secondPassShader;
			std::shared_ptr<OpenGLTexture> checkerBoard;
			unsigned int checkboardTextureUnit;

			const unsigned int cubeVertexCount = 4;
			const unsigned int cubeIndexCount = 4;
			std::shared_ptr<OpenGLVertexArray> cubeVAO;
			std::shared_ptr<OpenGLVertexBuffer> cubeVBO;
			std::shared_ptr<OpenGLIndexBuffer> cubeIBO;

			const unsigned int sphereVertexCount = 7936;
			const unsigned int sphereIndexCount = 1440;
			std::shared_ptr<OpenGLVertexArray> sphereVAO;
			std::shared_ptr<OpenGLVertexBuffer> sphereVBO;
			std::shared_ptr<OpenGLIndexBuffer> sphereIBO;

			const unsigned int hemisphereVertexCount = 3720;
			const unsigned int hemisphereIndexCount = 675;
			std::shared_ptr<OpenGLVertexArray> hemisphereVAO;
			std::shared_ptr<OpenGLVertexBuffer> hemisphereVBO;
			std::shared_ptr<OpenGLIndexBuffer> hemisphereIBO;

			const unsigned int cylinderVertexCount = 480;
			const unsigned int cylinderIndexCount = 90;
			std::shared_ptr<OpenGLVertexArray> cylinderVAO;
			std::shared_ptr<OpenGLVertexBuffer> cylinderVBO;
			std::shared_ptr<OpenGLIndexBuffer> cylinderIBO;

			const unsigned int screenQuadVertexCount = 4;
			const unsigned int screenQuadIndexCount = 6;
			std::shared_ptr<OpenGLVertexArray>  screenQuadVAO;
			std::shared_ptr<OpenGLVertexBuffer> screenQuadVBO;
			std::shared_ptr<OpenGLIndexBuffer>  screenQuadIBO;

			unsigned int renderPassFBO;
			unsigned int renderPassTextureID;
			unsigned int renderPassTextureUnit;
			unsigned int renderPassDepthBuffer;
		};
		static std::shared_ptr<RenderData> s_data; //!< Internal data for the renderer
	};
}

