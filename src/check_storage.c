/*
 * Functions to check Infiniband Network, Storage, Filesystem, etc.
 *
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "common.h"
#include "check.h"

struct _check_node check_node;
struct _check_item check_item[NODE_NUM_MAX];

int clushc_storage(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i = 0;
   static int row_num  = 0;
   char* flag_hyper_threading=(char *)malloc(8);
   char* path_checklog=(char *)malloc(FILEPATH_MAX);
   char* path_checklogfile=(char *)malloc(FILEPATH_MAX);
   char* name_checklog=(char *)malloc(STRING_MAX);

   printf("----\033[34m Cluster Health Checking NFS \033[0m----\n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* preparing the nodes checking log filename, eq., filename and filepath */
         path_checklog = getenv("CLUSHC_LOG");
         name_checklog = clushc_strcat(node_list[i],"-checks.txt\0");
         path_checklogfile = clushc_strcat(path_checklog, name_checklog);
        
         row_num = get_row_num(path_checklogfile, "NFS_MOUNTS"); 

         check_node.nfs_mounts = get_special_line(path_checklogfile, row_num);
         check_node.nfs_fsname = get_special_line(path_checklogfile,++row_num);
         check_node.nfs_mntdir = get_special_line(path_checklogfile,++row_num);
         remove_space(check_node.nfs_mounts);
         remove_space(check_node.nfs_fsname);
         remove_space(check_node.nfs_mntdir);
         
         strcpy(check_item[i].hostname, node_list[i]);
         strcpy(check_item[i].item_content, check_node.nfs_mounts);

         printf("[%s]->MOUNT_COUNTS\tSERVER_FS\tMOUNT_POINT\t\n",node_list[i]);
         printf("\t    [%2d]\t[%s]\t[%s]\n",atoi(check_node.nfs_mounts),
               check_node.nfs_fsname,check_node.nfs_mntdir);
         sleep(1);
      }
   }
   return 0;
}

