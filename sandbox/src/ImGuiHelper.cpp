#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <examples/imgui_impl_opengl3.cpp>
#include <examples/imgui_impl_glfw.cpp>

#include "ImGuiHelper.h"
#include "IMAT3905.h"

std::array<std::string, 50> ImGuiHelper::m_consoleLines = std::array<std::string, 50>();
unsigned int ImGuiHelper::m_consoleLinesLength = 50;
unsigned int ImGuiHelper::m_consolePosition = -1;

void ImGuiHelper::init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	GLFWwindow* win = SC::Application::getInstance()->getWindow()->getGLFWWindow();

	ImGui_ImplGlfw_InitForOpenGL(win, true);
	ImGui_ImplOpenGL3_Init("#version 430");

	for (int i = 0; i < m_consoleLinesLength; i++) m_consoleLines[i] = "";
}

void ImGuiHelper::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", NULL, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

	}
	else
	{
		("ImGui Dockspace has not been enabled in config.");
	}
}

void ImGuiHelper::end()
{
	ImGui::End();

	ImGuiIO& io = ImGui::GetIO();
	SC::Application* app = SC::Application::getInstance();
	io.DisplaySize = ImVec2((float)app->getWindow()->getWidth(), (float)app->getWindow()->getHeight());

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void ImGuiHelper::shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiHelper::writeToConsole(const std::string & text)
{
	++m_consolePosition;
	if (m_consolePosition >= m_consoleLinesLength)
	{
		m_consolePosition = 0;
	}
	m_consoleLines[m_consolePosition] = text + "\n";
}

char * ImGuiHelper::getConsoleString()
{
	char * main_ptr;
	char * reserve_ptr;
	unsigned int capacity = 2048;
	unsigned int allocated = 0;

	main_ptr = (char *)malloc(sizeof(char) * capacity);
	*main_ptr = '\0';

	int pos = m_consolePosition + 1;
	if (pos >= m_consoleLinesLength) pos = m_consoleLinesLength - pos;

	for (int i = 0; i < m_consoleLinesLength; i++)
	{
		int len = strlen(m_consoleLines[pos].c_str());
		if (!(allocated + len < capacity))
		{
			return main_ptr;
			// Reallocate
			//capacity += capacity;
			//reserve_ptr = (char *)realloc(main_ptr, sizeof(char) * capacity);
			//main_ptr = reserve_ptr;
		}

		strcat_s(main_ptr, sizeof(char) * capacity, m_consoleLines[pos].c_str());
		allocated += len;
		pos++;
		if (pos >= m_consoleLinesLength)
		{
			pos = 0;
		}
	}
	return main_ptr;
}
