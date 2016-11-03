/*
 * Functions to check Infiniband Network, Storage, Filesystem, etc.
 *
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "function.h"
#include "check.h"

struct _check_node check_node;
struct _check_node_fw check_node_fw;

static int row_num_ib = 0, row_num_bios = 0, row_num_bmc = 0;


int clushc_firmware(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i=0;
   char* flag_ok="OK";
   char* flag_hyper_threading=(char *)malloc(8);
   char* path_checklog=(char *)malloc(FILEPATH_MAX);
   char* path_checklogfile=(char *)malloc(FILEPATH_MAX);
   char* name_checklog=(char *)malloc(STRING_MAX);

   printf("---- Cluster Health Checking FirmWare ----\n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* preparing the nodes checking log filename, eq., filename and filepath */
         path_checklog = getenv("CLUSHC_LOG");
         name_checklog = clushc_strcat(node_list[i],"-checks.txt\0");
         path_checklogfile = clushc_strcat(path_checklog, name_checklog);
          
         row_num_ib = get_row_num(path_checklogfile, "IB_FW");;
         row_num_bios = get_row_num(path_checklogfile, "BIOS_FW");;
         row_num_bmc = get_row_num(path_checklogfile, "BMC_FW");;

         check_node_fw.ib = get_special_line(path_checklogfile,row_num_ib);
         check_node_fw.bios = get_special_line(path_checklogfile,row_num_bios);
         check_node_fw.bmc = get_special_line(path_checklogfile,row_num_bmc);
         remove_space(check_node_fw.ib);
         remove_space(check_node_fw.bios);
         remove_space(check_node_fw.bmc);
         
         printf("[%s]->The FW of IB is : %s\n",node_list[i], check_node_fw.ib);
         printf("\t   The FW of BIOS is : %s\n",check_node_fw.bios);
         printf("\t   The FW of BMC is : %s\n",check_node_fw.bmc);
         sleep(1);
      }
   }
   return 0;
}

