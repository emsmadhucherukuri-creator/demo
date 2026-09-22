#include "bess_ems.h"
#include "bess_safety.h"

bess_status_t bess_ems_dispatch(const bess_ems_config_t *c, const bess_telemetry_t *t, const bess_limits_t *l, const bess_health_t *h, double *power) {
    if(c==NULL||t==NULL||l==NULL||h==NULL||power==NULL)return BESS_ERR_INVALID;
    double target=c->target_peak_kw-t->site_load_kw;
    if(t->site_load_kw>c->target_peak_kw) target=t->site_load_kw-c->target_peak_kw; else target=-(t->renewable_kw>0.0?t->renewable_kw:0.0);
    if(c->backup_reserve && t->soc_pct<=l->reserve_soc_pct && target>0.0)target=0.0;
    return bess_safe_power_command(target,t,l,h,power);
}
