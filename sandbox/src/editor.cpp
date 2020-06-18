#include "editor.h"
#include "ImGuiHelper.h"
#include <map>

void Editor::init()
{
	// Start the singleton application
	m_application.reset(SC::Application::getInstance());

	SC::WindowProperties props;
	props.m_width = 1200;
	props.m_height = 800;
	props.m_title = "IMAT3905 Resit";
	m_application->init(props);

	// Set the event callback to this class
	auto window = SC::Application::getInstance()->getWindow();
	window->setEventCallback(std::bind(&Editor::onEvent, this, std::placeholders::_1));

	// Start the renderer
	SC::Renderer::init();

	// Setup ImGui
	ImGuiHelper::init();

	// Set up Game Objects

	// Floor
	m_gameObjects.push_back(std::make_shared<GameObject>(GameObject("Floor")));
	m_gameObjects.back()->addComponent(std::make_shared<ProxyMeshComponent>(ProxyMeshComponent(MeshType::Cuboid)));
	m_gameObjects.back()->addComponent(std::make_shared<TransformComponent>(TransformComponent({ 0,-0.05,0 }, { 0,0,0 }, { 10,0.1,10.0 })));
	m_gameObjects.back()->addComponent(std::make_shared<ColourComponent>(ColourComponent({ 0.0f ,1.f,0.f })));


	// Sphere
	m_gameObjects.push_back(std::make_shared<GameObject>(GameObject("Sphere")));
	m_gameObjects.back()->addComponent(std::make_shared<ProxyMeshComponent>(ProxyMeshComponent(MeshType::Sphere)));
	m_gameObjects.back()->addComponent(std::make_shared<TransformComponent>(TransformComponent({ -4.5,0.5,-4.5 }, { 0,0,0 }, { 1.f,1.f,1.f })));
	m_gameObjects.back()->addComponent(std::make_shared<ColourComponent>(ColourComponent({ 1.f,0.f,0.f })));
	m_gameObjects.back()->addComponent(std::make_shared<AIControllerComponent>(AIControllerComponent()));

	// Cube
	m_gameObjects.push_back(std::make_shared<GameObject>(GameObject("Cube")));
	m_gameObjects.back()->addComponent(std::make_shared<ProxyMeshComponent>(ProxyMeshComponent(MeshType::Cuboid)));
	m_gameObjects.back()->addComponent(std::make_shared<TransformComponent>(TransformComponent({ 0,0.5,0 }, { 0,0,0 }, { 1.f,1.f,1.f })));
	m_gameObjects.back()->addComponent(std::make_shared<ColourComponent>(ColourComponent({ 0.f,0.f,1.f })));
	m_gameObjects.back()->addComponent(std::make_shared<KeyboardComponent>(KeyboardComponent()));

}

