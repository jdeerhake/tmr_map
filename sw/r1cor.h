#include <stdio.h>
#include <ctype.h>
#include <math.h>

typedef struct {

  /* TIME TAG */
  short Tim_Moy_1;             /* num days from Jan 1, 1958 00:00:00 (days)  */
  long  Tim_Moy_2;             /* milli seconds within day            (sec)  */
  short Tim_Moy_3;             /* microseconds within sec        (microsec)  */
  
  /* LOCATION AND SURFACE TYPE */
  signed long Lat_Tra;        /* latitude                        (microdeg)  */
  signed long Lon_Tra;        /* longitude                       (microdeg)  */
  unsigned char Alt_Surface_Type; /* altimeter surface_type           (n/a)  */
  unsigned char Rad_Surface_Type; /* radiometer_surface_type          (n/a)  */
  
  /* FLAGS */
  unsigned char TMR_Bad;  /* TMR Brightness temp. interpolation flag  (n/a)  */
  unsigned char Instr_State_TMR; /* TMR Instrument state flag         (n/a)  */
  
  /* BRIGHTNESS TEMPERATURE */
  signed short Tb_18;        /* 18 GHz  brightness temp        (10-2 deg K) */ 
  signed short Tb_21;        /* 23 GHz  brightness temp        (10-2 deg K) */ 
  signed short Tb_37;        /* 37 GHz  brightness temp        (10-2 deg K) */ 
  
/* ALTIMETER RANGE CORRECTIONS */
  signed short Wet_H_Rad;    /* TMR wet tropo correction           (10-4 m) */
  
  /* BACKSCATTER COEFFICIENT */
  short Atm_Att_Sig0_Corr_Ku; /* 2-way Atmospheric attenuation on Ku Band
                              /* backscatter coeff                (10-2 dB) */
  short Atm_Att_Sig0_Corr_C;  /* 2-way Atmospheric attenuation on C Band
                              /* backscatter coeff                (10-2 dB) */
  
  /* ENVIRONMENTAL PARAMETERS */
  unsigned short Wind_Speed_Rad;  /* TMR wind speed                  (cm/s) */
  signed short Rad_Water_Vapor;   /* TMR water vapor content   (10-2 g/cm2) */
  signed short Rad_Liquid_Water;  /* TMR liquid water content  (10-2 Kg/m2) */

  /*Spare*/
  short Spare; 

  /*Spare*/
  long Spare2;
} r1cor;

#define R1COR_RECSIZE 44

int readr1cor(r1cor *rcor, int ndat, long swap, FILE *fin);
int numrec_r1cor(long *numdata, FILE *fp,long recsize, FILE *fnotes);
int writer1cor(r1cor *rcor, long swap, FILE *fin);

