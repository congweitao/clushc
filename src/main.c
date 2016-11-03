/*
 * Script: Node Health Script 
 * Created By: weitao cong (congwt@sugon.com) www.sugon.com
 * Created On: 29th August 2016
 * Detail: To Check Single Node Health. 
 * Checks: loadavg, memory, cpu, ethernet, infiniband, cpu test, nfs mounts, nis, mcelog
 * Functions: You can load/unload any function you need to run or not to run.
 * License: GPL 
 *
 */

#include <unistd.h>
#include <getopt.h>
#include "function.h"
#include "check.h"


   /* Parse Input Parameters */
char* l_opt_arg;
char* const short_options = "hilsbfonv:";
struct option long_options[] = {
    { "help",           0, NULL, 'h' },
    { "collect-info",   0, NULL, 'i' },
    { "hostlist",       1, NULL, 'l' },
    { "check-service",  0, NULL, 's' },
    { "check-bios",     0, NULL, 'b' },
    { "check-firmware", 0, NULL, 'f' },
    { "check-storage",  0, NULL, 'o' },
    { "check-network",  0, NULL, 'n' },
    { "version",        0, NULL, 'v' },
    {         0,        0,    0,  0  },
};

int main(int argc, char **argv)
{
   int opt;
   FILE* fp_conf;

  char node_list[NODE_NUM_MAX][NODE_WIDTH];
  char* check_system=(char *)malloc(FILEPATH_MAX);
  char* clushc_scpfile=(char *)malloc(FILEPATH_MAX);
  char* clushc_syncdo=(char *)malloc(FILEPATH_MAX);
  char* clushc_syncfile=(char *)malloc(FILEPATH_MAX);
  char* clushc_log=(char *)malloc(FILEPATH_MAX);
  char* clushc_path=(char *)malloc(FILEPATH_MAX);
  char* clushc_nodelist=(char *)malloc(FILEPATH_MAX);
  char* clushc_create_nodelist=(char *)malloc(FILEPATH_MAX);

   /* Setup Clushc environment variables */ 
   clushc_path = getenv("CLUSHC_PATH");
   clushc_nodelist = getenv("CLUSHC_NODELIST");
   clushc_scpfile = getenv("CLUSHC_SCP");
   clushc_syncdo =  getenv("CLUSHC_SYNCDO");
   clushc_syncfile = getenv("CLUSHC_SYNCFILE");
   check_system = getenv("CLUSHC_CHECK_SYSTEM");
   clushc_log = getenv("CLUSHC_LOG");
   clushc_create_nodelist = getenv("CLUSHC_CREATE_NODELIST");
 
   /* initializing memory space, create nodelist */
   memset(node_list,'\0',sizeof(node_list));
   get_nodelist(clushc_nodelist, node_list);
   
   /* Add your code in this part. */
   while((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
   {
      switch(opt)
      {
         case 'h':
               usage();
               break;
         case 'i':
               system(clushc_scpfile);
               system(clushc_syncdo);
               system(clushc_syncfile);
               system(check_system);
               break;
         case 'l':
                l_opt_arg = optarg;
                printf("%s\n",l_opt_arg);
                break;
         case 's':               
               clushc_service(clushc_path, node_list); 
               break;
         case 'n':               
               clushc_network(clushc_path, node_list);      
               break;
         case 'b':               
               clushc_bios(clushc_path, node_list); 
               break;
         case 'f':               
               clushc_firmware(clushc_path, node_list); 
               break;
         case 'o':               
               clushc_storage(clushc_path, node_list); 
               break;
         case 'v':
              printf("Clushc Version 1.0.0 uptdate 11/2/2016\n");
              break;
         default:
              usage();
      }
   }  

   return 0;
}
