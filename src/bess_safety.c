#include "bess_safety.h"
#include <math.h>
#include <stdio.h>

bess_limits_t bess_default_limits(void) {
    bess_limits_t l = { 600.0, 900.0, -20.0, 55.0, 500.0, 500.0, 10.0, 95.0, 20.0, 500.0, 500.0 };
    return l;
}

static bess_status_t fail(char *reason, size_t size, const char *text) {
    if (reason != NULL && size > 0U) (void)snprintf(reason, size, "%s", text);
    return BESS_ERR_LIMIT;
}

bess_status_t bess_validate_telemetry(const bess_telemetry_t *t, const bess_limits_t *l,
                                      const bess_health_t *h, char *reason, size_t size) {
    if (t == NULL || l == NULL || h == NULL) return BESS_ERR_INVALID;
    if (!h->bms_ok || !h->pcs_ok || !h->communication_ok || h->emergency_stop) return fail(reason, size, "unsafe subsystem state");
    if (!isfinite(t->soc_pct) || t->soc_pct < l->min_soc_pct || t->soc_pct > l->max_soc_pct) return fail(reason, size, "state of charge limit");
    if (!isfinite(t->temperature_c) || t->temperature_c < l->min_temperature_c || t->temperature_c > l->max_temperature_c) return fail(reason, size, "temperature limit");
    if (!isfinite(t->voltage_v) || t->voltage_v < l->min_voltage_v || t->voltage_v > l->max_voltage_v) return fail(reason, size, "voltage limit");
    return BESS_OK;
}

bess_status_t bess_safe_power_command(double requested, const bess_telemetry_t *t, const bess_limits_t *l,
                                      const bess_health_t *h, double *approved) {
    char reason[32];
    if (approved == NULL) return BESS_ERR_INVALID;
    if (bess_validate_telemetry(t, l, h, reason, sizeof reason) != BESS_OK) { *approved = 0.0; return BESS_ERR_LIMIT; }
    if (!isfinite(requested)) { *approved = 0.0; return BESS_ERR_INVALID; }
    if (requested > l->max_discharge_kw) requested = l->max_discharge_kw;
    if (requested < -l->max_charge_kw) requested = -l->max_charge_kw;
    if (t->soc_pct <= l->reserve_soc_pct && requested > 0.0) requested = 0.0;
    if (t->soc_pct >= l->max_soc_pct && requested < 0.0) requested = 0.0;
    *approved = requested;
    return BESS_OK;
}
