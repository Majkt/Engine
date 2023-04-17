#ifndef MAJKT_ENGINE_DEBUG_INSTRUMENTOR_H_
#define MAJKT_ENGINE_DEBUG_INSTRUMENTOR_H_

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt
{
	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* current_session_;
		std::ofstream output_stream_;
		int profile_count_;
	public:
		Instrumentor()
			: current_session_(nullptr), profile_count_(0)
		{
		}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			output_stream_.open(filepath);
			WriteHeader();
			current_session_ = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			output_stream_.close();
			delete current_session_;
			current_session_ = nullptr;
			profile_count_ = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (profile_count_++ > 0)
				output_stream_ << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			output_stream_ << "{";
			output_stream_ << "\"cat\":\"function\",";
			output_stream_ << "\"dur\":" << (result.End - result.Start) << ',';
			output_stream_ << "\"name\":\"" << name << "\",";
			output_stream_ << "\"ph\":\"X\",";
			output_stream_ << "\"pid\":0,";
			output_stream_ << "\"tid\":" << result.ThreadID << ",";
			output_stream_ << "\"ts\":" << result.Start;
			output_stream_ << "}";

			output_stream_.flush();
		}

		void WriteHeader()
		{
			output_stream_ << "{\"otherData\": {},\"traceEvents\":[";
			output_stream_.flush();
		}

		void WriteFooter()
		{
			output_stream_ << "]}";
			output_stream_.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: name_(name), stopped_(false)
		{
			start_timepoint_ = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!stopped_)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint_).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t ThreadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ name_, start, end, ThreadID });

			stopped_ = true;
		}
	private:
		const char* name_;
		std::chrono::time_point<std::chrono::high_resolution_clock> start_timepoint_;
		bool stopped_;
	};

} // namespace majkt

#define MAJKT_PROFILE 1
#if MAJKT_PROFILE
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define MAJKT_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define MAJKT_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define MAJKT_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define MAJKT_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define MAJKT_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define MAJKT_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define MAJKT_FUNC_SIG __func__
	#else
		#define MAJKT_FUNC_SIG "MAJKT_FUNC_SIG unknown!"
	#endif

	#define MAJKT_PROFILE_BEGIN_SESSION(name, filepath) ::majkt::Instrumentor::Get().BeginSession(name, filepath)
	#define MAJKT_PROFILE_END_SESSION() ::majkt::Instrumentor::Get().EndSession()
	#define MAJKT_PROFILE_SCOPE(name) ::majkt::InstrumentationTimer timer##__LINE__(name);
	#define MAJKT_PROFILE_FUNCTION() MAJKT_PROFILE_SCOPE(MAJKT_FUNC_SIG)
#else
	#define MAJKT_PROFILE_BEGIN_SESSION(name, filepath)
	#define MAJKT_PROFILE_END_SESSION()
	#define MAJKT_PROFILE_SCOPE(name)
	#define MAJKT_PROFILE_FUNCTION()
#endif

#endif  // MAJKT_ENGINE_DEBUG_INSTRUMENTOR_H_
