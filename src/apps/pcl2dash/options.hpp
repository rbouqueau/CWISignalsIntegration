#pragma once

#include "lib_appcommon/options.hpp"
#include "lib_pipeline/pipeline.hpp"
#include <string>

struct Config : IConfig {
	std::string inputPath;
	int numFrames = std::numeric_limits<int>::max();
	int threading = 2;
	int segDurInMs = 1;
	int delayInSeg = 0;
	std::string param_file;
};
