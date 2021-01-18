#ifndef __LINUX_BRIDGE_EBT_FTOS_T_H
#define __LINUX_BRIDGE_EBT_FTOS_T_H

struct ebt_ftos_t_info
{
	unsigned char ftos;
	// EBT_ACCEPT, EBT_DROP or EBT_CONTINUE or EBT_RETURN
	int target;
};
#define EBT_FTOS_TARGET "ftos"

#endif
