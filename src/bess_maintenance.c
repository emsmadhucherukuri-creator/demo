#include "bess_maintenance.h"

void bess_maintenance_init(bess_maintenance_t *r, time_t now) { if(r!=NULL){r->charge_cycles=0U;r->energy_throughput_kwh=0.0;r->fault_count=0U;r->last_service=now;} }
void bess_maintenance_update(bess_maintenance_t *r, double power, double seconds, bool fault) { if(r==NULL||seconds<0.0)return; r->energy_throughput_kwh += power<0.0?-power:power; r->energy_throughput_kwh *= seconds/3600.0; if(fault)++r->fault_count; r->charge_cycles=(uint64_t)(r->energy_throughput_kwh/1000.0); }
bool bess_maintenance_due(const bess_maintenance_t *r, time_t now, uint32_t days) { return r!=NULL && now>=r->last_service && (uint64_t)(now-r->last_service)>=(uint64_t)days*86400U; }
