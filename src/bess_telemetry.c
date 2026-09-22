#include "bess_telemetry.h"
#include <stdio.h>
#include <string.h>

void bess_telemetry_init(bess_telemetry_store_t *s) { if(s!=NULL) memset(s,0,sizeof *s); }
bess_status_t bess_telemetry_record(bess_telemetry_store_t *s, const bess_telemetry_t *sample) { if(s==NULL||sample==NULL)return BESS_ERR_INVALID; s->samples[s->next]=*sample; s->next=(s->next+1U)%BESS_TELEMETRY_HISTORY; if(s->count<BESS_TELEMETRY_HISTORY)++s->count; return BESS_OK; }
bess_status_t bess_telemetry_latest(const bess_telemetry_store_t *s, bess_telemetry_t *sample) { if(s==NULL||sample==NULL||s->count==0U)return BESS_ERR_INVALID; *sample=s->samples[(s->next+BESS_TELEMETRY_HISTORY-1U)%BESS_TELEMETRY_HISTORY]; return BESS_OK; }
bess_status_t bess_telemetry_export_csv(const bess_telemetry_store_t *s, const char *path) { if(s==NULL||path==NULL)return BESS_ERR_INVALID; FILE *f=fopen(path,"w"); if(f==NULL)return BESS_ERR_STATE; (void)fprintf(f,"timestamp,voltage_v,current_a,temperature_c,soc_pct,soh_pct,active_power_kw,reactive_power_kvar,site_load_kw,renewable_kw\n"); for(size_t i=0;i<s->count;++i){const bess_telemetry_t *t=&s->samples[(s->next+s->count-BESS_TELEMETRY_HISTORY+i)%BESS_TELEMETRY_HISTORY]; (void)fprintf(f,"%lld,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n",(long long)t->timestamp,t->voltage_v,t->current_a,t->temperature_c,t->soc_pct,t->soh_pct,t->active_power_kw,t->reactive_power_kvar,t->site_load_kw,t->renewable_kw);} return fclose(f)==0?BESS_OK:BESS_ERR_STATE; }
