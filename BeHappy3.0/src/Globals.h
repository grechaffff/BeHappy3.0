#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <string>
#include <SDL3/SDL_opengles2.h>
#include<thread>
#include<chrono>
#include"../resources/Icons/InitIcon.h"

#include<iostream>

#include<boost/asio.hpp>
#include<boost/array.hpp>
#include<boost/bind/bind.hpp>
#include<boost/asio/ssl.hpp>
#include "TextureManager.h"



// Удаляем #include "WindowManager.h", чтобы избежать зацикливания
// Удаляем #include "SignUP.h", чтобы избежать зацикливания




extern ImFont* font2;
extern ImFont* font3;
extern SDL_Window* window;
// Константы
constexpr int WIDTH = 400;
constexpr int HEIGHT = 450;

constexpr int WIDTH_Shop = 800;
constexpr int HEIGHT_Shop = 600;

extern boost::asio::io_context io_context;
extern boost::asio::ssl::stream<boost::asio::ip::tcp::socket > socket_ssl;



#endif // GLOBALS_H
