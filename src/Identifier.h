//
// Created by pc on 11-12-21.
//

#ifndef _IDENTIFIER_H
#define _IDENTIFIER_H

#include "Types.h"

#include <cstddef>

namespace trace {

    struct Identifier {

        Identifier();

        size_t        identifier;
        static size_t s_maxIdentifier;
    };
} // namespace trace

#endif // _IDENTIFIER_H
