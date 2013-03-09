#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "r1cor.h"

/***********************************************************************
* FUNCTION: NUMREC_R1COR
* Purpose:
* To determine the number of data records in the Radiometer products
*
* Input:
*   fp       - Pointer to the data file
*   fnotes   - Notes file
* Output:
*   numdata  - Number of data records
* FUNCTION returns 1 if error with number of bytes in file
***********************************************************************/

int numrec_r1cor(long *numdata, FILE *fp,long recsize, FILE *fnotes)
{
   long nbytes, nhrec, nhbyte, ndbyte;

/* Go to the end of file and count the number of bytes to the end of file
*/
   fseek(fp, 0, SEEK_END);
   nbytes = ftell(fp);

/* Make sure that there are an integer number of records in the file
*  given the number of bytes per record
*/
   if (nbytes >= recsize) {
      if ((nbytes%recsize) == 0) {
	*numdata = nbytes/recsize;
	/*fprintf(fnotes,"numrec_r1cor: %5d data records: total bytes = %d: recsize = %d\n", *numdata, nbytes, recsize);*/
	return 0;
     }
     else {
       fprintf(fnotes,"numrec_r1cor: There are NOT an integer number of records in this file\n");
       return 1;
     }
   }
   else {
     fprintf(fnotes,"numrec_r1cor: There are NOT enough bytes for a record in this file\n");
     return 1;
   }
}

/**********************************************************************
* FUNCTION: READR1COR
* Purpose:
* To read each element of a data line of a Radiometer Correction data file intro
* a structure
*
* Input:
*   fin   - The pointer to the Jason Correction data  file
*   ndat  - The data point number
*           Note first data point has ndat = 0
*                last data point has ndat = numdat - 1
*                (numdat = number of data points in file)
*   swap  - 1 indicates swap bytes
* Output:
*   rcor - Structure of data line
*********************************************************************/

int readr1cor(r1cor *rcor, int ndat, long swap, FILE *fin)
{
   int offset, i, off;
   unsigned char buf[R1COR_RECSIZE];

   offset = ndat*R1COR_RECSIZE;
   fseek(fin, offset, SEEK_SET);

   fread(buf, sizeof(buf), 1, fin);
   off = 0;

   /* TIME TAG */
   memmove(&(*rcor).Tim_Moy_1, &buf[off], sizeof((*rcor).Tim_Moy_1));
   off += sizeof((*rcor).Tim_Moy_1);

   memmove(&(*rcor).Tim_Moy_2, &buf[off], sizeof((*rcor).Tim_Moy_2));
   off += sizeof((*rcor).Tim_Moy_2);

   memmove(&(*rcor).Tim_Moy_3, &buf[off], sizeof((*rcor).Tim_Moy_3));
   off += sizeof((*rcor).Tim_Moy_3);


   /* LOCATION AND SURFACE TYPE */
   memmove(&(*rcor).Lat_Tra, &buf[off], sizeof((*rcor).Lat_Tra));
   off += sizeof((*rcor).Lat_Tra);

   memmove(&(*rcor).Lon_Tra, &buf[off], sizeof((*rcor).Lon_Tra));
   off += sizeof((*rcor).Lon_Tra);

   memmove(&(*rcor).Alt_Surface_Type, &buf[off], sizeof((*rcor).Alt_Surface_Type));
   off += sizeof((*rcor).Alt_Surface_Type);

   memmove(&(*rcor).Rad_Surface_Type, &buf[off], sizeof((*rcor).Rad_Surface_Type));
   off += sizeof((*rcor).Rad_Surface_Type);

   memmove(&(*rcor).TMR_Bad, &buf[off], sizeof((*rcor).TMR_Bad));
   off += sizeof((*rcor).TMR_Bad);

   memmove(&(*rcor).Instr_State_TMR, &buf[off], sizeof((*rcor).Instr_State_TMR));
   off += sizeof((*rcor).Instr_State_TMR);


   /* BRIGHTNESS TEMPERATURE */
   memmove( &(*rcor).Tb_18, &buf[off],sizeof((*rcor).Tb_18));
   off += sizeof((*rcor).Tb_18);
   memmove( &(*rcor).Tb_21,&buf[off], sizeof((*rcor).Tb_21));
   off += sizeof((*rcor).Tb_21);
   memmove(&(*rcor).Tb_37,&buf[off],  sizeof((*rcor).Tb_37));
   off += sizeof((*rcor).Tb_37);

   /* ALTIMETER RANGE CORRECTIONS */
   memmove(&(*rcor).Wet_H_Rad, &buf[off], sizeof((*rcor).Wet_H_Rad));
   off += sizeof((*rcor).Wet_H_Rad);

    /* BACKSCATTER COEFFICIENT */
   memmove( &(*rcor).Atm_Att_Sig0_Corr_Ku, &buf[off],sizeof((*rcor).Atm_Att_Sig0_Corr_Ku));
   off += sizeof((*rcor).Atm_Att_Sig0_Corr_Ku);

   memmove( &(*rcor).Atm_Att_Sig0_Corr_C, &buf[off],sizeof((*rcor).Atm_Att_Sig0_Corr_C));
   off += sizeof((*rcor).Atm_Att_Sig0_Corr_C);

 /* ENVIRONMENTAL PARAMETERS */
   memmove(&(*rcor).Wind_Speed_Rad,&buf[off],  sizeof((*rcor).Wind_Speed_Rad));
   off += sizeof((*rcor).Wind_Speed_Rad);
   memmove(&(*rcor).Rad_Water_Vapor, &buf[off], sizeof((*rcor).Rad_Water_Vapor));
   off += sizeof((*rcor).Rad_Water_Vapor);
   memmove( &(*rcor).Rad_Liquid_Water, &buf[off],sizeof((*rcor).Rad_Liquid_Water));
   off += sizeof((*rcor).Rad_Liquid_Water);

 /* Spare */
   memmove( &(*rcor).Spare, &buf[off],sizeof((*rcor).Spare));
   off += sizeof((*rcor).Spare);

 /* Spare2 */
   memmove( &(*rcor).Spare2, &buf[off],sizeof((*rcor).Spare2));
   off += sizeof((*rcor).Spare2);


/* If your system does not use Unix byte order, bytes have to be swapped
   for 2 and 4 byte integers, since the byte order is reversed from Unix.
   Remove the comments around the swapbyte and recompile.
*/
   if (swap == 1) {
     swapbyte(&(*rcor).Tim_Moy_1, 0, 2);
     swapbyte(&(*rcor).Tim_Moy_2, 0, 4);
     swapbyte(&(*rcor).Tim_Moy_3, 0, 2);

     swapbyte(&(*rcor).Lat_Tra, 0, 4);
     swapbyte(&(*rcor).Lon_Tra, 0, 4);

     swapbyte(&(*rcor).Tb_18,0,2);
     swapbyte(&(*rcor).Tb_21,0,2);
     swapbyte(&(*rcor).Tb_37,0,2);

     swapbyte(&(*rcor).Wet_H_Rad, 0, 2);

     swapbyte(&(*rcor).Atm_Att_Sig0_Corr_Ku,0,2);
     swapbyte(&(*rcor).Atm_Att_Sig0_Corr_C,0,2);

     swapbyte(&(*rcor).Wind_Speed_Rad,0,2);
     swapbyte(&(*rcor).Rad_Water_Vapor,0,2);
     swapbyte(&(*rcor).Rad_Liquid_Water,0,2);

     swapbyte(&(*rcor).Spare,0,2);
     swapbyte(&(*rcor).Spare2,0,4);
   }
   return 0;
}
/***************************************************************************
* FUNCTION: WRITER1COR
* Purpose:
* To write an element of a data line of correction product
*
* Input:
*   (*r1cor) - Structure of data line
*   fin     - The pointer to the Jason Real Time data file
*   swap    - Flag indicating if byte swapping needs to be performed
*             1 = swap bytes
*
****************************************************************************/

