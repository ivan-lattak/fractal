#ifndef FRACTAL_EXCEPT_H
#define FRACTAL_EXCEPT_H

#include <exception>

namespace fractal {

    class bad_usage : public std::exception {

        const char* what() const noexcept {
            return "Bad usage";
        }

    };
    
}

#endif // FRACTAL_EXCEPT_H
