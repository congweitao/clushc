/*
 * Functions to check Infiniband Network, Storage, Filesystem, etc.
 *
 */
#include "common.h"
#include "check.h"

int get_item_content(char* path, char* item, 
                     char* ItemContent[NODE_NUM_MAX][2], char NodeList[NODE_NUM_MAX][NODE_WIDTH])
{
   int i = 0;

   static char* parameter = NULL;
   static int row_num = 0;
   char* path_checklog=(char *)malloc(FILEPATH_MAX);
   char* path_checklogfile=(char *)malloc(FILEPATH_MAX);
   char* name_checklog=(char *)malloc(STRING_MAX);  
   
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* setup filename and filepath */
         path_checklog = getenv("CLUSHC_LOG");
         name_checklog = clushc_strcat(node_list[i],"-checks.txt\0");
         path_checklogfile = clushc_strcat(path_checklog, name_checklog);

         row_num = get_row_num(path_checklogfile, item);
         if(row_num == -1) { printf("%s Information was not checked..\n",item);return -1;}     

         parameter = get_special_line(path_checklogfile,row_num);
         remove_space(parameter);

         ItemContent[i][0] = node_list[i];
         ItemContent[i][1] = parameter;
       }
    }
   return 0;
}