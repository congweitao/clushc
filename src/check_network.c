/*
 * Functions to check Infiniband Network, Storage, Filesystem, etc.
 *
 */

#include "common.h"
#include "check.h"


int clushc_network(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH])
{
   int i=0;
   char* item_content[NODE_NUM_MAX][2];

   printf("----------------\033[34m Cluster Health Checking Infiniband \033[0m----------------\n");
   printf(" HOSTNAME |  IB INTERFACE |  IB STATE |  IB RATE |  OPENSMD STATE | CONN MODE | STATUS \n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         get_item_content(clushc_path,"IB_INTERFACE", item_content, node_list); 
         printf("%-8s     %-12s",node_list[i], item_content[i][1]);

         get_item_content(clushc_path,"IB_STATE", item_content, node_list); 
         if(strcmp(item_content[i][1],"ACTIVE") == 0)
            printf("      %-8s",item_content[i][1]);
         else
            printf("      \033[31m%-8s\033[0m",item_content[i][1]);

         get_item_content(clushc_path,"IB_RATE", item_content, node_list); 
         printf("     %-8s", item_content[i][1]);

         get_item_content(clushc_path,"OPENSMD", item_content, node_list); 
         if(strcmp(item_content[i][1],"stopped") == 0)
            printf("    %-8s",item_content[i][1]);
	 else
            printf("    \033[33m%-8s\033[0m",item_content[i][1]);

         get_item_content(clushc_path,"CONNECTION_MODE", item_content, node_list); 
	 if(strcmp(item_content[i][1],"connected") == 0)
            printf("      %-8s\n", item_content[i][1]);
	 else
            printf("      \033[31m%-8s\033[0m\n",item_content[i][1]);
         sleep(1);
      }
   }
   return 0;
}

