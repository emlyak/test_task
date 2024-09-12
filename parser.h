#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include <cmath>
#include <complex>
#include <fstream>


class Parser
{
public:
    Parser();

    ~Parser() = default;

    void read_file(const std::string& file_name);

    std::vector<double> freqs;
    std::vector<double> data;


private:
    std::string file_name;

    void fit_to_window(const size_t& width, size_t& height);


};

#endif // PARSER_H
