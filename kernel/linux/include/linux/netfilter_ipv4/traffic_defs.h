/*
 ** <:copyright-Tecom
 **
 **  Copyright (c) 2005 Tecom Corporation
 **  All Rights Reserved
 **  No portions of this material may be reproduced in any form without the
 **  written permission of:
 **   Tecom Corporation
 **  WH041 Echo Li
 **  WuHan, Hubei 
 **  All information contained in this document is Tecom Corporation
 **  company private, proprietary, and trade secret.
 **
 **  :>
 ***/
#include <linux/if_ether.h>
#include <linux/list.h>

typedef struct __traffic_config{

	//use the standard list 
	struct list_head list;

        long int ip_address;
        char h_dest[ETH_ALEN];

        int ip_traffic_MAX;     //the limit of payload.
                                //eg,if ip_traffic_MAX is 99
                                // means the quota is 99 MByte
        int autoBlock;
	int ip_traffic_local;	//to counter the byte when less than 1M

}traffic_config_t,*ptraffic_config_t;

