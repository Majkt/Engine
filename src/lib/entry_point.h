#pragma once

#ifndef MAJKT_ENGINE_PLATFORM
#define MAJKT_ENGINE_PLATFORM

#include <glog/logging.h>
#include "glog/stl_logging.h"

#include <iostream>

// Application will be defined by client.
extern Majkt::Application* Majkt::CreateApplication();

int main(int argc, char** argv)
{
	google::InitGoogleLogging(argv[0]);
	// Log both to log file and stderr
  	FLAGS_alsologtostderr = true;

	LOG(INFO) << "Majkt Engine Started";
	auto app = Majkt::CreateApplication();
	app->Run();
	delete app;
	LOG(INFO) << "Majkt Engine Ended";
}

#endif // MAJKT_ENGINE_PLATFORM
