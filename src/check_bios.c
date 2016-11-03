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

static int flag_ibstat=1;
static int flag_ht=0;

struct _check_node check_node;
struct _check_node_mem check_node_mem;
struct _check_item check_item[NODE_NUM_MAX];


static int row_num = 0;
static int row_num_memory = 0, row_num_load = 0;

int check_memory()
{


   return 0;
}

int clushc_bios(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i=0;
   char* flag_ok="PASSED";
   char* flag_hyper_threading=(char *)malloc(8);
   char* path_checklog=(char *)malloc(FILEPATH_MAX);
   char* path_checklogfile=(char *)malloc(FILEPATH_MAX);
   char* name_checklog=(char *)malloc(STRING_MAX);

   printf("---- Cluster Health Checking System ----\n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* setup filename and filepath */
         path_checklog = getenv("CLUSHC_LOG");
         name_checklog = clushc_strcat(node_list[i],"-checks.txt\0");
         path_checklogfile = clushc_strcat(path_checklog, name_checklog);
         
         row_num = get_row_num(path_checklogfile, "THREAD_PER_CORE");
         row_num_load = get_row_num(path_checklogfile, "LOAD_AVG");

         check_node.thread_per_core = get_special_line(path_checklogfile,row_num);
         check_node.cpu_model = get_special_line(path_checklogfile,++row_num);
         check_node.load_avg = get_special_line(path_checklogfile,row_num_load);
         remove_space(check_node.thread_per_core);
         remove_space(check_node.cpu_model);
         remove_space(check_node.load_avg);
         
         if(atoi(check_node.thread_per_core) == 1) {
             flag_hyper_threading = "OFF";
             flag_ok = "PASSED";
          }
         else{
             flag_hyper_threading = "ON";
             flag_ok = "\033[5;31mNOT PASSED\033[0m";
         }
         printf("[%s]  ->  Hyper-Threading--[%s]\t[%s]\n",node_list[i],flag_hyper_threading,flag_ok);
         printf("      ->  Load Average--------[%s]\n",check_node.load_avg);
         sleep(1);
      }
   }
   return 0;
}

