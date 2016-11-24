/*
 * To create a status report
 *
 */
#include "common.h"
#include "check.h"

struct _check_item check_item;
struct _check_node check_node;
struct _check_node_mem check_node_mem;
struct _check_node_disk check_node_disk;
struct _check_service check_service;

int output_report(
        char* clushc_path,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i=0, j=0;
   char* path_checklog=(char *)malloc(FILEPATH_MAX);
   char* path_checklogfile=(char *)malloc(FILEPATH_MAX);
   char* name_checklog=(char *)malloc(STRING_MAX);
   char load_avg_status[8]="normal";  // load average is defined as normal and  high

   printf("-------------------------------------------------- \
\033[34m Node Health Check Report \033[0m---------------------------------------------------------\n");
   printf("             HYPER-THREADING\tLOAD-AVG\tIB_OPENSMD\tIB-STAT\t\tIB-CN-MODE\tSTACK-SIZE\tCPU-TEM\t\tDISK-USAGE\tMEMORY-DIMMS\n");
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* setup filename and filepath */
         path_checklog = getenv("CLUSHC_LOG");
         name_checklog = clushc_strcat(node_list[i],"-checks.txt\0");
         path_checklogfile = clushc_strcat(path_checklog, name_checklog);

         check_item.ht = get_row_num(path_checklogfile, "THREAD_PER_CORE");
         check_item.load_avg = get_row_num(path_checklogfile, "LOAD_AVG");
         check_item.ib_status = get_row_num(path_checklogfile,"IB_STATE");
         check_item.ib_opensmd = get_row_num(path_checklogfile,"OPENSMD");
	 check_item.ib_conn_mode = get_row_num(path_checklogfile,"CONNECTION_MODE");
	 check_item.stack = get_row_num(path_checklogfile,"STACK_SIZE");
	 check_item.cpu_temp = get_row_num(path_checklogfile,"CPU0_TEMP");
	 if(check_item.cpu_temp == -1 )
	    check_item.cpu_temp = get_row_num(path_checklogfile,"CPU1_TEMP");
	 check_item.disk_usage = get_row_num(path_checklogfile,"DISK_USAGE");
	 check_item.mem_dimms = get_row_num(path_checklogfile,"USED_DIMMS");

         check_node.thread_per_core = get_special_line(path_checklogfile,check_item.ht);
         check_node.load_avg = get_special_line(path_checklogfile,check_item.load_avg);
	 check_service.stacksize = get_special_line(path_checklogfile,check_item.stack);
	 check_node.ib_status = get_special_line(path_checklogfile,check_item.ib_status);
	 check_node.ib_opensmd = get_special_line(path_checklogfile,check_item.ib_opensmd);
	 check_node.ib_connection_mode = get_special_line(path_checklogfile,check_item.ib_conn_mode);
	 check_node.cpu_temp = get_special_line(path_checklogfile,check_item.cpu_temp);
	 check_node_disk.disk_usage = get_special_line(path_checklogfile,check_item.disk_usage);
	 check_node_mem.mem_dimms_used = get_special_line(path_checklogfile,check_item.mem_dimms);

         remove_space(check_node.thread_per_core);
         remove_space(check_node.load_avg);
         remove_space(check_node.ib_opensmd);
         remove_space(check_service.stacksize);
         remove_space(check_node.ib_status);
         remove_space(check_node.ib_connection_mode);
         remove_space(check_node.cpu_temp);
         remove_space(check_node_disk.disk_usage);
         remove_space(check_node_mem.mem_dimms_used);

         /* load average is defined as normal and high */
	 check_item.cpu = get_row_num(path_checklogfile,"PROCESSORS");
         check_node.processors = get_special_line(path_checklogfile,check_item.cpu);
	 remove_space(check_node.processors);
         if((atof(check_node.load_avg) - atoi(check_node.processors)) > 0) strcpy(load_avg_status,"high");
	 else strcpy(load_avg_status,"normal");
         
	 if(strcmp(check_node.thread_per_core,"1") == 0) 		status[0]=0; else status[0]=1;
	 if(strcmp(load_avg_status,"normal") == 0) 			status[1]=0; else status[1]=1;
	 if(strcmp(check_node.ib_opensmd,"stopped") == 0) 		status[2]=0; else status[2]=1;
	 if(strcmp(check_node.ib_status,"ACTIVE") == 0) 		status[3]=0; else status[3]=1;
	 if(strcmp(check_node.ib_connection_mode,"connected") == 0) 	status[4]=0; else status[4]=1;
	 if(strcmp(check_service.stacksize,"unlimited") == 0) 		status[5]=0; else status[5]=1;
         if(atoi(check_node.cpu_temp) < 90) 				status[6]=0; else status[6]=1;
	 if(atoi(check_node_disk.disk_usage) < 90)			status[7]=0; else status[7]=1;
	 if(atoi(check_node_mem.mem_dimms_used) == 4)			status[8]=0; else status[8]=1;

         printf("[%-6s]  ->",node_list[i]);
	 printf("\t");
	 for(j = 0; j < ITEM_NUM; j++)
	 {
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