void Editor::run()
{
	float elapsedTime = 0.f;

	while (m_application->isRunning())
	{
		elapsedTime += m_application->resetTimer();
		if (elapsedTime > 1.0 / 60.f)
		{
			//ImGuiHelper::writeToConsole("Frame time (ms): " + std::to_string(elapsedTime));

			// Update Draw all game objects

			SC::Renderer::beginScene();
			
			for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
			{
				(*it)->onUpdate(elapsedTime);

				auto meshTypeIt = (*it)->getComponent<ProxyMeshComponent>();
				auto modelIt = (*it)->getComponent<TransformComponent>();
				auto colourIt = (*it)->getComponent<ColourComponent>();

				const MeshType& meshType = static_cast<ProxyMeshComponent*>(meshTypeIt->get())->getMeshType();
				const glm::mat4& model = static_cast<TransformComponent*>(modelIt->get())->getTransform();
				const glm::vec3& colour = static_cast<ColourComponent*>(colourIt->get())->getColour();

				switch (meshType)
				{
				case MeshType::Capsule:
					SC::Renderer::drawCapsule(model, 0.5f, 0.5f, colour);
					break;
				case MeshType::Cuboid:
					SC::Renderer::drawCube(model, { 1.f,1.f,1.f }, colour);
					break;
				case MeshType::Sphere:
					SC::Renderer::drawSphere(model, 1.0f, colour);
				}
			}
			SC::Renderer::endScene();

			ImGuiHelper::begin();

			// Renderewr output window
			ImGui::Begin("Renderer output");
			uint32_t textureID = SC::Renderer::getFramebufferTextureID();
			ImGui::Image((void*)textureID, ImVec2{ 800, 600 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			ImGui::End();

			// Game object settings window

			ImGui::Begin("Properties");


			// Game object list box
			// Get char * for game object names
			std::vector<char *> gameObjectsNames(m_gameObjects.size());
			int i = 0;
			for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
			{
				const std::string& name = (*it)->name();
				int len = strlen(name.c_str()) + 1;
				gameObjectsNames[i] = (char*)malloc(len);
				strcpy_s(gameObjectsNames[i], len, name.c_str());
				i++;
			}

			ImGui::TextWrapped("Game Objects:");
			static int gameObjectIndex = 0;
			ImGui::SetNextItemWidth(-1);
			ImGui::ListBox("##GameObjects", &gameObjectIndex, gameObjectsNames.data(), gameObjectsNames.size(), gameObjectsNames.size());
			// Clean up char * for list box
			for (auto it = gameObjectsNames.begin(); it != gameObjectsNames.end(); ++it) free(*it);

			// Component list box
			// Get char * for component types/names
			auto entity = m_gameObjects.at(gameObjectIndex);
			std::vector<char *> componentTypes(entity->componentCount());
			i = 0;
			for (auto it = entity->begin(); it != entity->end(); ++it)
			{
				const std::string& type = (*it)->getType().name();
				int len = strlen(type.c_str()) - 5; // Removing "class "
				componentTypes[i] = (char*)malloc(len);
				strncpy_s(componentTypes[i], len, type.c_str()+6, len - 1);
				componentTypes[i][len - 1] = '\0';
				i++;
			}

			ImGui::TextWrapped("Components:");
			static int componentIndex = 0;
			ImGui::SetNextItemWidth(-1);
			ImGui::ListBox("##Components", &componentIndex, componentTypes.data(), componentTypes.size(), componentTypes.size());
			// Clean up char * for component list box
			for (auto it = componentTypes.begin(); it != componentTypes.end(); ++it) free(*it);

			// Component properties
			ImGui::TextWrapped("Properties:");
			ImGui::NewLine();
			// Get the selected component
			auto it = m_gameObjects.at(gameObjectIndex)->begin() + componentIndex;
			// Get the select components type as a const char *
			const char * type = (*(m_gameObjects.at(gameObjectIndex)->begin() + componentIndex))->getType().name();

			// ProxyMesh
			if (type == typeid(ProxyMeshComponent).name())
			{
				MeshType& meshType = static_cast<ProxyMeshComponent*>(it->get())->getMeshType();
				if (meshType == MeshType::Sphere)
				{
					int i = 0;
				}
				MeshType meshTypes[3] = {MeshType::Cuboid,MeshType::Sphere, MeshType::Capsule };
				std::map<MeshType, int> meshIndices = { {MeshType::Cuboid,0},{MeshType::Sphere,1},{MeshType::Capsule,2} };

				static int meshIndex;
				// Set meshInt top current mesh type
				meshIndex = meshIndices.at(meshType);

				ImGui::TextWrapped("Mesh Type:");
				ImGui::RadioButton("Cuboid", &meshIndex, 0); 
				ImGui::RadioButton("Sphere", &meshIndex, 1); 
				ImGui::RadioButton("Capsule", &meshIndex, 2);

				// Update mesh type from meshInt
				meshType = meshTypes[meshIndex];
			}

			// Colour
			if (type == typeid(ColourComponent).name())
			{
				glm::vec3& colourGLM = static_cast<ColourComponent*>(it->get())->getColour();
				static float colourFloat[3];
				// Set col float from component
				colourFloat[0] = colourGLM.r;
				colourFloat[1] = colourGLM.g;
				colourFloat[2] = colourGLM.b;

				ImGui::TextWrapped("Render Colour:");
				ImGui::ColorEdit3("Colour", colourFloat);

				// Set component from col float
				colourGLM = { colourFloat[0],colourFloat[1],colourFloat[2] };
			}

			// Transform
			if (type == typeid(TransformComponent).name())
			{
				auto transformComp = static_cast<TransformComponent*>(it->get());

				// Position
				glm::vec3& position = transformComp->getPosition();
				static float pos[3];
				// Set pos from component
				pos[0] = position.r;
				pos[1] = position.g;
				pos[2] = position.b;

				ImGui::TextWrapped("Transform");
				ImGui::Text("X           Y           Z");
				ImGui::InputFloat3("Position", pos, 2);
				// Set component from pos
				position = { pos[0],pos[1],pos[2] };

				// Rotation
				glm::vec3& rotation = transformComp->getRotation();
				static float rot[3];
				// Set pos from component
				rot[0] = glm::degrees(rotation.x);
				rot[1] = glm::degrees(rotation.y);
				rot[2] = glm::degrees(rotation.z);

				ImGui::InputFloat3("Rotation", rot, 2);
				// Set component from rot
				rotation = { glm::radians(rot[0]),glm::radians(rot[1]),glm::radians(rot[2]) };

				// Scale
				glm::vec3& scale = transformComp->getScale();
				static float scl[3];
				// Set pos from component
				scl[0] = scale.x;
				scl[1] = scale.y;
				scl[2] = scale.z;

				ImGui::InputFloat3("Scale", scl, 2);
				// Set component from scl
				scale = { scl[0],scl[1],scl[2] };

				// Recalc model matrix
				transformComp->calculateTransform();
			}

			// Keyboard
			if (type == typeid(KeyboardComponent).name()) ImGui::TextWrapped("No properties to edit.");
			
			// AIController
			if (type == typeid(AIControllerComponent).name())
			{
				ImGui::TextWrapped("Add editor widgets for AI locations");
			}

			ImGui::End();

			// Console output window -- use ImGuiHelper::writeToConsole to write to this console
			ImGui::Begin("Console");
			auto consoleText = ImGuiHelper::getConsoleString();
			ImGui::Text(consoleText);
			free(consoleText);
			ImGui::SetScrollHere(1.0f);
			ImGui::End();

			//ImGui::ShowDemoWindow();

			ImGuiHelper::end();

			m_application->updateWindow(elapsedTime);
			elapsedTime = 0.f;
		}
	}
}

void Editor::shutdown()
{

	// Stop IMGui
	ImGuiHelper::shutdown();

	// Stop the renderer
	SC::Renderer::shutdown();
}

void Editor::onEvent(SC::Event & e)
{
	SC::EventDispatcher dispatcher(e);
	dispatcher.dispatch<SC::WindowCloseEvent>(std::bind(&Editor::onClose, this, std::placeholders::_1));
	dispatcher.dispatch<SC::KeyPressedEvent>(std::bind(&Editor::onKeyPress, this, std::placeholders::_1));

	if (!e.handled())
	{
		for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			(*it)->onEvent(e);
		}
	}
}

bool Editor::onKeyPress(SC::KeyPressedEvent & e)
{
	switch (e.GetKeyCode())
	{
	case SC_KEY_W:
		SC::Renderer::cameraForward(); return true;
		break;
	case SC_KEY_S:
		SC::Renderer::cameraBack(); return true;
		break;
	case SC_KEY_A:
		SC::Renderer::cameraLeft(); return true;
	break;
	case SC_KEY_D:
		SC::Renderer::cameraRight(); return true;
		break;
	case SC_KEY_Q:
		SC::Renderer::cameraUp(); return true;
		break;
	case SC_KEY_E:
		SC::Renderer::cameraDown(); return true;
		break;
	}
	return false;
}
