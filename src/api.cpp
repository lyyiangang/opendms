#include <api.hpp>
#include <includes.hpp>
#include <utils/common_utils.hpp>
#include <basic/Pipeline.hpp>
#include <fstream>
#include <memory>

std::unique_ptr<opendms::Pipeline> _pipeline;

namespace opendms
{
    DMS::DMS(){

    }

    DMS::~DMS(){

    }

    int DMS::init(const std::string& cfg_file){
        RegistLogger();
        lg->info("reading config file from {}", cfg_file);
        std::ifstream f_stream(cfg_file);
        ASSERT(f_stream.is_open());
        json js;
        try{
            f_stream >> js;
            lg->info("config file content:{}", js.dump(4));
        }
        catch(json::exception& e){
            lg->critical("error when parse config file.messgae:{}, id:{}", e.what(), e.id);
            return 1;
        }

        // Pipeline pipeline(js["pipline"]);
        _pipeline = std::make_unique<Pipeline>(js["pipline"]);
        return 0;
    }

    int DMS::ProcessOneFrame(const Frame& frame, FaceData* face_result){
        int error = _pipeline->ProcessFrame(frame);
        *face_result = _pipeline->GetFaceData();
        return error;
    }
} // namespace opendms
