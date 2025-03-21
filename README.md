# BeHappy3.0

## Описание
Клиентская часть маркетплейса реализована на языке C++ с использованием **ImGui** для графического интерфейса, **SDL3** для создания окон и управления событиями, **OpenGL** для рендеринга графики и **Boost** для работы с асинхронными сетевыми операциями и многозадачностью. Клиент взаимодействует с сервером для отображения информации о товарах, заказах и управления пользователями.

## Стек технологий
- **C++**: Основной язык программирования.
- **ImGui**: Лёгкая библиотека для создания графических интерфейсов.
- **SDL3**: Библиотека для работы с окнами, обработкой событий и рендерингом через OpenGL.
- **OpenGL**: Для рендеринга 2D и 3D графики в клиентском приложении.
- **Boost**: Для работы с многозадачностью и асинхронными сетевыми операциями.
- **CMake**: Для сборки проекта.

## Требования 
Для корректной работы клиентского приложения, необходимо также клонировать серверную часть. Серверная часть написана на C++ и использует библиотеки Boost Asio и OpenSSL для обработки запросов и обеспечения безопасности.
