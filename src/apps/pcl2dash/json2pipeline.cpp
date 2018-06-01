#include "lib_pipeline/pipeline.hpp"
#include "lib_media/mux/gpac_mux_mp4.hpp"
#include "multi_file_reader.hpp"
#include "cwi_pcl_encoder.hpp"
#include "options.hpp"

using namespace Modules;
using namespace Pipelines;

extern const char *g_appName;

std::unique_ptr<Pipeline> buildPipeline(const IConfig &iconfig) {
	auto config = safe_cast<const Config>(&iconfig);
	auto pipeline = uptr(new Pipeline);

	auto input = pipeline->addModule<MultifileReader>(config->inputPath);
	auto pclEncoder = pipeline->addModule<CWI_PCLEncoder>();
	auto muxer = pipeline->addModule<Mux::GPACMuxMP4>("pcl", 1000, Mux::GPACMuxMP4::FragmentedSegment, Mux::GPACMuxMP4::OneFragmentPerFrame, Mux::GPACMuxMP4::Browsers | Mux::GPACMuxMP4::ExactInputDur | Mux::GPACMuxMP4::NoEditLists);
	pipeline->connect(input, 0, pclEncoder, 0);
	pipeline->connect(pclEncoder, 0, muxer, 0);

	return pipeline;
}