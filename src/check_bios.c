/*
 * Functions to check Infiniband Network, Storage, Filesystem, etc.
 *
 */
#include "common.h"
#include "check.h"

int clushc_bios(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH])
{
   int i = 0;
   char* item_content[NODE_NUM_MAX][2];
 
   /* make a decision and print the results */
   printf("----------------------------------\
\033[34m Cluster Health Checking System \033[0m\
----------------------------------\n");
   printf(" HOSTNAME | HYPER THREADING | TOTAL MEM BARS | \
LOAD AVG | CPU USAGE(%) | MEM SIZE(GB) | MEM USAGE(%) | STATUS  \n");
   for(i = 0; i< NODE_NUM_MAX; i++){
     if(strlen(node_list[i]) != 0){   
        /* get the checked-node item and the value */
        get_item_content(clushc_path,"THREAD_PER_CORE", item_content, node_list);
        if(atoi(item_content[i][1]) == 1) {
               printf("%-8s       OFF         ",item_content[i][0]);
            }
        else{
               printf("%-8s        \033[31mON\033[0m         ",item_content[i][0]);
           }
        /* check total memory slots */
        get_item_content(clushc_path,"TOTAL_DIMMS", item_content, node_list);
        printf("         %-8s",item_content[i][1]);
	/* check cpu load average */
        get_item_content(clushc_path,"LOAD_AVG", item_content, node_list);
        printf("     %-8s",item_content[i][1]);
        /* check cpu used ratio (%) */
        get_item_content(clushc_path,"CPU_USED", item_content, node_list);
        printf("    %-8s",item_content[i][1]);

        get_item_content(clushc_path,"MEMORY_SIZE", item_content, node_list);
        printf("    %-8s",item_content[i][1]);

        get_item_content(clushc_path,"MEM_USED_PERC", item_content, node_list);
        printf("          %-8s\n",item_content[i][1]);

        sleep(1);
      }
   }
   return 0;
}

