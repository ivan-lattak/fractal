#ifndef FRACTAL_PARSER_H
#define FRACTAL_PARSER_H

#include <istream>
#include <string>

#include <mpfr.h>

#include "except.h"

namespace fractal {

    class parser {
    
    public:
        parser(const std::string&, std::istream&);

        bool get_params(std::string&, mpfr_t&, mpfr_t&, mpfr_t&, unsigned int&) const;

    private:
        const std::string mExecutableName;
        std::istream& mInputStream;

        bool parse_first_line(std::string&) const;
        void parse_line(std::string&) const;
        [[noreturn]] void usage() const;

    };
    
}

#endif // FRACTAL_PARSER_H
