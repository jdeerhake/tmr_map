drop table if exists data;

create table data (
  tim_moy_1           int,
  tim_moy_2           int,
  tim_moy_3           int,
  lat_tra             int,
  lon_tra             int,
  alt_surface_type    int unsigned,
  rad_surface_type    int unsigned,
  tmr_bad             tinyint,
  instr_state_tmr     tinyint,
  tb_18               int,
  tb_21               int,
  tb_37               int,
  wet_h_rad           int,
  atm_att_sig0_corr_ku      int,
  atm_att_sig0_corr_c       int,
  wind_speed_rad            int unsigned,
  rad_water_vapor           int,
  rad_liquid_water          int,
  index(tim_moy_1, lat_tra, lon_tra, tmr_bad)
) engine=myisam;

alter table data disable keys;