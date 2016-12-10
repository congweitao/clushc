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

   printf("--------\033[34m Cluster Health Checking Infiniband \033[0m--------\n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         get_item_content(clushc_path,"NAME_UP_IB", item_content, node_list); 
         printf("[%-4s]  -> Infiniband Interface ---- [%-8s]\n",node_list[i], item_content[i][1]);
         get_item_content(clushc_path,"IB_STATE", item_content, node_list); 
         if(strcmp(item_content[i][1],"ACTIVE") == 0)
            printf("         -> Infiniband State ------- [%-8s] ---- [PASSWD]\n",item_content[i][1]);
         else
            printf("         -> Infiniband State ------- [%-8s] ---- \033[31m[NOT PASSSWD]\033[0m\n",item_content[i][1]);
         get_item_content(clushc_path,"IB_RATE", item_content, node_list); 
         printf("         -> Infiniband Rate -------- [%-8s]\n", item_content[i][1]);
         get_item_content(clushc_path,"OPENSMD", item_content, node_list); 
         if(strcmp(item_content[i][1],"stopped") == 0)
            printf("         -> Service opensmd --------- [%-8s]\n",item_content[i][1]);
	 else
            printf("         -> Service  opensmd -------- \033[33m[%-8s]\033[0m\n",item_content[i][1]);
         get_item_content(clushc_path,"CONNECTION_MODE", item_content, node_list); 
	 if(strcmp(item_content[i][1],"connected") == 0)
            printf("         -> IB Connect Mode  ------- [%-8s]----[PASSWD]\n", item_content[i][1]);
	 else
            printf("         -> IB Connect Mode  ------- [%-8s]----\033[31m[NOT PASSWD]\033[0m\n",item_content[i][1]);
         sleep(1);
      }
   }
   return 0;
}

