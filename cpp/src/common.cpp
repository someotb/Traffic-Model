#include "common.hpp"
#include "traffic_models.hpp"

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
    std::fstream config_file("../../data/" + args[1]);

    if (!config_file.is_open())
        throw std::invalid_argument("Failed to open config file");

    std::getline(config_file, config);
    float st = std::stof(config);
    if (st >= 50.0f && st <= 3600.0f)
        l_o.sim_time = st;
    else
        throw std::invalid_argument("50.0 <= Simulation time <= 3600.0");

    std::getline(config_file, config);
    std::istringstream iss(config);
    iss >> model_type;

    if (model_type == "uniform" || model_type == "Uniform")
        l_o.type_of_model = ModelType::unfiform;
    else if (model_type == "poissonian" || model_type == "Poissonian")
        l_o.type_of_model = ModelType::poissonian;
    else
        throw std::invalid_argument("Invalid type of model. Use uniform or poissonian");

    iss >> l_o.packet_interval >> l_o.packet_size;
    if (iss.fail() || l_o.packet_interval <= 0 || l_o.packet_size <= 0)
         throw std::invalid_argument("Invalid model parameters. Expected: <model_type> <interval> <size>");

    return l_o;
}

void simulate(const launch_options &lo)
{
    float sim_time = lo.sim_time * 1000; // Считаем что интервал между пакетами в мс.
    float cur_time = 0.0f;
    std::ofstream output("../../data/data.csv", std::ios::trunc);

    if (!output.is_open())
        throw std::invalid_argument("Failed to open output file");

    if (lo.type_of_model == ModelType::poissonian)
    {
        output << "poissonian\n";
        Poissonian_traffic_model ptm(lo.packet_size, lo.packet_interval);
        while (true)
        {
            int pi = ptm.generate_interval();
            int ps = std::max(1, static_cast<int>(ptm.generate_packet_size()));
            cur_time += pi;
            if (cur_time >= sim_time) break;
            output << cur_time << "," << ps << "\n";
        }
    }
    else if (lo.type_of_model == ModelType::unfiform)
    {
        output << "unfiform\n";
        Uniform_traffic_model utm(lo.packet_size, lo.packet_interval);
        while (true)
        {
            int ps = utm.get_packet_length();
            int pi = utm.get_packet_interval();
            cur_time += pi;
            if (cur_time >= sim_time) break;
            output << cur_time << "," << ps << "\n";
        }
    }
}
