/**
 * Common Funcitons
 *
 */

#include"common.h"

#define MAX_SIZE 100

int get_nodelist(char* PathList, char NodeList[NODE_NUM_MAX][NODE_WIDTH]){
   FILE* fp;
   int i = 0;
   
   fp=fopen(PathList,"r");
   if (fp == NULL ){
       printf("Nodelist file could not be opened.\n");
       return -1;
   }

   while(!feof(fp)){
        fscanf(fp,"%s",NodeList[i]);
        i++;
   }
   fclose(fp);
 
   return 0;
}

int get_host_id(char HostName[NODE_WIDTH], char PrefixName[NODE_WIDTH]){
  int hp_i=0, hp_j=0, hp_k=0;
  char id_num[NODE_WIDTH];

  for(hp_i=0; hp_i< strlen(HostName); hp_i++){
     if( HostName[hp_i] >= '0' && HostName[hp_i] <='9' ){
         id_num[hp_j++] = HostName[hp_i];
     }
     else {
         PrefixName[hp_k++]=HostName[hp_i];
     }
     id_num[hp_j] = '\0';
  }
  
  return atoi(id_num);
}

char* clushc_strcat(const char* dest, const char* src){
  char* str=malloc(sizeof(char)*(strlen(dest)+strlen(src)));

  strcpy(str,dest);
  if(str[strlen(str)-1] == '\n') str[strlen(str)-1] = '\0';
  
  return  strcat(str,src);
}

char* get_special_line(char* PathLog, int WhichLine){
   FILE* fp_log;
   char* line_content=malloc(MAX_SIZE);
   int i=0,j=0;
   char* item=malloc(100);
   char* item_tmp=malloc(100);

   if( WhichLine == -1 ) {
      item = "NO INFO";
      return item;
   }   

   fp_log = fopen(PathLog,"r"); 
   if (  fp_log == NULL ){
      printf("Log file could not be opened.\n");
      printf("Make sure file %s exist.\n",PathLog);
      return "NO INFO";
    }
   else {
      while(WhichLine--){
       fgets(line_content,MAX_SIZE,fp_log);   
       }
   }
   fclose(fp_log);
   
   i = strlen(line_content);
   while(line_content[i--] != '='){
      if(line_content[i] != '=') item_tmp[j++] = line_content[i];
      else
         {
            item_tmp[--j]='\0';
         }
    }   
   
   j=0;
   for(i=(strlen(item_tmp)-1);i>=0;i--){
       item[j++] = item_tmp[i];
   }
   item[j] = '\0';
   
   return item;
}

int sort_merge(const int NUM,
               char output[NODE_NUM_MAX][NODE_WIDTH], 
               char input[NODE_NUM_MAX][NODE_WIDTH]){

      int i = 0, j = 0;
      int nodelist[NODE_NUM_MAX];
      char* first_item_nodename = input[0];
      char* first_item_content = input[1];
      char* tmp_item = NULL;

      for (i = 2; i < NUM; i++){
          
      }

  return 0;
}


//remove the head and tail spaces
char *remove_space(char *str)  
{  
   char *p = str;
   char *q = str;
 
   while( *q++ ); q -= 2;
   while( p <= q && isspace(*q) ) q--;
   while( p <= q && isspace(*p) ) p++;
   while( p <= q ) *str++ = *p++;
 
   *str = '\0';
 
   return str;
}

int get_row_num(const char* path, const char* item){
    FILE* fp;
    int line = 0;   
    char* str = (char *)malloc(MAX_SIZE);  
  
    fp = fopen(path, "r");
    if(fp == NULL){
	printf("Sys log could not be opened.\n");
	return -1;
    }
    
    while(!feof(fp)){
         fgets(str, MAX_SIZE, fp);
  	 if(!strstr(str, item)) line++;
         else return ++line;
      }

   fclose(fp);
   
   return -1;
}


void usage()
{
 
printf("General usage:
==============
usage: clushc [-h] [-l NODELIST] [-o CHECK_STORAGE] [-n CHECK_NETWORK]
              [--collect-info COLLECT_INFO] [--check-service CHECK_SERVICE]
              [--check-bios CHECK_BIOS] [--check-firmware CHECK_FIRMWARE] [--version]

Clushc administration tool

optional arguments:
  -h, --help            request mon help
  -i INPUT_FILE, --in-file INPUT_FILE
                        input hosts file
  --cluster CLUSTER     cluster name
  --admin-socket ADMIN_SOCKET_NOPE
                        you probably mean --admin-daemon
  -s, --status          show cluster status
  -w, --watch           watch live cluster changes
  --watch-debug         watch debug events
  --watch-info          watch info events
  --watch-sec           watch security events
  --watch-warn          watch warn events
  --watch-error         watch error events
  --version, -v         display version
  --verbose             make verbose
  --concise             make less verbose

Clushc  Version 1.0.0 update 11/2/2016\n");
}

