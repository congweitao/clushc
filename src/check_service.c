/*
 * This Part will check services of SElinux, iptables, firwalld, 
 * ntpd, gridview_platform, pbs related services, etc.
 */

#include "common.h"
#include "check.h"

char* item_content[NODE_NUM_MAX][2];

int clushc_service(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i=0;

   printf("----------------\033[34m Cluster Health Checking Services \033[0m----------------\n");
   printf(" HOSTNAME   |   OOM     |       STACK-SIZE   |    SELINUX    |   STATUS  \n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* preparing the nodes checking log filename, eq., filename and filepath */
         get_item_content(clushc_path,"OOM", item_content, node_list); 
         if(atoi(item_content[i][1])==2) 
             printf("%-8s        %-8s",node_list[i],item_content[i][1]);
         else  
             printf("%-8s        %-8s",node_list[i],item_content[i][1]);

         get_item_content(clushc_path,"STACK_SIZE", item_content, node_list); 
         if(strcmp(item_content[i][1],"unlimited") == 0) 
             printf("        %-8s",item_content[i][1]);
	 else
             printf("        %-8s",item_content[i][1]);

         get_item_content(clushc_path,"SELINUX", item_content, node_list); 
         if(strcmp(item_content[i][1],"disabled") == 0)
             printf("        %-8s\n",item_content[i][1]);
	 else
             printf("        %-8s\n",item_content[i][1]);

         sleep(1);
       }
   }
   return 0;
}

