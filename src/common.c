/**
 * Common Funcitons
 *
 */

#include"common.h"

#define MAX_SIZE 1024

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
 
   return --i;
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

void clushc_strcat(char* target, const char* dest, const char* src){
     int i = 0, j = 0;
     
     strcpy(target,dest);
     while(target[i] != '\0' ) i++;
     while(src[j] != '\0' ) 
     {
        target[i] = src[j];
        i++;
        j++;
     }
     target[i] = '\0';
}

char* get_special_line(char* PathLog, int WhichLine){
   FILE* fp_log;
   char* line_content=malloc(MAX_SIZE);
   int i=0,j=0;
   char* item=malloc(100);
   char* item_tmp=malloc(100);

   if( WhichLine == -1 ) {
      return "NO INFO";
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

/* ML kmeans*/
int sort_merge(int NodesNum, int InputList[NODE_NUM_MAX])
{
   int i = 0, j = 0;
   int tmp = 0, N = 0;
   int index = 0, count[MAX_DIMMS] ={0};

   /* bubble sort, smallest to the biggest */
   for(i = 0; i< NodesNum; i++)
     for(j = 1;j < NodesNum; j++)
      {
         if (InputList[i] > InputList[j])
          {
            tmp = InputList[i];
            InputList[i] = InputList[j];
            InputList[j] = tmp;
          }
      }
   /* to find out the largest counts of dimms */
  for(i = 1; i <= MAX_DIMMS; i++)
  {
    if(InputList[i] != 0) count[InputList[i]]++;
  }

  tmp = count[1]; 
  for(i = 2; i < MAX_DIMMS; i++)
  {  
    if(tmp < count[i])
      {
         tmp = count[i];
         index = i;
      }
  }

  return index;
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
         else 
         {
            free(str);
            fclose(fp);
            return ++line;
         }
      }
}


void setup_environment()
{
   /* Setup Clushc environment variables */
   strcpy(clushc_path, getenv("CLUSHC_PATH"));
   strcpy(clushc_nodelist, getenv("CLUSHC_NODELIST"));
   strcpy(clushc_scpfile, getenv("CLUSHC_SCP"));
   strcpy(clushc_syncdo,  getenv("CLUSHC_SYNCDO"));
   strcpy(clushc_syncfile, getenv("CLUSHC_SYNCFILE"));
   strcpy(check_system, getenv("CLUSHC_CHECK_SYSTEM"));
   strcpy(clushc_log, getenv("CLUSHC_LOG"));
   strcpy(clushc_create_nodelist, getenv("CLUSHC_CREATE_NODELIST"));
}

void get_clushc_version()
{
   printf("Clushc  Version %s \n",clushc_version);
}

void usage()
{
 
   printf("General usage:\n"); 
   printf("==============\n"); 
   printf("usage: clushc [-h] [-l NODELIST] [-o CHECK_STORAGE] [-n CHECK_NETWORK]\n");
   printf("              [--collect-info COLLECT_INFO] [--create-nodelist CREATE_NODELIST]\n");
   printf("              [--check-service CHECK_SERVICE]\n");
   printf("              [--collect-info COLLECT_INFO] [--check-service CHECK_SERVICE]\n");
   printf("              [--check-storage CHECK_STORAGE] [--check-network CHECK_NETWORK]\n");
   printf("              [--check-bios CHECK_BIOS] [--check-firmware CHECK_FIRMWARE] [--version]\n\n");

   printf("Clushc administration tool\n\n");

   printf("Optional arguments:\n");
   printf("  -h, --help            request mon help\n");
   printf("  -c, --create-hostlist creating nodelist in CLUSHC root path\n");
   printf("  -l HOSTLIST, --hostlist HOSTLIST\n");
   printf("                        input hosts file\n");
   printf("  -i, --collect-info    collecting information from the clients\n");
   printf("  -p, --report          outputing a check report\n");
   printf("  -n, --check-network   checking network status\n");
   printf("  -f, --check-firmware  checking firmware information\n");
   printf("  -o, --check-storage   checking storage information\n");
   printf("  -s, --check-service   checking OS' default parameter\n");
   printf("  -b, --check-bios      checking BIOS' default parameter\n");
   printf("  --version, -v         display version\n\n");
}

