/*
 * Functions to check Infiniband Network, Storage, Filesystem, etc.
 *
 */

#include "common.h"
#include "check.h"

int clushc_firmware(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH])
{
   int i=0;
   char* item_content[NODE_NUM_MAX][2];

   printf("------------------\033[34m Cluster Health Checking Firmware \033[0m------------------\n");
   printf(" HOSTNAME | IB FIRMWARE |BIOS FIRMWARE | BMC FIRMWARE | STATUS  \n");

   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
	 /* infiniband firmware */
	 get_item_content(clushc_path,"IB_FW", item_content, node_list);
         printf("%-8s    %-16s",node_list[i],item_content[i][1]);
	 /* bios firmware */
	 get_item_content(clushc_path,"BIOS_FW", item_content, node_list);
         printf("  %-12s",item_content[i][1]);
	 /* bios firmware */
	 get_item_content(clushc_path,"BMC_FW", item_content, node_list);
         printf("  %-12s\n",item_content[i][1]);
         sleep(1);
      }
   }
   return 0;
}

