#pragma once

#ifndef MAJKT_ENGINE_PLATFORM
#define MAJKT_ENGINE_PLATFORM

#include "src/lib/core/application.h"
#include "src/lib/debug/instrumentor.h"

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

	LOG(INFO) << "--------------- Majkt Engine Started ---------------";
	MAJKT_PROFILE_BEGIN_SESSION("Startup", get_current_dir() + "/src/sandbox/MajktProfile-Startup.json");
	auto app = majkt::CreateApplication();
	MAJKT_PROFILE_END_SESSION();

	MAJKT_PROFILE_BEGIN_SESSION("Runtime", get_current_dir() + "/src/sandbox/MajktProfile-Runtime.json");
	app->Run();
	MAJKT_PROFILE_END_SESSION();

	MAJKT_PROFILE_BEGIN_SESSION("Startup", get_current_dir() + "/src/sandbox/MajktProfile-Shutdown.json");
	delete app;
	MAJKT_PROFILE_END_SESSION();
	LOG(INFO) << "---------------  Majkt Engine Ended  ---------------";
	LOG(INFO) << "To view profiling results, open the profiles in chrome://tracing/: " << get_current_dir() << "/src/sandbox/";
}

#endif // MAJKT_ENGINE_PLATFORM