int writer1cor(r1cor *rcor, long swap, FILE *fin)
{
   long offset, i,j, off;
   unsigned char buf[R1COR_RECSIZE];

   if (swap == 1) {
     swapbyte(&(*rcor).Tim_Moy_1, 0, 2);
     swapbyte(&(*rcor).Tim_Moy_2, 0, 4);
     swapbyte(&(*rcor).Tim_Moy_3, 0, 2);

     swapbyte(&(*rcor).Lat_Tra, 0, 4);
     swapbyte(&(*rcor).Lon_Tra, 0, 4);

     swapbyte(&(*rcor).Tb_18,0,2);
     swapbyte(&(*rcor).Tb_21,0,2);
     swapbyte(&(*rcor).Tb_37,0,2);

     swapbyte(&(*rcor).Wet_H_Rad, 0, 2);

     swapbyte(&(*rcor).Atm_Att_Sig0_Corr_Ku,0,2);
     swapbyte(&(*rcor).Atm_Att_Sig0_Corr_C,0,2);

     swapbyte(&(*rcor).Wind_Speed_Rad,0,2);
     swapbyte(&(*rcor).Rad_Water_Vapor,0,2);
     swapbyte(&(*rcor).Rad_Liquid_Water,0,2);

     swapbyte(&(*rcor).Spare,0,2);
     swapbyte(&(*rcor).Spare2,0,4);
   }

   off = 0;

   /* TIME TAG */
   memmove(&buf[off], &(*rcor).Tim_Moy_1, sizeof((*rcor).Tim_Moy_1));
   off += sizeof((*rcor).Tim_Moy_1);
   memmove(&buf[off], &(*rcor).Tim_Moy_2, sizeof((*rcor).Tim_Moy_2));
   off += sizeof((*rcor).Tim_Moy_2);
   memmove(&buf[off], &(*rcor).Tim_Moy_3, sizeof((*rcor).Tim_Moy_3));
   off += sizeof((*rcor).Tim_Moy_3);

   /* LOCATION AND SURFACE TYPE */
   memmove(&buf[off], &(*rcor).Lat_Tra, sizeof((*rcor).Lat_Tra));
   off += sizeof((*rcor).Lat_Tra);

   memmove(&buf[off], &(*rcor).Lon_Tra, sizeof((*rcor).Lon_Tra));
   off += sizeof((*rcor).Lon_Tra);


   memmove(&buf[off], &(*rcor).Alt_Surface_Type, sizeof((*rcor).Alt_Surface_Type));
   off += sizeof((*rcor).Alt_Surface_Type);

   memmove(&buf[off], &(*rcor).Rad_Surface_Type, sizeof((*rcor).Rad_Surface_Type));
   off += sizeof((*rcor).Rad_Surface_Type);

   memmove(&buf[off], &(*rcor).TMR_Bad, sizeof((*rcor).TMR_Bad));
   off += sizeof((*rcor).TMR_Bad);

   memmove(&buf[off], &(*rcor).Instr_State_TMR, sizeof((*rcor).Instr_State_TMR));
   off += sizeof((*rcor).Instr_State_TMR);

/* BRIGHTNESS TEMPERATURE */
   memmove(&buf[off], &(*rcor).Tb_18, sizeof((*rcor).Tb_18));
   off += sizeof((*rcor).Tb_18);
   memmove(&buf[off], &(*rcor).Tb_21, sizeof((*rcor).Tb_21));
   off += sizeof((*rcor).Tb_21);
   memmove(&buf[off], &(*rcor).Tb_37, sizeof((*rcor).Tb_37));
   off += sizeof((*rcor).Tb_37);

   /* ALTIMETER RANGE CORRECTIONS */
   memmove(&buf[off], &(*rcor).Wet_H_Rad, sizeof((*rcor).Wet_H_Rad));
   off += sizeof((*rcor).Wet_H_Rad);

 /* BACKSCATTER COEFFICIENT */
   memmove(&buf[off], &(*rcor).Atm_Att_Sig0_Corr_Ku, sizeof((*rcor).Atm_Att_Sig0_Corr_Ku));
   off += sizeof((*rcor).Atm_Att_Sig0_Corr_Ku);
   memmove(&buf[off], &(*rcor).Atm_Att_Sig0_Corr_C, sizeof((*rcor).Atm_Att_Sig0_Corr_C));
   off += sizeof((*rcor).Atm_Att_Sig0_Corr_C);

 /* ENVIRONMENTAL PARAMETERS */
   memmove(&buf[off], &(*rcor).Wind_Speed_Rad, sizeof((*rcor).Wind_Speed_Rad));
   off += sizeof((*rcor).Wind_Speed_Rad);

   memmove(&buf[off], &(*rcor).Rad_Water_Vapor, sizeof((*rcor).Rad_Water_Vapor));
   off += sizeof((*rcor).Rad_Water_Vapor);

   memmove(&buf[off], &(*rcor).Rad_Liquid_Water, sizeof((*rcor).Rad_Liquid_Water));
   off += sizeof((*rcor).Rad_Liquid_Water);

/* Spare*/
   memmove(&buf[off], &(*rcor).Spare, sizeof((*rcor).Spare));
   off += sizeof((*rcor).Spare);

/* Spare2*/
   memmove(&buf[off], &(*rcor).Spare2, sizeof((*rcor).Spare2));
   off += sizeof((*rcor).Spare2);

   fwrite(buf, sizeof(buf), 1, fin);


   return 0;
}



