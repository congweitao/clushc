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

static int row_num = 0, row_num_mem = 0;
static int row_num_memory = 0, row_num_load = 0;
static int row_num_mem_used_perc = 0;

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

   printf("----\033[34m Cluster Health Checking System \033[0m----\n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* setup filename and filepath */
         path_checklog = getenv("CLUSHC_LOG");
         name_checklog = clushc_strcat(node_list[i],"-checks.txt\0");
         path_checklogfile = clushc_strcat(path_checklog, name_checklog);
         
         row_num = get_row_num(path_checklogfile, "THREAD_PER_CORE");
         row_num_load = get_row_num(path_checklogfile, "LOAD_AVG");
         row_num_mem = get_row_num(path_checklogfile, "MEMORY_SIZE");
         row_num_mem_used_perc = get_row_num(path_checklogfile, "MEM_USED_PERC");

         check_node.thread_per_core = get_special_line(path_checklogfile,row_num);
         check_node.cpu_model = get_special_line(path_checklogfile,++row_num);
         check_node.load_avg = get_special_line(path_checklogfile,row_num_load);
         check_node_mem.mem_size = get_special_line(path_checklogfile,row_num_mem);
         check_node_mem.mem_used_perc = get_special_line(path_checklogfile,row_num_mem_used_perc);
         remove_space(check_node.thread_per_core);
         remove_space(check_node.cpu_model);
         remove_space(check_node.load_avg);
         remove_space(check_node_mem.mem_size);
         remove_space(check_node_mem.mem_used_perc);
         
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
         printf("      ->  Total Memory--------[%s]\n",check_node_mem.mem_size);
         printf("      ->  Memory Used Ratio--------[%s]\n",check_node_mem.mem_used_perc);
         sleep(1);
      }
   }
   return 0;
}

