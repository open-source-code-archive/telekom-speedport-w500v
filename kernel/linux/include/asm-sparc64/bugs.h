/*  $Id: bugs.h,v 1.1.1.1 2006/01/25 03:56:48 root Exp $
 *  include/asm-sparc64/bugs.h:  Sparc probes for various bugs.
 *
 *  Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#include <linux/config.h>

extern unsigned long loops_per_jiffy;

static void check_bugs(void)
{
#ifndef CONFIG_SMP
	cpu_data(0).udelay_val = loops_per_jiffy;
#endif
}
