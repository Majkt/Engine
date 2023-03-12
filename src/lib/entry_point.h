#pragma once

#ifndef MAJKT_ENGINE_PLATFORM
#define MAJKT_ENGINE_PLATFORM

#include <glog/logging.h>
#include "glog/stl_logging.h"

#include <iostream>

// Application will be defined by client.
extern majkt::Application* majkt::CreateApplication();

int main(int argc, char** argv)
{
	google::InitGoogleLogging(argv[0]);
	// Log both to log file and stderr
  	FLAGS_alsologtostderr = true;

	LOG(INFO) << "Majkt Engine Started";
	auto app = majkt::CreateApplication();
	app->Run();
	delete app;
	LOG(INFO) << "Majkt Engine Ended";
}

#endif // MAJKT_ENGINE_PLATFORM
