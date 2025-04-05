#include "AsyncImageClient.h"
#include<fstream>
#include"../src/WindowManager.h"
#include"../UI/ErrorWindow.h"




void AsyncImageClient::Start(const std::string& host, int port)
{
    auto self = shared_from_this();
    resolver_.async_resolve(host, std::to_string(port),
        [this, self](boost::system::error_code ec, boost::asio::ip::tcp::resolver::results_type endpoints) {
            if (!ec) {
                boost::asio::async_connect(socket_, endpoints,
                    boost::asio::bind_executor(strand_,
                        [this, self](boost::system::error_code ec, boost::asio::ip::tcp::endpoint) {
                            if (!ec) {
                                std::cout << "Connect succesfull:" << std::endl;
                                receive_image_count();
                            }
                            else {
                                std::cerr << "Ошибка подключения: " << ec.message() << "\n";
                            }
                        }));
            }
            else {
                std::cerr << "Ошибка резолвинга: " << ec.message() << "\n";
            }
        });

}

void AsyncImageClient::SendStoreInfo(const std::string& store_name, const std::vector<std::string>& image_files, unsigned int user_id)
{
    store_name_ = store_name;
    image_files_ = image_files;
    userID = user_id;
    image_index_ = 0;
    auto self = shared_from_this();
    uint8_t cmd = 1;

    // Сначала отправляем команду
    boost::asio::async_write(socket_, boost::asio::buffer(&cmd, sizeof(cmd)),
        boost::asio::bind_executor(strand_,
            [this, self](boost::system::error_code ec, std::size_t) {
                if (!ec) {
                    std::cout << "Команда 1 (создание магазина) отправлена\n";
                    // Потом — отправка данных магазина
                    send_store_name();
                }
                else {
                    std::cerr << "Ошибка при отправке команды: " << ec.message() << "\n";
                }
            }));


}

void AsyncImageClient::SendImages()
{
    std::cout << "SendImages:" << std::endl;
    auto self = shared_from_this();
    boost::asio::post(strand_, [this, self]() {
        send_next_image();
        });

}



void AsyncImageClient::send_store_name()
{
    uint32_t name_length = htonl(store_name_.size());
    uint32_t store_id = htonl(userID);

    buffer_.resize(sizeof(store_id) + sizeof(name_length) + store_name_.size());
    std::memcpy(buffer_.data(), &store_id, sizeof(store_id));
    std::memcpy(buffer_.data() + sizeof(store_id), &name_length, sizeof(name_length));
    std::memcpy(buffer_.data() + sizeof(store_id) + sizeof(name_length), store_name_.data(), store_name_.size());

    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(buffer_),
        boost::asio::bind_executor(strand_,
            [this, self](boost::system::error_code ec, std::size_t) {
                if (!ec) {
                    std::cout << "Отправлено название магазина: " << store_name_ << "\n";
                    SendImages();
                    //send_next_image();
                }
                else {
                    std::cerr << "Ошибка отправки названия магазина: " << ec.message() << "\n";
                }
            }));
   
}
/*
void AsyncImageClient::read_server_message_length()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer(&store_server_length_, sizeof(store_server_length_)),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec && length == sizeof(store_server_length_)) {
                store_server_length_ = ntohl(store_server_length_);
                // std::cout << "Получена длина ответа от сервера: " << store_server_length_ << "\n";
                read_server_message();
            }
            else {
                std::cerr << "Ошибка при чтении длины ответа: " << ec.message() << "\n";
            }
        });
}
*/
void AsyncImageClient::read_server_message()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer(buffer_, 10),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::string message(buffer_.begin(), buffer_.begin() + length);
                std::cout << "Ответ сервера: " << message << "\n";
            }
            else {
                std::cerr << "Ошибка чтения ответа сервера: " << ec.message() << "\n";
            }
        });

}
/*
void AsyncImageClient::read_server_message()
{
    auto self(shared_from_this());
    store_name_.resize(store_server_length_);

    boost::asio::async_read(socket_, boost::asio::buffer(store_name_),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec && length == store_server_length_) {
                std::cout << "Ответ от сервера: " << store_name_ << "\n";
                if (strcmp(store_name_.c_str(), "Successfull") == 0) {

                    std::cout << store_name_ << std::endl;
                    std::string data = store_name_;
                    WindowManager::Instance().CloseWindow("CreateShop");
                    WindowManager::Instance().CloseWindow("ShopMenu");
                    ErrorWindow::Instance().ErrorMessage = data;
                    WindowManager::Instance().OpenWindow("authServer");

                }
            }
            else {
                std::cerr << "Ошибка при чтении данных: " << ec.message() << "\n";
            }
        });

}
*/


