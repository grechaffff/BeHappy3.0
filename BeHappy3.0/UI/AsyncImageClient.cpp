#include "AsyncImageClient.h"
#include<fstream>
#include"../src/WindowManager.h"
#include"../UI/ErrorWindow.h"

AsyncImageClient::AsyncImageClient(boost::asio::io_context& io_context, const std::string& host, int port,  unsigned int id ,
    const std::string& store_name, const std::vector<std::string>& image_files)
    : socket_(io_context), resolver_(io_context), strand_(boost::asio::make_strand(io_context)),
    store_name_(store_name), image_files_(image_files), image_index_(0) , userID(id) {
}

void AsyncImageClient::Start(const std::string& host, int port , unsigned int userID)
{
    auto self = shared_from_this(); // ������ ���������, ��� ��� ������ ��� � shared_ptr
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver_.resolve(host, std::to_string(port));

    boost::asio::async_connect(socket_, endpoints,
        boost::asio::bind_executor(strand_,
            [self , userID](boost::system::error_code ec, boost::asio::ip::tcp::endpoint) {
                if (!ec) {
                    self->send_store_name(userID);
                }
                else {
                    std::cerr << "������ �����������: " << ec.message() << "\n";
                }
            }));

}



void AsyncImageClient::send_store_name(unsigned int userID)
{
    uint32_t name_length = htonl(store_name_.size());  // ����� ����� �������� (4 �����)
    uint32_t store_id = htonl(userID);  // ������������ id � ������� ������� (4 �����)

    // ����� �����: 4 ����� (id) + 4 ����� (����� �����) + ���� ���
    buffer_.resize(sizeof(store_id) + sizeof(name_length) + store_name_.size());

    // �������� ID �������� � �����
    std::memcpy(buffer_.data(), &store_id, sizeof(store_id));

    // �������� ����� �����
    std::memcpy(buffer_.data() + sizeof(store_id), &name_length, sizeof(name_length));

    // �������� ���� ��� ��������
    std::memcpy(buffer_.data() + sizeof(store_id) + sizeof(name_length), store_name_.data(), store_name_.size());

    // ���������� ������
    boost::asio::async_write(socket_, boost::asio::buffer(buffer_),
        boost::asio::bind_executor(strand_,
            [self = shared_from_this()](boost::system::error_code ec, std::size_t) {
                if (!ec) {
                    std::cout << "���������� �������� ��������: " << self->store_name_
                        << " (ID: " << self->userID << ")\n";
                    self->send_next_image();
                }
                else {
                    std::cerr << "������ �������� �������� ��������: " << ec.message() << "\n";
                }
            }));
   
}

void AsyncImageClient::read_server_message_length()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer(&store_server_length_, sizeof(store_server_length_)),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec && length == sizeof(store_server_length_)) {
                store_server_length_ = ntohl(store_server_length_);
                // std::cout << "�������� ����� ������ �� �������: " << store_server_length_ << "\n";
                read_server_message();
            }
            else {
                std::cerr << "������ ��� ������ ����� ������: " << ec.message() << "\n";
            }
        });
}

void AsyncImageClient::read_server_message()
{
    auto self(shared_from_this());
    store_name_.resize(store_server_length_);

    boost::asio::async_read(socket_, boost::asio::buffer(store_name_),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec && length == store_server_length_) {
                std::cout << "����� �� �������: " << store_name_ << "\n";
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
                std::cerr << "������ ��� ������ ������: " << ec.message() << "\n";
            }
        });

}

void AsyncImageClient::send_next_image()
{
    if (image_index_ >= image_files_.size()) {
        std::cout << "��� ����������� ����������.\n";

        uint32_t zero = htonl(0);
        boost::asio::async_write(socket_, boost::asio::buffer(&zero, sizeof(zero)),
            boost::asio::bind_executor(strand_,
                [self = shared_from_this()](boost::system::error_code ec, std::size_t) {
                    if (!ec) {
                        //std::cout << "������ ���������� ���������.\n";
                        self->read_server_message_length();
                    }
                    else {
                        std::cerr << "������ �������� ������� ����������: " << ec.message() << "\n";
                    }
                }));
        return;
    }


    std::ifstream file(image_files_[image_index_], std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "������: �� ������� ������� ���� " << image_files_[image_index_] << "\n";
        image_index_++;
        send_next_image();  // ���������� ���� � ��������� � ����������
        return;
    }

    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    buffer_.resize(sizeof(uint32_t) + file_size);

    uint32_t net_size = htonl(static_cast<uint32_t>(file_size));
    std::memcpy(buffer_.data(), &net_size, sizeof(net_size));
    file.read(buffer_.data() + sizeof(net_size), file_size);

    boost::asio::async_write(socket_, boost::asio::buffer(buffer_),
        boost::asio::bind_executor(strand_,
            [self = shared_from_this()](boost::system::error_code ec, std::size_t) {
                if (!ec) {
                    std::cout << "���������� �����������: " << self->image_files_[self->image_index_] << "\n";
                    self->image_index_++;
                    self->send_next_image();
                }
                else {
                    std::cerr << "������ �������� �����������: " << ec.message() << "\n";
                }
            }));

}



