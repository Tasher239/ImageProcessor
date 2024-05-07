#include <memory>

#include "./include/data/image.h"
#include "./include/utils/args_processor.h"
#include "./include/io/image_format.h"
#include "./include/io/bmp.h"
#include "./include/utils/pipeline.h"
#include "./include/filters/negative.h"
#include "./include/filters/grayscale.h"
#include "./include/filters/crop.h"
#include "./include/filters/sharp.h"
#include "./include/filters/edge_detection.h"
#include "./include/filters/my_filter.h"
#include "./include/filters/gaussian_blur.h"
#include "./include/filters/glass_distortion.h"
#include <iostream>

Pipeline::Factory CreateFilterFactory() {
    Pipeline::Factory filter_factory;

    filter_factory.RegisterFilter<Negative::Factory>("-neg");
    filter_factory.RegisterFilter<GrayScale::Factory>("-gs");
    filter_factory.RegisterFilter<Crop::Factory>("-crop");
    filter_factory.RegisterFilter<Sharpening::Factory>("-sharp");
    filter_factory.RegisterFilter<EdgeDetection::Factory>("-edge");
    filter_factory.RegisterFilter<MyFilter::Factory>("-my_filter");
    filter_factory.RegisterFilter<GaussianBlur::Factory>("-blur");
    filter_factory.RegisterFilter<GlassDistortion::Factory>("-glass_dist");

    return filter_factory;
};

int main(int argc, char **argv) {
    try {
        ArgsProcessor args_processor(argc, argv);
        std::cout << "read arguments: OK\n";
        std::unique_ptr<ImageFormat> image_format = std::make_unique<BMP>();

        Image image = image_format->Load(args_processor.GetInputFile());
        std::cout << "Download Image: OK\n";

        Pipeline::Factory filter_factory = CreateFilterFactory();
        std::cout << "create filter factory: OK\n";

        Pipeline pipeline;
        for (const ArgsProcessor::FilterInfo &filter_info : args_processor.GetFilters()) {
            pipeline.AddFilter(filter_factory.CreateFilter(filter_info.GetName(), filter_info.GetParams()));
        }
        std::cout << "Add filters to pipeline: OK\n";

        Image new_image = pipeline.Process(image);
        std::cout << "Process: OK\n";

        image_format->Save(new_image, args_processor.GetOutputFile());
        std::cout << "Save Image: OK\n";

    } catch (const std::exception &exception) {
        std::cerr << "Error: " << exception.what() << '\n';
        return 1;
    }
    return 0;
}
