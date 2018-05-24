#include <exception>
#include <iostream>
#include <string>

#include <cstdlib>
#include <mpfr.h>

#include "parser.h"

#define FILENAME_SIZE (1 << 16)

const mpfr_prec_t DEFAULT_PREC = 256;

int main(int argc, const char** argv) {
    try {
        const char* executableName = argc > 0 ? argv[0] : "";
        fractal::parser parser(executableName);

        std::string outputFile;
        mpfr_t xCenter, yCenter, width;
        unsigned int maxIters;

        while (parser.read(outputFile, xCenter, yCenter, width, maxIters)) {
            std::cerr << "outputFile = \"" << outputFile << "\"\n";
            std::cerr << "xCenter = \"" << mpfr_get_d(xCenter, MPFR_RNDN) << "\"\n";
            std::cerr << "yCenter = \"" << mpfr_get_d(yCenter, MPFR_RNDN) << "\"\n";
            std::cerr << "width = \"" << mpfr_get_d(width, MPFR_RNDN) << "\"\n";
            std::cerr << "maxIters = \"" << maxIters << "\"\n";
        }
    }
    catch (std::exception& e) {
        std::cerr << "An unhandled exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "An unhandled exception occurred" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}