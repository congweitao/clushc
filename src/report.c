/*
 * To create a status report
 *
 */
#include "common.h"
#include "check.h"


int output_report(
        char* clushc_path,
	int   NodeNumber,
        char node_list[NODE_NUM_MAX][NODE_WIDTH]){
   //
   int i=0, j=0, item_j = 0;
   char load_avg_status[8]="normal";  // load average is defined as normal and  high
   char* cpus=NULL;

   /* item ann value */
   char* item_content[NODE_NUM_MAX][2];
   int i_list[NODE_NUM_MAX]; 

   printf("-------------------------------------------------- \
	    \033[34m Node Health Check Report \033[0m	      \
	   -------------------------------------------------- \n");
   printf(" HOSTNAME\t HYPER-THREADING\tLOAD-AVG\tIB_OPENSMD\t \
	    IB-STAT\t\tIB-CN-MODE\tSTACK-SIZE\tCPU-TEM\t\tDISK-USAGE\tMEMORY-BARS\n");

   for(i = 0; i< NodeNumber; i++){
      if(strlen(node_list[i]) != 0){
         /*  check hyper-threading cofiguration */ 
	 get_item_content(clushc_path,"THREAD_PER_CORE", item_content, node_list);
	 if(strcmp(item_content[i][1],"1") == 0) 		status[0]=0; else status[0]=1;
         /* load average is defined as normal and high */
	 get_item_content(clushc_path,"PROCESSORS", item_content, node_list);
	 cpus = item_content[i][1];
	 get_item_content(clushc_path,"LOAD_AVG", item_content, node_list);
         if((atof(item_content[i][1]) - atoi(cpus)) > 0) strcpy(load_avg_status,"high");
         else strcpy(load_avg_status,"normal");
	 if(strcmp(load_avg_status,"normal") == 0) 		status[1]=0; else status[1]=1;
	 get_item_content(clushc_path,"OPENSMD", item_content, node_list);
	 if(strcmp(item_content[i][1],"stopped") == 0) 		status[2]=0; else status[2]=1;
	 get_item_content(clushc_path,"IB_STATE", item_content, node_list);
	 if(strcmp(item_content[i][1],"ACTIVE") == 0) 		status[3]=0; else status[3]=1;
	 get_item_content(clushc_path,"CONNECTION_MODE", item_content, node_list);
	 if(strcmp(item_content[i][1],"connected") == 0) 	status[4]=0; else status[4]=1;
	 get_item_content(clushc_path,"STACK_SIZE", item_content, node_list);
	 if(strcmp(item_content[i][1],"unlimited") == 0) 	status[5]=0; else status[5]=1;
	 /* check cpu0 or cpu1 temperture, default critical is defined as higher than 90 */
         if(atoi(item_content[i][1]) < 90) 			status[6]=0; else status[6]=1;
	 get_item_content(clushc_path,"DISK_USAGE", item_content, node_list);
	 if(atoi(item_content[i][1]) < 90)			status[7]=0; else status[7]=1;

         /* check whether memory bar was down or not */
	 get_item_content(clushc_path,"USED_DIMMS", item_content, node_list);
         for(item_j = 0;item_j < NodeNumber;item_j++) i_list[item_j] = atoi(item_content[item_j][1]);
	 if(atoi(item_content[i][1]) == sort_merge(NodeNumber,i_list))  status[8]=0; else status[8]=1;

	 /* print descision */
         printf("  %-8s      ",node_list[i]);
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
