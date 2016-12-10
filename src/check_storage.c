/*
 * Functions to check Infiniband Network, Storage, Filesystem, etc.
 *
 */

#include "common.h"
#include "check.h"

char* item_content[NODE_NUM_MAX][2];

int clushc_storage(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i = 0;

   printf("------------\033[34m Cluster Health Checking Storage \033[0m------------\n");
   printf(" HOSTNAME |   SHARE FS    |   MOUNT POINT   |  DISKE COUNTS |  DISK USAGE(%) | DISK RATE | DISK PROTOCOL \n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* preparing the nodes checking log filename, eq., filename and filepath */
         get_item_content(clushc_path,"NFS_FSNAME", item_content, node_list);
         printf("%-8s    %-12s",node_list[i],item_content[i][1]);

         get_item_content(clushc_path,"NFS_DIR", item_content, node_list);
         printf("    %-12s",item_content[i][1]);

         get_item_content(clushc_path,"DISK_NUM", item_content, node_list);
         printf("        %-8s",item_content[i][1]);

         get_item_content(clushc_path,"DISK_USAGE", item_content, node_list);
         printf("        %-8s\n",item_content[i][1]);

         sleep(1);
      }
   }
   return 0;
}

