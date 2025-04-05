#include "App.h"
#include"../resources/Font.h"
#include"../resources/Icons/InitIcon.h"
#include"../resources/Icons/IconMemory.h"
#include"../src/ErrorManager.h"
#include"TextureManager.h"
#include"../src/WindowManager.h"
#include"../UI/ErrorWindow.h"
#include"../UI/CreateShop.h"
#include"../UI/ShopManager.h"
#include"../UI/AsyncImageClient.h"

enum class AppState
{
	Connecting,
	Running,
	Error

};

App::App() : window(nullptr), gl_context(nullptr), running(true), moving(false), mouseOffsetX(0), mouseOffsetY(0), clear_color(ImVec4(0.45f, 0.55f, 0.60f, 1.00f)) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("Error: SDL_Init(): %s\n", SDL_GetError());
		running = false;
		return;
	}

	const char* glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS;
	window = SDL_CreateWindow("BH", 400, 450, window_flags);
	if (!window) {
		printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
		running = false;
		return;
	}

	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	gl_context = SDL_GL_CreateContext(window);
	if (!gl_context) {
		printf("Error: SDL_GL_CreateContext(): %s\n", SDL_GetError());
		running = false;
		return;
	}

	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1);
	SDL_ShowWindow(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	
	ImGui::MyColor();


	float size_pixels2 = 30.0f;
	ImFontConfig config2;
	config2.GlyphRanges = ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
	config2.FontDataOwnedByAtlas = true; // ImGui управляет ресурсами памяти шрифта
	font2 = ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)my_font_data2, my_font_size2, size_pixels2, &config2);



	float size_pixels3 = 27.0f;
	ImFontConfig config3;
	config3.MergeMode = true;
	//config.GlyphMinAdvanceX = 13.0f;
	config3.FontDataOwnedByAtlas = true; // ImGui управляет ресурсами памяти шрифта
	static const ImWchar icon_ranges[] = { ICON_MIN, ICON_MAX, 0 };
	ImFont* font3 = ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)MemoryIcon, IconMem, size_pixels3, &config3, icon_ranges);



	ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);
}


App::~App() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DestroyContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



bool App::ConnectToServer(std::string& errorMessage)
{
	try
	{
		boost::asio::ssl::context ctx(boost::asio::ssl::context::tlsv13);
		boost::system::error_code error;

		ctx.load_verify_file("C:\\Users\\Rocket\\cert\\selfsigned.crt", error);
		if (error) {
			throw std::runtime_error("Failed to load certificate: " + error.message());
			return false;
		}

		boost::asio::ip::tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve("127.0.0.1", "7171");
		connect(socket_ssl.lowest_layer(), endpoints, error);
		if (error) {
			errorMessage = "Failed to connect to server: " + error.message();
			return false;
		}

		socket_ssl.handshake(boost::asio::ssl::stream_base::client, error);
		if (error) {
			errorMessage = "Handshake failed: " + error.message();
			return false;
		}

		return true;
	}
	catch (const std::exception& e)
	{
		errorMessage = e.what();
		return false;
	}
}





void App::Run() {
	AppState state = AppState::Connecting;
	std::string errorMessage;

	if (ConnectToServer(errorMessage)) {
		state = AppState::Running;
	}
	else {
		state = AppState::Error;
	}

	auto client = std::make_shared<AsyncImageClient>(io_context);
	client->Start("127.0.0.1", 7272);

	io_context.run();


	WindowManager& manager = WindowManager::Instance();

	auto signInWindow = std::make_shared<SignIN>(nullptr);
	auto signUpWindow = std::make_shared<SignUP>(signInWindow.get());
	signInWindow->getSignUpWindow(signUpWindow.get());
	auto WindowError = std::make_shared<ErrorWindow>();
	WindowError->IsOpen = false;

	auto Create = std::make_shared<CreateShop>();
	Create->IsOpen = false;
	manager.AddWindow("CreateShop", Create);
	
	auto StoreManagmentShop = std::make_shared<ShopManager>();
	StoreManagmentShop->IsOpen = false;
	manager.AddWindow("ShopManager", StoreManagmentShop);

	manager.AddWindow("authServer", WindowError);

	manager.AddWindow("SignIN", signInWindow);

	manager.AddWindow("SignUP", signUpWindow);

	auto shopMenu = std::make_shared<Shop>(manager);
	shopMenu->IsOpen = false;
	manager.AddWindow("ShopMenu", shopMenu);

	auto userInfo = std::make_shared<UserInfo>();
	userInfo->IsOpen = false;
	manager.AddWindow("UserInfo", userInfo);

	TextureManager::Instance().SetShopImage(TextureManager::Instance().LoadTexture("C:/Users/Rocket/src/BH_Logo.png"));

	bool windowSizeChanged = false; // Флаг для отслеживания изменения размера

	while (running) {
		Uint32 startTime = SDL_GetTicks();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
			

			HandleWindowMovement(window, &event);
		}

		// Проверка условия для изменения размера окна
		

		

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		

		WindowManager::Instance().AdjustWindowSize(window);
		if (state == AppState::Running) {
			manager.RenderAll();
		
		}
		else if (state == AppState::Error) {
			ErrorManager errorServer;
			SDL_SetWindowSize(window, 400, 150);
			errorServer.ErrorConnectServer(errorMessage);
		}

		ImGui::Render();
		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SetSwapInterval(-1);
		SDL_GL_SwapWindow(window);
		//SDL_Delay(10);
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 8) {
			SDL_Delay(8 - frameTime); // Точное ограничение до ~80 FPS
		}
	}

	socket_ssl.lowest_layer().close();
}



void App::HandleWindowMovement(SDL_Window* window, SDL_Event* event) {
	if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN && event->button.button == SDL_BUTTON_LEFT) {
		moving = true;
		int winX, winY;
		SDL_GetWindowPosition(window, &winX, &winY);
		float mouseX, mouseY;
		SDL_GetGlobalMouseState(&mouseX, &mouseY);
		mouseOffsetX = mouseX - winX;
		mouseOffsetY = mouseY - winY;
	}

	if (event->type == SDL_EVENT_MOUSE_BUTTON_UP && event->button.button == SDL_BUTTON_LEFT) {
		moving = false;
	}

	if (moving && event->type == SDL_EVENT_MOUSE_MOTION) {
		float mouseX, mouseY;
		SDL_GetGlobalMouseState(&mouseX, &mouseY);
		SDL_SetWindowPosition(window, mouseX - mouseOffsetX, mouseY - mouseOffsetY);
	}
}