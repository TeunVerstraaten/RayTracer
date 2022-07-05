//
// Created by pc on 11-12-21.
//

#include "Identifier.h"

namespace trace {

    size_t Identifier::s_maxIdentifier = 0;

    Identifier::Identifier() : identifier(s_maxIdentifier) {
        ++s_maxIdentifier;
    }
} // namespace trace