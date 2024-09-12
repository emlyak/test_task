#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include <complex>
#include <fstream>


class Parser
{
public:
    Parser();

    ~Parser() = default;

    void read_file(const std::string file_name);

    std::vector<double> freqs;
    std::vector<std::complex<double>> data;


private:
    std::string file_name;


};

#endif // PARSER_H
