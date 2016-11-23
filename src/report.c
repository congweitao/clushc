/*
 * To create a status report
 *
 */

#include "common.h"
#include "check.h"

struct _check_item check_item;
struct _check_node check_node;
struct _check_node_mem check_node_mem;
struct _check_service check_service;

int output_report(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i=0, j=0;
   char* path_checklog=(char *)malloc(FILEPATH_MAX);
   char* path_checklogfile=(char *)malloc(FILEPATH_MAX);
   char* name_checklog=(char *)malloc(STRING_MAX);

   printf("------------------------------------------\033[34m Node Health Check Report \033[0m-------------------------------------------------\n");

   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* setup filename and filepath */
         path_checklog = getenv("CLUSHC_LOG");
         name_checklog = clushc_strcat(node_list[i],"-checks.txt\0");
         path_checklogfile = clushc_strcat(path_checklog, name_checklog);

         check_item.ht = get_row_num(path_checklogfile, "THREAD_PER_CORE");
         check_item.load_avg = get_row_num(path_checklogfile, "LOAD_AVG");
         check_item.cpu_used = get_row_num(path_checklogfile, "CPU_USED");
         check_item.mem_used_perc = get_row_num(path_checklogfile, "MEM_USED_PERC");
         check_item.ib_status = get_row_num(path_checklogfile,"IB_STATE");
	 check_item.ib_conn_mode = get_row_num(path_checklogfile,"CONNECTION_MODE");
	 check_item.stack = get_row_num(path_checklogfile,"STACK_SIZE");

         check_node.thread_per_core = get_special_line(path_checklogfile,check_item.ht);
         check_node.load_avg = get_special_line(path_checklogfile,check_item.load_avg);
         check_node.cpu_used = get_special_line(path_checklogfile,check_item.cpu_used);
         check_node_mem.mem_used_perc = get_special_line(path_checklogfile,check_item.mem_used_perc);
	 check_service.stacksize = get_special_line(path_checklogfile,check_item.stack);
	 check_node.ib_status = get_special_line(path_checklogfile,check_item.ib_status);
	 check_node.ib_connection_mode = get_special_line(path_checklogfile,check_item.ib_conn_mode);

         remove_space(check_node.thread_per_core);
         remove_space(check_node.load_avg);
         remove_space(check_node.cpu_used);
         remove_space(check_node_mem.mem_used_perc);
         remove_space(check_service.stacksize);
         remove_space(check_node.ib_status);
         remove_space(check_node.ib_connection_mode);

	 if(strcmp(check_node.thread_per_core,"1") == 0) status[0]=0; else status[0]=1;
	 if(strcmp(check_node.load_avg,"20") == 0) status[1]=0;else status[2]=0;
	 if(strcmp(check_node.cpu_used,"400") == 0) status[2]=0;else status[3]=0;
	 if(strcmp(check_node_mem.mem_used_perc,"90") == 0) status[3]=0;else status[4]=1;
	 if(strcmp(check_node.ib_status,"ACTIVE") == 0) status[4]=0;else status[5]=1;
	 if(strcmp(check_node.ib_connection_mode,"CONNECTED") == 0) status[5]=0;else status[6]=1;
	 if(strcmp(check_service.stacksize,"unlimited") == 0) status[6]=0;else status[7]=1;

         printf("[%s]  ->  HYPER-THREADING\tLOAD-AVG\tCPU-USED-RATIO\tMEMORY-USED-RATIO   IB-STAT\tIB-CN-MODE\tSTACK-SIZE\n",node_list[i]);
	 printf("\t\t");
	 for(j = 0; j < ITEM_NUM; j++)
	 {
	     if(j==4) printf("     ");
	     switch(status[j])
		{
			case 0: printf("\033[34mPASSED    \033[0m\t");break;
			case 1: printf("\033[31mNOT PASSWD\033[0m\t");break;
			default: printf("UNKOWN\t");break;
		}
	 }
 	 printf("\n");
         sleep(1);
      }
   }
   return 0;
}
