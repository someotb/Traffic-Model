#pragma once

#include <random>

class Poissonian_traffic_model
{
private:
    float _packet_length;
    float _packet_interval;
    std::mt19937 _generator;
    std::poisson_distribution<int> _interval_dist;
    std::exponential_distribution<float> _size_dist;

public:
    void set_packet_length(float packet_length) { _packet_length = packet_length; }
    void set_packet_interval(float packet_interval) { _packet_interval = packet_interval; }
    float get_packet_length() { return _packet_length; }
    float get_packet_interval() { return _packet_interval; }

    Poissonian_traffic_model(float packet_length, float packet_interval)
        : _packet_length(packet_length),
        _packet_interval(packet_interval),
        _generator(std::random_device{}()),
        _interval_dist(packet_interval),
        _size_dist(1.0f / packet_length)
    {}

    ~Poissonian_traffic_model() = default;

    int generate_interval() {
        return _interval_dist(_generator);
    }

    float generate_packet_size() {
        return _size_dist(_generator);
    }
};

class Uniform_traffic_model
{
    private:
        int _packet_length;
        int _packet_interval;
    public:
        void set_packet_length(int packet_length) { _packet_length = packet_length; }
        void set_packet_interval(int packet_interval) { _packet_interval = packet_interval; }
        int get_packet_length() { return _packet_length; }
        int get_packet_interval() { return _packet_interval; }

        Uniform_traffic_model(int pack_len, int pack_int)
            : _packet_length(pack_len),
            _packet_interval(pack_int)
            {}

        ~Uniform_traffic_model() = default;
};
