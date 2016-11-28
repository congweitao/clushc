/*
 * Functions to check Infiniband Network, Storage, Filesystem, etc.
 *
 */

#include "common.h"
#include "check.h"

struct _check_node check_node;

int clushc_network(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i=0;
   static int row_num = 0;
   static int row_num_opensmd = 0;
   char* flag_ok="PASSED";
   char* flag_hyper_threading=(char *)malloc(8);
   char* path_checklog=(char *)malloc(FILEPATH_MAX);
   char* path_checklogfile=(char *)malloc(FILEPATH_MAX);
   char* name_checklog=(char *)malloc(STRING_MAX);

   printf("----\033[34m Cluster Health Checking Infiniband \033[0m----\n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* preparing the nodes checking log filename, eq., filename and filepath */
         path_checklog = getenv("CLUSHC_LOG");
         name_checklog = clushc_strcat(node_list[i],"-checks.txt\0");
         path_checklogfile = clushc_strcat(path_checklog, name_checklog);
        
         row_num = get_row_num(path_checklogfile, "NAME_UP_IB");         
         row_num_opensmd = get_row_num(path_checklogfile, "OPENSMD");         
 
         check_node.ib_name = get_special_line(path_checklogfile, row_num);
         check_node.ib_status = get_special_line(path_checklogfile, ++row_num);
         check_node.ib_rate = get_special_line(path_checklogfile, ++row_num);
         check_node.ib_opensmd = get_special_line(path_checklogfile, row_num_opensmd);
         check_node.ib_connection_mode = get_special_line(path_checklogfile, ++row_num_opensmd);
         remove_space(check_node.ib_status);
         remove_space(check_node.ib_name);
         remove_space(check_node.ib_rate);
         remove_space(check_node.ib_opensmd);
         remove_space(check_node.ib_connection_mode);
         
         printf("[%s]    -> Device Name----------- [%-8s]\n",node_list[i], check_node.ib_name);
         if(strcmp(check_node.ib_status,"ACTIVE") == 0)
            printf("\t   -> IB State ------------- [%-8s] ---- [PASSWD]\n",check_node.ib_status);
         else
            printf("\t   -> IB State ------------- [%-8s] ---- \033[31m[NOT PASSSWD]\033[0m\n",check_node.ib_status);
         printf("\t   -> IB Rate -------------- [%-8s]\n", check_node.ib_rate);
         if(strcmp(check_node.ib_opensmd,"stopped") == 0)
            printf("\t   -> IB OpenSM ------------ [%-8s]\n",check_node.ib_opensmd);
	 else
            printf("\t   -> IB OpenSM ------------ \033[33m[%-8s]\033[0m\n",check_node.ib_opensmd);
	 if(strcmp(check_node.ib_connection_mode,"connected") == 0)
            printf("\t   -> IB Connection Mode --- [%-8s]----[PASSWD]\n",check_node.ib_connection_mode);
	 else
            printf("\t   -> IB Connection Mode --- [%-8s]----\033[31m[NOT PASSWD]\033[0m\n",check_node.ib_connection_mode);
         sleep(1);
      }
   }
   return 0;
}

