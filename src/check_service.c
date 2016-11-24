/*
 * This Part will check services of SElinux, iptables, firwalld, 
 * ntpd, gridview_platform, pbs related services, etc.
 */

#include "common.h"
#include "check.h"

static int flag_ibstat=1;
static int flag_ht=0;

struct _check_service check_service;

static int row_num = 0;
static int row_num_selinux = 0, row_num_stacksize = 0;

int clushc_service(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i=0;
   char* flag_ok="PASSED";
   char* flag_hyper_threading=(char *)malloc(8);
   char* path_checklog=(char *)malloc(FILEPATH_MAX);
   char* path_checklogfile=(char *)malloc(FILEPATH_MAX);
   char* name_checklog=(char *)malloc(STRING_MAX);

   printf("----\033[34m Cluster Health Checking Services \033[0m----\n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* preparing the nodes checking log filename, eq., filename and filepath */
         path_checklog = getenv("CLUSHC_LOG");
         name_checklog = clushc_strcat(node_list[i],"-checks.txt\0");
         path_checklogfile = clushc_strcat(path_checklog, name_checklog);
         
         row_num = get_row_num(path_checklogfile, "OOM");
         row_num_selinux = get_row_num(path_checklogfile, "SELINUX");
         row_num_stacksize = get_row_num(path_checklogfile, "STACK_SIZE");

         check_service.oom = get_special_line(path_checklogfile,row_num);
         check_service.stacksize = get_special_line(path_checklogfile,row_num_stacksize);
         check_service.selinux = get_special_line(path_checklogfile,row_num_selinux);
         remove_space(check_service.oom);
         remove_space(check_service.stacksize);
         remove_space(check_service.selinux);
        
         if(atoi(check_service.oom)==2) flag_ok="OK";
         else  flag_ok="\033[5;31m NOT OK\033[0m";
 
         printf("[%s]  ->  Services of OOM is: --[%s]\n",node_list[i],flag_ok);
         printf("          Stack Size is: --------[%s]\n",check_service.stacksize);
         printf("          SElinux is: --------[%s]\n",check_service.selinux);
         sleep(1);
       }
   }
   return 0;
}

