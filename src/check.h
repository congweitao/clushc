/*
 * Functions to check Infiniband Network, Storage, Filesystem, etc.
 *
 */
#ifndef  _CHECK_H
#define  _CHECK_H
#include "common.h"

/* define an array to store check status */
int status[ITEM_NUM];

/* the selected check-items */
struct _check_item{
	int ht;      // hyper-threading
	int cpu;
	int cpu_temp;
	int mem_dimms;
	int disk_usage;
        int load_avg; // load average
	int ib_opensmd;
	int ib_status;
	int ib_conn_mode;
	int stack; // the stack size
};

/* checking node items */
struct _check_node{
       char* thread_per_core;
       char* cpu_model;
       char* cpu_temp;
       char* processors;
       char* load_avg;
       char* cpu_used;
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
	char* mem_size;
	char* mem_dimms;
	char* mem_dimms_used;
	char* mem_dimms_size;
	char* size;
	char* locator;
	char* type;
	char* speed;
	char* mem_used_perc;
};

struct _check_node_fw{
	char* ib;
	char* bios;
	char* bmc;
};

struct _check_node_disk{
	char* disk_num;
	char* disk_vendor;
        char* disk_size;
	char* disk_usage;
	char* disk_protocol;
	char* disk_rate;
};

struct _check_service{
	char* ntpd;
	char* oom;
	char* firewalld;
	char* selinux;
	char* stacksize;
	char* iptable;
};

struct _check_torque{
	char* pbs_mom;
	char* pbs_server;
	char* trqauthd;
	char* maui;
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

// output a check report of the selected parameters
int output_report(
	char* clushc_path,
	char node_list[NODE_NUM_MAX][NODE_WIDTH]);
#endif
