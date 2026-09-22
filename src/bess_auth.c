#include "bess_auth.h"

bool bess_authorize(bess_role_t role, bool write_operation, bool safety_operation) {
    if (role > BESS_ROLE_ADMIN) return false;
    if (safety_operation) return role >= BESS_ROLE_ENGINEER;
    if (write_operation) return role >= BESS_ROLE_OPERATOR;
    return true;
}
