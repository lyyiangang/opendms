#include <includes.hpp>
#include <utils/common_utils.hpp>
#include <utils/FrameSource.hpp>
#include <ui/visulizer.hpp>
#include <basic/Pipeline.hpp>
#include <fstream>
using namespace opendms;

int main(int arc, char** argv){
    RegistLogger();
    std::string cfg_file = "../cfg.json";
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
        abort();
    }
    FrameSource frame_source("../p_data/rgb_640x480.avi");
    Pipeline pipeline(js["pipline"]);
    Visulizer vis;
    while(1){
        Frame frame = frame_source.frame();
        if(frame.img.empty()){
            lg->warn("empty frmae.");
            break;
        }
        pipeline.ProcessFrame(frame);
        const FaceData& det_result = pipeline.GetFaceData();
        vis.Render(frame, det_result);
        bool do_exit = vis.Show();
        if(do_exit){
            lg->warn("exit loop");
            break;
        }
    };

    return 0;
}