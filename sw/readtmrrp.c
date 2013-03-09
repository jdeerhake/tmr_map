/**********************************************************************************
* Purpose:
* An example program to read data of TMR replacement product
* Input:  file name
* Output:
*        print out of the first ndump records
* Date: 08/30/06
**********************************************************************************/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "r1cor.h"

int main(int argc, char *argv[])
{
  long   i, j,swap, numdata;
  FILE *ifin;
  r1cor rcor;

  if (argc == 1) {
    fprintf(stdout,"Usage: %s tmr_rep_prod_pass_file\n", argv[0]);
    exit(1);
  }

  /* Correction Product is written in Unix byte order (Big Endian).
  This example program is tested on Linux system (Little Endian),
  so the bytes order needs to be swapped in this case*/

  i = 1;
  swap = *((char*) &i);

  /* file name convention TMR_Cccc_Pppp, ccc is cycle number, ppp is Pass number*/
  ifin = fopen(argv[1],"rb");
  if(ifin == NULL){
    fprintf(stdout, "readtmrrp: Error in file opening %s \n", argv[1]);
    exit(-1);
  }
  /*fprintf(stdout,"readtmrrp: reading correction data file %s \n", argv[1]);*/
  /* check number of records in the file*/
  if (numrec_r1cor(&numdata, ifin, R1COR_RECSIZE, stdout) == 1) {
    /*fprintf(stdout,"readtmrrp: Error with file %s\n", ifin);*/
    fclose(ifin);
  }

  /* read and then dump records*/
  for (i = 0; i < numdata; ++i) {
    readr1cor(&rcor, i, swap, ifin);
    if(i == 0){
      /*fprintf(stdout," index    day    millisec    microsec lat(microdeg) lon(microdeg)  alt_surf_type  rad_surf_type  tmr_bad instr_state_tmr tb_18 (10-2 K) tb_21 (10-2K) tb_37(10-2K) pd (10-4m) attsig0K (10-2dB) attsig0C (10-2dB) WindSpeedRad(cm/s) RadWaterVapor(10-2 g/cm2) RadLiquidWater (10-2 Kg/m2) \n");*/
    }
    fprintf(stdout,"%d,%ld,%d,%ld,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d \n",
	    rcor.Tim_Moy_1, rcor.Tim_Moy_2, rcor.Tim_Moy_3,
	    rcor.Lat_Tra, rcor.Lon_Tra,
	    rcor.Alt_Surface_Type, rcor.Rad_Surface_Type,
	    rcor.TMR_Bad, rcor.Instr_State_TMR,
	    rcor.Tb_18, rcor.Tb_21, rcor.Tb_37,
	    rcor.Wet_H_Rad,
	    rcor.Atm_Att_Sig0_Corr_Ku,rcor.Atm_Att_Sig0_Corr_C,
	    rcor.Wind_Speed_Rad, rcor.Rad_Water_Vapor, rcor.Rad_Liquid_Water);
  }
  fclose(ifin);
  return 0;

}

