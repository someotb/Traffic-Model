#pragma once

enum class ModelType
{
    unfiform,
    poissonian
};

struct launch_options
{
    float sim_time;
    ModelType type_of_model;
    int packet_size;
    int packet_interval;
};

launch_options opts_parser(int argc, char *argv[]);

void simulate(const launch_options &lo);
