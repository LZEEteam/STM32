#ifndef __USMART_STR_H
#define __USMART_STR_H	 
#include "sys.h"

  
u8 usmart_get_parmpos(u8 num);
u8 usmart_strcmp(u8*str1,u8 *str2);
u32 usmart_pow(u8 m,u8 n);
u8 usmart_str2num(u8*str,u32 *res);
u8 usmart_get_cmdname(u8*str,u8*cmdname,u8 *nlen,u8 maxlen);
u8 usmart_get_fname(u8*str,u8*fname,u8 *pnum,u8 *rval);
u8 usmart_get_aparm(u8 *str,u8 *fparm,u8 *ptype);
u8 usmart_get_fparam(u8*str,u8 *parn);
#endif











