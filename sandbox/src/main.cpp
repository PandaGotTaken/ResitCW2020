#include "IMAT3905.h"
#include <iostream>

int main()
{
	// Start the singleton application
	std::shared_ptr<SC::Application> application(SC::Application::getInstance());
	application->init();

	// Start the renderer
	SC::Renderer::init();

	float elapsedTime = 0.f;

	glm::mat4 cubeModel = glm::mat4(1.0f);
	glm::vec3 cubeColour(0.f, 1.0f, 0.f);

	glm::mat4 sphereModel = glm::translate(glm::mat4(1.0f), glm::vec3(2.0,0.0,0.0));
	glm::vec3 sphereColour(1.f, 0.1f, 0.2f);

	glm::mat4 capsuleModel = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0, 0.0, 0.0));
	glm::vec3 capsuleColour(0.2f, 0.1f, 1.0f);


	while (application->isRunning())
	{
		elapsedTime += application->resetTimer();
		if (elapsedTime > 1.0 / 60.f)
		{
			std::cout << "Time elapsed: " << elapsedTime << std::endl;

			if (SC::InputPoller::isKeyPressed(SC_KEY_SPACE))
			{
				std::cout << "Space is pressed" << std::endl;
			}

			if (SC::InputPoller::isMouseButtonPressed(SC_MOUSE_BUTTON_2))
			{
				std::cout << "Mouse button 2 is pressed" << std::endl;
			}

			if (SC::InputPoller::isKeyPressed(SC_KEY_W))
			{
				SC::Renderer::cameraForward();
			}

			if (SC::InputPoller::isKeyPressed(SC_KEY_S))
			{
				SC::Renderer::cameraBack();
			}

			if (SC::InputPoller::isKeyPressed(SC_KEY_A))
			{
				SC::Renderer::cameraLeft();
			}

			if (SC::InputPoller::isKeyPressed(SC_KEY_D))
			{
				SC::Renderer::cameraRight();
			}

			if (SC::InputPoller::isKeyPressed(SC_KEY_UP))
			{
				SC::Renderer::cameraUp();
			}

			if (SC::InputPoller::isKeyPressed(SC_KEY_DOWN))
			{
				SC::Renderer::cameraDown();
			}

			SC::Renderer::beginScene();

			//cubeModel = glm::rotate(cubeModel, elapsedTime * glm::radians(25.f), glm::vec3(0.1, 1, 0.2));

			//sphereModel = glm::rotate(sphereModel, elapsedTime * glm::radians(45.f), glm::vec3(0.1, 0.9, 0.2));

			capsuleModel = glm::rotate(capsuleModel, elapsedTime * glm::radians(45.f), glm::vec3(0.5, 1, 0.8));
			
			SC::Renderer::drawCube(cubeModel, glm::vec3(1.0f, 1.0f, 1.0f), cubeColour);

			SC::Renderer::drawSphere(sphereModel, 1.0f, sphereColour);

			SC::Renderer::drawCapsule(capsuleModel, 0.5f, 0.5f, capsuleColour);

			SC::Renderer::endScene();

			application->updateWindow(elapsedTime);
			elapsedTime = 0.f;
		}
	}
	
	// Stop the renderer
	SC::Renderer::shutdown();

	return 0;
}