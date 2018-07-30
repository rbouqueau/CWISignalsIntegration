#include "lib_appcommon/options.hpp"
#include "lib_utils/format.hpp"
#include "lib_utils/tools.hpp"
#include "options.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>

const char *g_appName = "pcl2dash";

extern int safeMain(int argc, char const* argv[]);

std::unique_ptr<const IConfig> processArgs(int argc, char const* argv[]) {
	CmdLineOptions opt;
	auto opts = uptr(new Config);

	opt.add("n", "frames", &opts->numFrames, format("Num frames to process [default=%s]", opts->numFrames));
	opt.add("t", "threading", &opts->threading, format("Threads: 1 is mono, 2 is multi [default=%s]", opts->threading));

	auto files = opt.parse(argc, argv);
	if (files.size() > 1) {
		Log::msg(Error, "Usage: %s [options, see below] [PCL_files_pattern]", g_appName);
		opt.printHelp(std::cerr);
		throw std::runtime_error("invalid command line");
	}

	if (files.size() == 1)
		opts->inputPath = files[0];

	return std::move(opts);
}

int main(int argc, char const* argv[]) {
	try {
		return safeMain(argc, argv);
	} catch (std::exception const& e) {
		std::cerr << "[" << g_appName << "] " << "Error: " << e.what() << std::endl;
		return 1;
	}
}
