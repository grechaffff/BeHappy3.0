#include"Globals.h"


boost::asio::ssl::context ctx(boost::asio::ssl::context::tlsv13);

ImFont* font2 = nullptr;
ImFont* font3 = nullptr;

SDL_Window* window = nullptr;
SDL_GLContext gl_context;
ImVec4 clear_color;
bool running;
bool moving;

boost::asio::io_context io_context;
boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_ssl(io_context , ctx);

GLuint imageMemoryShop = 0;

//std::shared_ptr<AsyncImageClient> client = nullptr;

std::vector<GLuint > imageMemoryList;
constexpr float imageWidth = 70.0f;
constexpr float imageHeight = 70.0f;



int mouseOffsetX, mouseOffsetY;