/**********************************************************************
* FUNCTION: Swap bytes
* Purpose:
* To perform data byte swap
* Input:
*  buf -- data buffer
*  start_bytes -- starting bytes in the buffer to be swapped
*  num_bytes   -- number of bytes after the start_bytes to be swapped
* Output:
*  buf -- swapped data buffer
*********************************************************************/
swapbyte(char buf[], int start_byte, int num_bytes){
   char            temp;
   if (num_bytes == 2) {
      temp = buf[start_byte];
      buf[start_byte] = buf[start_byte + 1];
      buf[start_byte + 1] = temp;
      return (0);
   }
   else if (num_bytes == 4) {
      temp = buf[start_byte];
      buf[start_byte] = buf[start_byte + 3];
      buf[start_byte + 3] = temp;
      temp = buf[start_byte + 1];
      buf[start_byte + 1] = buf[start_byte + 2];
      buf[start_byte + 2] = temp;
      return (0);
   }
   else {
      printf("swap_bytes: num_bytes not one of 2 or 4.\n");
      exit(1);
   }
}

/********************************************************************
* FUNCTION: threedig_num
* Purpose:
* To convert an integer cycle number into a character string
*
* Input:
*   icyc         - Integer cycle number
* Output:
*   cyc[4]       - The character string array
********************************************************************/

int threedig_num(char cyc[4], long icyc){
   long i1, i2, i3, ir;
   static char nc[10] = "0123456789";

   if ((icyc < 0) || (icyc > 999)) {
     printf("findcyc: Cycle number must lie between 0 and 999: icyc = %d\n",
	     icyc);
     exit(1);
   }

   i1 = icyc/100;
   ir = icyc - i1*100;
   i2 = ir/10;
   i3 = ir - i2*10;

   cyc[0] = nc[i1];
   cyc[1] = nc[i2];
   cyc[2] = nc[i3];
   cyc[3] = '\0';

   return 0;
}
