/**
 * Common Funcitons
 *
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

#define NODE_NUM_MAX 1024
#define NODE_WIDTH 24

extern char node_list[NODE_NUM_MAX][NODE_WIDTH];
extern char* check_system;
extern char* clushc_scpfile;
extern char* clushc_syncdo;
extern char* clushc_syncfile;
extern char* clushc_log;
extern char* clushc_path;
extern char* clushc_nodelist;
extern char* clushc_create_nodelist;


int get_nodelist(char* PathList, char NodeList[NODE_NUM_MAX][NODE_WIDTH]);
int get_host_id(char HostName[NODE_WIDTH], char PrefixName[NODE_WIDTH]);

// input stands for nodename and a value
int sort_merge(const int NUM, char output[NODE_NUM_MAX][NODE_WIDTH], 
               char input[NODE_NUM_MAX][NODE_WIDTH]);
char* clushc_strcat(const char* dest, const char* src);
char* get_special_line(char* PathLog, int WhichLine);
int get_row_num(const char* path, const char* item);
//remove the head and tail spaces
char* remove_space(char *str);
void setup_environment();
void usage();
