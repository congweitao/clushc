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
 
   /* get the checked-node item and the value */
   get_item_content(clushc_path,"THREAD_PER_CORE", item_content, node_list);

   /* make a decision and print the results */
   printf("----\033[34m Cluster Health Checking System \033[0m----\n");
   for(i = 0; i< NODE_NUM_MAX; i++){
     if(strlen(node_list[i]) != 0){   
        if(atoi(item_content[i][1]) == 1) {
               printf("[%-8s]     ->  Hyper-Threading[%s]--------[OFF]----[PASSWD]\n",item_content[i][0],item_content[i][1]);
            }
           else{
               printf("[%-8s]     ->  Hyper-Threading[%s]--------[ON ]----\033[31m[NOT PASSWD]\033[0m\n",item_content[i][0],item_content[i][1]);
           }
           sleep(1);
      }
   }
   return 0;
}

