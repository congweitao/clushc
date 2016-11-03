/*
 * Functions to check Infiniband Network, Storage, Filesystem, etc.
 *
 */

#include "common.h"

#define FILEPATH_MAX 1024
#define STRING_MAX 1024

// checking node items
struct _check_node{
       char* thread_per_core;
       char* cpu_model;
       char* load_avg;
       char* ib_status;
       char* ib_name;
       char* ib_rate;
       char* ib_opensmd;
       char* ib_connection_mode;
       char* nfs_mounts;
       char* nfs_fsname;
       char* nfs_mntdir;
};

struct _check_node_mem{
	char* memory_size;
	char* dimm_counts;
	char* size;
	char* locator;
	char* type;
	char* speed;
};

struct _check_node_fw{
	char* ib;
	char* bios;
	char* bmc;
};

struct _check_service{
	char* ntpd;
	char* oom;
	char* firewalld;
	char* selinux;
	char* stacksize;
	char* iptable;
};

struct _check_item{
        char hostname[NODE_WIDTH];
        char item_content[200];
};

int clushc_network(
	char* clushc_path, 
	char node_list[NODE_NUM_MAX][NODE_WIDTH]);

int clushc_bios(
	char* clushc_path, 
	char node_list[NODE_NUM_MAX][NODE_WIDTH]);

int clushc_service(
	char* clushc_path, 
	char node_list[NODE_NUM_MAX][NODE_WIDTH]);

int clushc_storage(
	char* clushc_path, 
	char node_list[NODE_NUM_MAX][NODE_WIDTH]);

int clushc_firmware(
	char* clushc_path, 
	char node_list[NODE_NUM_MAX][NODE_WIDTH]);
