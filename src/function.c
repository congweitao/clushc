/**
 * Common Funcitons
 *
 */

#include"function.h"

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



int parse_args(char* args)
{
   if((strcmp(args,"--collect-info") == 0) || (strcmp(args, "-ci") == 0)) return 0; 
   if((strcmp(args,"--check-network") == 0) || (strcmp(args, "-cn") == 0)) return 1; 
   if((strcmp(args,"--check-storage") == 0) || (strcmp(args, "-cstor") == 0)) return 2; 
   if((strcmp(args,"--check-firmware") == 0) || (strcmp(args, "-cf") == 0)) return 3; 
   if((strcmp(args,"--check-bios") == 0) || (strcmp(args, "-cb") == 0)) return 4; 
   if((strcmp(args,"--check-service") == 0) || (strcmp(args, "-cs") == 0)) return 5; 
   else if((strcmp(args,"--help") == 0) || (strcmp(args, "-h") == 0)) return 8;
   else return 8; 
}

void usage()
{
   printf("Clushc Usage: \n");
   printf("clushc --help           |  -h        print help message.\n");
   printf("clushc --collect-info   |  -ci       cluster health check on all nodes.\n");
   printf("clushc --check-service   |  -cs      checking service status on all nodes.\n");
   printf("clushc --check-network  |  -cn       checking network on all nodes.\n");
   printf("clushc --check-storage  |  -cstor      checking storage on all nodes.\n");
   printf("clushc --check-firmware |  -cf       checking firmware on all nodes.\n");
   printf("clushc --check-bios     |  -cb       checking bios on all nodes.\n");
}

