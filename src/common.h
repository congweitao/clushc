/**
 * Common Funcitons
 *
*/
#ifndef _COMMON_H
#define _COMMON_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

/* define the max number of the checked nodes */
#define NODE_NUM_MAX 1024
/* define the hostname length */
#define NODE_WIDTH 24
/* define the filepath length */
#define FILEPATH_MAX 512
/* define a string length */
#define STRING_MAX 1024
/* define the number of selected parameter*/
#define ITEM_NUM 9
/* define the max number of dimms */
#define MAX_DIMMS 24

static char clushc_version[30]="1.0.0";

extern char node_list[NODE_NUM_MAX][NODE_WIDTH];
extern char check_system[STRING_MAX];
extern char clushc_scpfile[STRING_MAX];
extern char clushc_syncdo[STRING_MAX];
extern char clushc_syncfile[STRING_MAX];
extern char clushc_log[STRING_MAX];
extern char clushc_path[STRING_MAX];
extern char clushc_nodelist[STRING_MAX];
extern char clushc_create_nodelist[STRING_MAX];


int get_nodelist(char* PathList, char NodeList[NODE_NUM_MAX][NODE_WIDTH]);
int get_host_id(char HostName[NODE_WIDTH], char PrefixName[NODE_WIDTH]);
/* input stands for nodename and a value */
int sort_merge(int NodesNUM, int InputList[NODE_NUM_MAX]);
void clushc_strcat(char* target, const char* dest, const char* src);
char* get_special_line(char* PathLog, int WhichLine);
int get_row_num(const char* path, const char* item);
//remove the head and tail spaces
char* remove_space(char *str);
/* get item and content */
int get_item_content(char* path, char* item, 
	             char* ItemContent[NODE_NUM_MAX][2], char NodeList[NODE_NUM_MAX][NODE_WIDTH]);
void setup_environment();
void get_clushc_version();
void usage();
#endif
