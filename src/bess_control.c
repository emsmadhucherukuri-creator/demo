#include "bess_control.h"
#include "bess_safety.h"

bool bess_mode_allows_power(bess_mode_t mode) { return mode == BESS_MODE_CHARGE || mode == BESS_MODE_DISCHARGE || mode == BESS_MODE_GRID_SUPPORT || mode == BESS_MODE_PEAK_SHAVING || mode == BESS_MODE_BACKUP; }

bess_status_t bess_set_mode(bess_mode_t requested, const bess_health_t *health, bess_mode_t *current) {
    if (health == NULL || current == NULL || requested > BESS_MODE_EMERGENCY) return BESS_ERR_INVALID;
    if (requested != BESS_MODE_EMERGENCY && health->emergency_stop) return BESS_ERR_STATE;
    if (requested == BESS_MODE_BACKUP && !health->breaker_closed) return BESS_ERR_STATE;
    *current = requested;
    return BESS_OK;
}

bess_status_t bess_command_power(bess_mode_t mode, double requested, const bess_telemetry_t *telemetry,
                                 const bess_limits_t *limits, const bess_health_t *health, double *approved) {
    if (!bess_mode_allows_power(mode)) { if (approved != NULL) *approved = 0.0; return BESS_ERR_STATE; }
    if (mode == BESS_MODE_CHARGE && requested > 0.0) requested = -requested;
    if (mode == BESS_MODE_DISCHARGE && requested < 0.0) requested = -requested;
    return bess_safe_power_command(requested, telemetry, limits, health, approved);
}
