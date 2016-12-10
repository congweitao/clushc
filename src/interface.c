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
   char path_checklog[STRING_MAX];
   char path_checklogfile[STRING_MAX];
   char name_checklog[STRING_MAX];  
   char file_extension[24]="-checks.txt";
 
   for(i = 0; i< NODE_NUM_MAX; i++){
      if(strlen(node_list[i]) != 0){
         /* setup filename and filepath */
         strcpy(path_checklog, getenv("CLUSHC_LOG"));
         clushc_strcat(name_checklog, node_list[i],file_extension);
         clushc_strcat(path_checklogfile, path_checklog, name_checklog);
        
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
