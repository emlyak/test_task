#include "parser.h"

Parser::Parser() {}

void Parser::read_file(const std::string& file_name)
{
    std::ifstream file(file_name);

    // skip part of file
    while(!file.eof())
    {
        std::string inner_buf;
        file >> inner_buf;
        if (inner_buf == "S11")
            break;
    }

    // read freqs and values
    while(!file.eof())
    {
        double freq;
        double real;
        double im;
        file >> freq;
        file >> real;
        file >> im;

        data.emplace_back(
            // translate to real space
            20 * std::log10(std::sqrt(std::pow(real, 2) + std::pow(im, 2))));
        freqs.push_back(freq);
    }
}

// void Parser::normalize(const size_t& width, size_t& height)
// {
//     const auto [min, max] = std::minmax_element(freqs.begin(), freqs.end());

//     const double oldRange {*max - *min};
//     const double k = width / oldRange;

//     std::for_each(freqs.begin(), freqs.end(),
//                   [&oldRange, &k](double &n) {(n - oldRange) * k;});


// }

