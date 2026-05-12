#include "common.hpp"

#include <sstream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>

launch_options opts_parser(int argc, char *argv[])
{
    launch_options l_o;
    std::string config;
    std::string model_type;

    if (argc != 2)
        throw std::invalid_argument("Failed to execute program, e.g ./main 'inputfile.*'");

    std::vector<std::string> args(argv, argv + argc);
    std::fstream config_file("../" + args[1]);

    if (!config_file.is_open())
        throw std::invalid_argument("Failed to open file");

    std::getline(config_file, config);
    l_o.sim_time = std::stof(config);

    std::getline(config_file, config);
    std::istringstream iss(config);
    iss >> model_type;

    if (model_type == "uniform" || model_type == "Uniform")
        l_o.type_of_model = ModelType::unfiform;
    else if (model_type == "poissonian" || model_type == "Poissonian")
        l_o.type_of_model = ModelType::poissonian;
    else
        throw std::invalid_argument("Invalid type of model. Use uniform or poissonian");

    iss >> l_o.packet_size >> l_o.packet_interval;

    return l_o;
}
