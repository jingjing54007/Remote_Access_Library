#include "stdafx.h"
#include "IO_Runner.h"
#include <boost/asio.hpp>

namespace SL {
	namespace Remote_Access_Library {
		namespace Network {
			class IO_RunnerImpl {
			public:
				boost::asio::io_service io_service;
				IO_RunnerImpl() :work(io_service) { //MUST BE 1, otherwise calls can be interleaved when sendiing and receiving
					io_servicethread = std::thread([this]() {
						std::cout << "Starting io_service Factory" << std::endl;
						io_service.run();
						std::cout << "stopping io_service Factory" << std::endl;
					});
				}
				~IO_RunnerImpl()
				{
					io_service.stop();
					io_servicethread.join();
				}

				std::thread io_servicethread;
				boost::asio::io_service::work work;
			};
		}
	}
}


SL::Remote_Access_Library::Network::IO_Runner::IO_Runner() {
	Start();
}


SL::Remote_Access_Library::Network::IO_Runner::~IO_Runner()
{
	Stop();
}

void SL::Remote_Access_Library::Network::IO_Runner::Start()
{
	Stop();
	_IO_RunnerImpl = new IO_RunnerImpl();
}

void SL::Remote_Access_Library::Network::IO_Runner::Stop()
{
	delete _IO_RunnerImpl;
	_IO_RunnerImpl = nullptr;
}

boost::asio::io_service& SL::Remote_Access_Library::Network::IO_Runner::get_io_service()
{
	return _IO_RunnerImpl->io_service;
}

