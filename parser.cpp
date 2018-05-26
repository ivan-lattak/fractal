#include <istream>
#include <isstream>
#include <string>

#include <mpfr.h>

#include "parser.h"

namespace fractal {

    parser::parser(const std::string& pExecutableName,
                   std::istream& pInputStream) :
            mExecutableName(pExecutableName),
            mInputStream(pInpuStream) { }

    bool parser::get_params(std::string& pOutputFile,
                            mpfr_t& pXCenter,
                            mpfr_t& pYCenter,
                            mpfr_t& pWidth,
                            unsigned int& pMaxIters) const {
        std::string line;
        std::istringstream lineStream;
        std::string xCenter, yCenter, width;

        if (!parse_first_line(line)) {
            return false;
        }
        pOutputFile = line;

        parse_line(line);
        lineStream.str(line);
        lineStream.clear();
        lineStream >> xCenter >> yCenter;
        if (mpfr_init_set_str(pXCenter, xCenter.c_str(), 10, MPFR_RNDN) ||
            mpfr_init_set_str(pYCenter, yCenter.c_str(), 10, MPFR_RNDN)    ) {
            usage();
        }

        parse_line(line);
        lineStream.str(line);
        lineStream.clear();
        lineStream >> width;
        if (mpfr_init_set_str(pWidth, width.c_str(), 10, MPFR_RNDN)) {
            usage();
        }
        if (mpfr_sgn(pWidth) == 0) {
            std::cerr << "Invalid input: <width> is zero!" << std::endl;
            throw fractal::bad_usage();
        }
        if (mpfr_sgn(pWidth) < 0) {
            mpfr_neg(pWidth, pWidth, MPFR_RNDN);
        }

        parse_line(line);
        lineStream.str(line);
        lineStream.clear();
        lineStream >> pMaxIters;
        if (pMaxIters == 0) {
            usage();
        }

        std::getline(std::cin, line);

        return true;
    }

    bool parser::parse_first_line(std::string& line) const {
        std::getline(std::cin, line);
        if (!std::cin.good()) {
            return false;
        }
        if (line.empty()) {
            usage();
        }
        return true;
    }

    void parser::parse_line(std::string& line) const {
        std::getline(std::cin, line);
        if (!std::cin.good()) {
            usage();
        }
        if (line.empty()) {
            usage();
        }
    }

    [[noreturn]] void parser::usage() const {
        std::cerr << "Usage: " << mExecutableName << "\n";
        std::cerr << "<output-file>\\n\n";
        std::cerr << "<x-center> <y-center>\\n\n";
        std::cerr << "<width>\\n\n";
        std::cerr << "<max-iters>\\n\n";
        std::cerr << "\n";
        std::cerr << "Renders a rectangular section of the Mandebrot set, "
                     "centered on the complex number (<x-center> + <y-center>*j), "
                     "which is <width> wide on the x-axis, and uses at most "
                     "<max-iters> iterations for each pixel. The image is then output "
                     "into <output-file> in BMP format with 24-bit depth, "
                     "1920x1080 pixels large." << std::endl;

        throw fractal::bad_usage();
    }

}
