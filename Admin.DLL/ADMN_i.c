/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Oct 01 20:57:02 2025
 */
/* Compiler settings for ADMN.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IADMNObj = {0x51FA7D21,0x82F3,0x11D2,{0xA9,0xBC,0x44,0x45,0x53,0x54,0x00,0x00}};


const IID LIBID_ADMNLib = {0x51FA7D14,0x82F3,0x11D2,{0xA9,0xBC,0x44,0x45,0x53,0x54,0x00,0x00}};


const CLSID CLSID_ADMNObj = {0xF4E06E56,0x62AB,0x4732,{0xAF,0x44,0x9E,0x24,0xCD,0x9F,0x0C,0x66}};


#ifdef __cplusplus
}
#endif