void AsyncImageClient::send_next_image()
{
    if (image_index_ >= image_files_.size()) {
        std::cout << "Все изображения отправлены.\n";

        uint32_t zero = htonl(0);
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(&zero, sizeof(zero)),
            boost::asio::bind_executor(strand_,
                [this, self](boost::system::error_code ec, std::size_t) {
                    if (!ec) {
                        read_server_message();
                    }
                    else {
                        std::cerr << "Ошибка отправки маркера завершения: " << ec.message() << "\n";
                    }
                }));
        return;
    }

    std::ifstream file(image_files_[image_index_], std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Ошибка: не удалось открыть файл " << image_files_[image_index_] << "\n";
        image_index_++;
        send_next_image();
        return;
    }

    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    buffer_.resize(sizeof(uint32_t) + file_size);

    uint32_t net_size = htonl(static_cast<uint32_t>(file_size));
    std::memcpy(buffer_.data(), &net_size, sizeof(net_size));
    file.read(buffer_.data() + sizeof(net_size), file_size);

    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(buffer_),
        boost::asio::bind_executor(strand_,
            [this, self](boost::system::error_code ec, std::size_t) {
                if (!ec) {
                    std::cout << "Отправлено изображение: " << image_files_[image_index_] << "\n";
                    image_index_++;
                    send_next_image();
                }
                else {
                    std::cerr << "Ошибка отправки изображения: " << ec.message() << "\n";
                }
            }));
}


void AsyncImageClient::receive_image_count()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer(&image_count_, sizeof(image_count_)),
        boost::asio::bind_executor(strand_,
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec && length == sizeof(image_count_)) {
                    image_count_ = ntohl(image_count_);
                    std::cout << "Сервер отправит " << image_count_ << " изображений\n";
                    if (image_count_ > 0) {
                        receive_next_image();
                    }
                    else {

                        // send_store_name();
                    }
                }
                else {
                    std::cerr << "Ошибка чтения количества изображений: " << ec.message() << "\n";
                }
            }));

}

void AsyncImageClient::receive_next_image()
{
    if (image_count_ == 0) {
        // send_store_name();
        return;
    }

    auto self(shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer(&image_size_, sizeof(image_size_)),
        boost::asio::bind_executor(strand_,
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec && length == sizeof(image_size_)) {
                    image_size_ = ntohl(image_size_);
                    buffer_.resize(image_size_);
                    receive_image_data();
                }
                else {
                    std::cerr << "Ошибка получения размера изображения: " << ec.message() << "\n";
                }
            }));
}

void AsyncImageClient::receive_image_data()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer(buffer_),
        boost::asio::bind_executor(strand_,
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec && length == buffer_.size()) {
                    //save_image();
                    std::vector< unsigned char > image_data(buffer_.begin(), buffer_.end());
                    TextureManager& txManager = TextureManager::Instance();
                    imageMemoryShop = txManager.LoadTextureFromMemory(image_data);


                    imageMemoryList.push_back(imageMemoryShop);



                    std::cout << "Изображение загружено в память, размер: " << image_data.size() << " байт\n";

                    image_count_--;
                    receive_next_image();
                }
                else {
                    std::cerr << "Ошибка при получении изображения: " << ec.message() << "\n";
                }
            }));

}





