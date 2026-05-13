#include "common.hpp"

int main(int argc, char *argv[])
{
    launch_options lo = opts_parser(argc, argv);
    simulate(lo);
    return 0;
}
