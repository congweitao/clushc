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
       printf("\033[31m[ERROR]\033[0m  NodeList File Could not be Opened.\n");
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
      printf("\033[31m[ERROR]\033[0m Make sure file %s exist.\n",PathLog);
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


//remove the head and tail spaces of a certain character
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


void setup_environment()
{
   /* Setup Clushc environment variables */
   clushc_path = getenv("CLUSHC_PATH");
   clushc_nodelist = getenv("CLUSHC_NODELIST");
   clushc_scpfile = getenv("CLUSHC_SCP");
   clushc_syncdo =  getenv("CLUSHC_SYNCDO");
   clushc_syncfile = getenv("CLUSHC_SYNCFILE");
   check_system = getenv("CLUSHC_CHECK_SYSTEM");
   clushc_log = getenv("CLUSHC_LOG");
   clushc_create_nodelist = getenv("CLUSHC_CREATE_NODELIST");
}

void get_clushc_version()
{
   printf("Clushc  Version 1.0.0 update 11/2/2016\n");
}

void usage()
{
 
   printf("General usage:\n"); 
   printf("==============\n"); 
   printf("usage: clushc [-h] [-l NODELIST] [-o CHECK_STORAGE] [-n CHECK_NETWORK]\n");
<<<<<<< HEAD
   printf("              [--collect-info COLLECT_INFO] [--create-nodelist CREATE_NODELIST]\n");
   printf("              [--check-service CHECK_SERVICE]\n");
=======
   printf("              [--collect-info COLLECT_INFO] [--check-service CHECK_SERVICE]\n");
>>>>>>> ab146f55d50ec0d3d3e59807ea24af00d71b348f
   printf("              [--check-storage CHECK_STORAGE] [--check-network CHECK_NETWORK]\n");
   printf("              [--check-bios CHECK_BIOS] [--check-firmware CHECK_FIRMWARE] [--version]\n\n");

   printf("Clushc administration tool\n\n");

   printf("Optional arguments:\n");
   printf("  -h, --help            request mon help\n");
<<<<<<< HEAD
   printf("  -c, --create-hostlist creating nodelist in CLUSHC root path\n");
   printf("  -l HOSTLIST, --hostlist HOSTLIST\n");
   printf("                        input hosts file\n");
   printf("  -i, --collect-info    collecting information from the clients\n");
=======
   printf("  -l HOSTLIST, --hostlist HOSTLIST\n");
   printf("                        input hosts file\n");
>>>>>>> ab146f55d50ec0d3d3e59807ea24af00d71b348f
   printf("  -n, --check-network   checking network status\n");
   printf("  -f, --check-firmware  checking firmware information\n");
   printf("  -o, --check-storage   checking storage information\n");
   printf("  -s, --check-service   checking OS' default parameter\n");
   printf("  -b, --check-bios      checking BIOS' default parameter\n");
   printf("  --version, -v         display version\n\n");
<<<<<<< HEAD
=======

   printf("Clushc  Version 1.0.0 update 11/2/2016\n");
>>>>>>> ab146f55d50ec0d3d3e59807ea24af00d71b348f
}

