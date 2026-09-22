#ifndef BESS_AUTH_H
#define BESS_AUTH_H

#include "bess_types.h"

bool bess_authorize(bess_role_t role, bool write_operation, bool safety_operation);

#endif
