#pragma once
#include"../src/Globals.h"

class AsyncImageClient : public std::enable_shared_from_this<AsyncImageClient>
{

public:

    AsyncImageClient(boost::asio::io_context& io_context)
        : socket_(io_context), resolver_(io_context), strand_(boost::asio::make_strand(io_context)),
        image_index_(0) {
    }

    void Start(const std::string& host, int port);

    
    void SendStoreInfo(const std::string& store_name, const std::vector<std::string>& image_files, unsigned int user_id);

    void SendImages();

    std::string get_Name_store() {

        return store_name_;
    }

private:
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::strand<boost::asio::any_io_executor> strand_;

    std::string store_name_;
    std::vector<std::string> image_files_;
    std::vector<char> buffer_;
    size_t image_index_;
    unsigned int userID;

    uint32_t image_count_;
    uint32_t image_size_;

    void send_store_name();

    void read_server_message_length();

    void read_server_message();

    void send_next_image();

    void receive_image_count();

    void receive_next_image();


    void receive_image_data();
};