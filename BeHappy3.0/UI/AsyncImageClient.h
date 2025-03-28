#pragma once
#include"../src/Globals.h"

class AsyncImageClient : public std::enable_shared_from_this<AsyncImageClient>
{

public:

    AsyncImageClient(boost::asio::io_context& io_context, const std::string& host, int port,  unsigned int id ,
        const std::string& store_name, const std::vector<std::string>& image_files);


    void Start(const std::string& host, int port , unsigned int userID);

    static AsyncImageClient& instance();

    std::string get_Name_store() {

        return store_name_;
    }

private:
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::strand<boost::asio::any_io_executor> strand_;

    std::string store_name_;
    std::vector<std::string> image_files_;
    size_t image_index_;
    std::vector<char> buffer_;

    unsigned int userID;
    uint32_t store_server_length_;

    void send_store_name(unsigned int userID);

    void read_server_message_length();

    void read_server_message();

    void send_next_image();
};