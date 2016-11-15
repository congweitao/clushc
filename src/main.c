/*
 * Script: Node Health Script 
 * Created By: weitao cong (congwt@sugon.com) www.sugon.com
 * Created On: 29th August 2016
 * Detail: To Check Single Node Health. 
 * Checks: loadavg, memory, cpu, ethernet, infiniband, cpu test, nfs mounts, nis, mcelog
 * Functions: You can load/unload any common you need to run or not to run.
 * License: GPL 
 *
 */

#include <unistd.h>
#include <getopt.h>
#include "common.h"
#include "check.h"

/* Parse Input Parameters */
char* l_opt_arg;
char* const short_options = "hilsbfoncv";
struct option long_options[] = {
    { "help",           0, NULL, 'h' },
    { "collect-info",   0, NULL, 'i' },
    { "hostlist",       1, NULL, 'l' },
    { "check-service",  0, NULL, 's' },
    { "check-bios",     0, NULL, 'b' },
    { "check-firmware", 0, NULL, 'f' },
    { "check-storage",  0, NULL, 'o' },
    { "check-network",  0, NULL, 'n' },
    { "create-nodelist",  0, NULL, 'c' },
    { "version",        0, NULL, 'v' },
    {         0,        0,    0,  0  },
};

/* environment variables */
char  node_list[NODE_NUM_MAX][NODE_WIDTH];
char* check_system;
char* clushc_scpfile;
char* clushc_syncdo;
char* clushc_syncfile;
char* clushc_log;
char* clushc_path;
char* clushc_nodelist;
char* clushc_create_nodelist;

int main(int argc, char **argv)
{
   int opt;
   FILE* fp_conf;

   /*  Initializing Parameter */
   check_system=(char *)malloc(FILEPATH_MAX);
   clushc_scpfile=(char *)malloc(FILEPATH_MAX);
   clushc_syncdo=(char *)malloc(FILEPATH_MAX);
   clushc_syncfile=(char *)malloc(FILEPATH_MAX);
   clushc_log=(char *)malloc(FILEPATH_MAX);
   clushc_path=(char *)malloc(FILEPATH_MAX);
   clushc_nodelist=(char *)malloc(FILEPATH_MAX);
   clushc_create_nodelist=(char *)malloc(FILEPATH_MAX);

   /* Setup Clushc environment variables */ 
   setup_environment();

   /* Initializing memory space, creating nodelist */
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
                clushc_nodelist = optarg;
		unsetenv("CLUSHC_NODELIST");
                setenv("CLUSHC_NODELIST",clushc_nodelist,1);
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
         case 'c':               
               system(clushc_create_nodelist); 
               break;
         case 'v':
	      get_clushc_version();
              break;
         default:
              usage();
      }
   }  
   return 0;
}