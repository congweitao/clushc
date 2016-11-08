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
struct _check_node_disk check_node_disk;

int clushc_storage(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i = 0;
   static int row_num_nfs  = 0;
   static int row_num_disk  = 0;
   char* flag_hyper_threading=(char *)malloc(8);
   char* path_checklog=(char *)malloc(FILEPATH_MAX);
   char* path_checklogfile=(char *)malloc(FILEPATH_MAX);
   char* name_checklog=(char *)malloc(STRING_MAX);

   printf("----\033[34m Cluster Health Checking Storage \033[0m----\n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* preparing the nodes checking log filename, eq., filename and filepath */
         path_checklog = getenv("CLUSHC_LOG");
         name_checklog = clushc_strcat(node_list[i],"-checks.txt\0");
         path_checklogfile = clushc_strcat(path_checklog, name_checklog);
        
         row_num_nfs = get_row_num(path_checklogfile, "NFS_MOUNTS"); 
         row_num_disk = get_row_num(path_checklogfile, "DISK_NUM"); 

         check_node.nfs_mounts = get_special_line(path_checklogfile, row_num_nfs);
         check_node.nfs_fsname = get_special_line(path_checklogfile,++row_num_nfs);
         check_node.nfs_mntdir = get_special_line(path_checklogfile,++row_num_nfs);
         check_node_disk.disk_num = get_special_line(path_checklogfile,row_num_disk);
         check_node_disk.disk_vendor = get_special_line(path_checklogfile,++row_num_disk);
         check_node_disk.disk_size = get_special_line(path_checklogfile,++row_num_disk);
         check_node_disk.disk_usage = get_special_line(path_checklogfile,++row_num_disk);
         check_node_disk.disk_rate = get_special_line(path_checklogfile,++row_num_disk);
         check_node_disk.disk_protocol = get_special_line(path_checklogfile,++row_num_disk);
         remove_space(check_node.nfs_mounts);
         remove_space(check_node.nfs_fsname);
         remove_space(check_node.nfs_mntdir);
         remove_space(check_node_disk.disk_num);
         remove_space(check_node_disk.disk_vendor);
         remove_space(check_node_disk.disk_size);
         remove_space(check_node_disk.disk_usage);
         remove_space(check_node_disk.disk_rate);
         remove_space(check_node_disk.disk_protocol);
         

         printf("[%s]->MOUNT_COUNTS\tSERVER_FS\tMOUNT_POINT\t\n",node_list[i]);
         printf("        \033[32m %4d\t%4s\t%4s\033[0m\n",atoi(check_node.nfs_mounts),
               check_node.nfs_fsname,check_node.nfs_mntdir);
         printf("\t->DISK NUMBER\tVENDOR\tSIZE\tUSAGE\tROTATION RATE\tPROTOCOL\n");
         printf("    \033[32m %4s\t%4s\t%4s\t%4s\t%4s\t%4s\033[0m\n\n",
                check_node_disk.disk_num,check_node_disk.disk_vendor,check_node_disk.disk_size,
		check_node_disk.disk_usage,check_node_disk.disk_rate,check_node_disk.disk_protocol);
         sleep(1);
      }
   }
   return 0;
}

