#!/bin/bash
#
# Script: Node Health Script 
# Created By: Weitao Cong (congwt@sugon.com) www.sugon.com
# Created On: 29th August 2016
# Detail: To Check Single Node Health. 
# HowTo Run: chmod +x check_system.sh; ./check_system.sh
# Checks: loadavg, memory, cpu, ehternet, infiniband, infiniband ipath test, cpu test, nfs mounts, nis, mcelog
# Functions: You can load/unload any function you need to run or not to run.
# License: GPL
#

TOP_DIR=${CLUSHC_PATH}

## Check Tools
check_command()
{
   CMD=$1
   which ${CMD} >/dev/null 2>&1 
   if [ $? != 0 ];then
      echo -e "\033[31m[ERROR]\033[0m $(hostname)'s command ${CMD} not found..."
      return 1;
   else
      return 0;
   fi
}

## Operating Sytem
os(){
OS=`cat /etc/redhat-release`
Kernel_version=`uname -r`
STACK_SIZE=`ulimit -s`
OOM=`sysctl -a | grep vm.overcommit_memory | awk -F '=' '{print $2}'`

echo "OS = $OS" >> $Report
echo "KERNEL_VER = $Kernel_version" >> $Report
echo "STACK_SIZE = $STACK_SIZE" >> $Report
echo "OOM = $OOM" >> $Report
}

## LoadAvg Function
loadavg() {
LoadAvg=`uptime | awk -F "load average:" '{print $2}' | cut -f 1 -d,`
echo "LOAD_AVG = $LoadAvg" >> $Report
}

selinux(){
SELINUX=`cat /etc/sysconfig/selinux | sed -n "/^SELINUX=/p" | awk -F '=' '{print $2}'`

echo "SELINUX = $SELINUX" >> $Report
}


disk(){
# check the local disks, number, capacity, usage, protocol, rotation rate, 
DISK_NAME=($(cat /proc/diskstats |grep sd|sed 's/[0-9]//g'| sed 's/[[:space:]]//g'|sort|uniq))
DISK_VENDOR=($(cat /proc/scsi/scsi |grep 'Vendor:'|awk '{print $2}'))
DISK_NUM=$(echo ${#DISK_NAME[@]})
DISK_VENDORsda=${DISK_VENDOR[0]}
DISK_CAPACITYsda=$(smartctl -a /dev/sda |grep 'User Capacity:'|sed 's/\[//'|sed 's/\]//'|awk '{print $5$6}')
ROTATION_RATEsda=$(smartctl -a /dev/sda |grep 'Rotation Rate:'|awk '{print $3$4}')
TRANSPORT_PROTOCOLsda=$(smartctl -a /dev/sda |grep 'Transport protocol:'|awk '{print $3}')
DISK_HEALTH_STATUSsda=$(smartctl -H /dev/sda | awk -F ':' '{printf $2}')
DISK_USAGE=$(df -k | grep -v Filesystem| awk '{print int($5)}' |head -n1)

echo "DISK_NUM = $DISK_NUM " >> $Report; 
echo "DISK_VENDORsda = ${DISK_VENDORsda}" >> $Report;
echo "DISK_CAPACITYsda = $DISK_CAPACITYsda" >> $Report;
echo "DISK_USAGE = $DISK_USAGE" >> $Report;
echo "ROTATION_RATEsda = $ROTATION_RATEsda" >> $Report;
echo "TRANSPORT_PROTOCOLsda = $TRANSPORT_PROTOCOLsda" >> $Report;
echo "DISK_HEALTH_STATUSsda = $DISK_HEALTH_STATUSsda">> $Report;
}

bios(){
SERIAL_NUM_TMP1=`dmidecode -s system-serial-number`;

if [  -n "$(echo $SERIAL_NUM_TMP1 | sed -n "/^[0-9]\+$/p")" ];then
   SERIAL_NUM=$SERIAL_NUM_TMP1;
else
   SERIAL_NUM="NULL";
fi

BIOS_FW=`dmidecode -t bios | grep Version | awk -F ':' '{print $2}'`;
BMC_FW="NULL";

echo "SERIAL_NUM = $SERIL_NUM" >> $Report;
echo "BIOS_FW = $BIOS_FW" >> $Report;
echo "BMC_FW = $BMC_FW" >> $Report;
}

## System date, online time
sys_time()
{
   DATE=`date +%Y/%m/%d/%H:%M`
   UPTIME=`uptime | awk -F " " '{print $2,$3,$4,$5}'`
  
   echo "DATE = $DATE" >> $Report; 
   echo "UPTIME = $UPTIME" >> $Report;
}

## Memory Function
memory() {
TOTAL_MEM=`grep "MemTotal:" /proc/meminfo | awk '{msum+=($2/1024)/1024} END {printf "%.0f",msum}'`
FREE_MEM=`grep "MemFree:" /proc/meminfo | awk '{mfree+=($2/1024)/1024} END {printf "%.0f",mfree}'`
TOTAL_SWAP=`grep "SwapTotal:" /proc/meminfo | awk '{ssum+=($2/1024)/1024} END {printf "%.0f",ssum}'`
FREE_SWAP=`grep "SwapFree:" /proc/meminfo | awk '{sfree+=($2/1024)/1024} END {printf "%.0f",sfree}'`
BUFFERS=`grep "Buffers:" /proc/meminfo | awk '{sfree+=($2/1024)/1024} END {printf "%.0f",sfree}'`
CACHED=`grep "Cached:" /proc/meminfo | awk '{sfree+=($2/1024)/1024} END {printf "%.0f",sfree}'`
MEM_USED_PERC=$(expr 100 \* \( $TOTAL_MEM - $FREE_MEM - $BUFFERS - $CACHED \) \/ $TOTAL_MEM )
TOTAL_DIMMS=$(dmidecode -t memory |grep 'Size' |wc -l)
USED_DIMMS=$(dmidecode -t memory |grep 'MB$' |grep  '[[:digit:]]'|wc -l)
SINGLE_MEM_SIZE=($(dmidecode -t memory |grep 'MB$'|awk -F ':' '{print $2}'|sort|uniq))

echo "MEMORY_SIZE = $TOTAL_MEM" >> $Report
echo "MEM_USED_PERC = ${MEM_USED_PERC}" >> $Report 
echo "SWAP_SIZE = $TOTAL_SWAP" >> $Report
echo "TOTAL_DIMMS = $TOTAL_DIMMS" >> $Report
echo "USED_DIMMS = $USED_DIMMS" >> $Report
echo "SINGLE_MEM_SIZE = $SINGLE_MEM_SIZE" >> $Report
}

## CPU Function
cpu() {
NUM_PROCESSOR=`grep processor /proc/cpuinfo | wc -l`
THREAD_PER_CORE=`lscpu | grep 'Thread(s) per core'| awk '{print $4}'`
CPU_MODEL=`cat /proc/cpuinfo | grep 'model name' | sort | uniq | cut -d : -f 2`
CACHE_SIZE=`cat /proc/cpuinfo | grep 'cache size' | sort | uniq | cut -d : -f 2`
CACHE_ALIGMENT=`cat /proc/cpuinfo | grep cache_alignment | sort | uniq | cut -d : -f 2`
CPU_USED=$(ps -A -o  pcpu | tail -n+2 | paste -sd+ | bc);

check_command ipmitool;
if [ $? -eq 0 ];then
   CPU0_TEMP=`ipmitool -I open sdr | grep CPU0_Temp | awk -F ' ' '{print $3}'`
   CPU1_TEMP=`ipmitool -I open sdr | grep CPU1_Temp | awk -F ' ' '{print $3}'`
else
   CPU0_TEMP="UNKOWN"
   CPU1_TEMP="UNKOWN"
fi

if [ -n "$CPU0_TEMP" ];then
   echo "CPU0_TEMP = $CPU0_TEMP" >> $Report
fi

if [ -n "$CPU1_TEMP" ];then
   echo "CPU1_TEMP = $CPU1_TEMP" >> $Report
fi

echo "PROCESSORS = $NUM_PROCESSOR" >> $Report
echo "THREAD_PER_CORE = $THREAD_PER_CORE" >> $Report
echo "CPU_MODEL = $CPU_MODEL" >> $Report
echo "CACHE_SIZE = $CACHE_SIZE" >> $Report
echo "CACHE_ALIGMENT = $CACHE_ALIGMENT" >> $Report
echo "CPU_USED = $CPU_USED" >> $Report
}

## Ethernet Function (eth1 for me, you can edit for yours)
ethernet() {
NUM_ETHER_CONT=$(lspci | grep 'Ethernet controller' | wc -l)
NAME_UP_ETHER=($(ip link show | grep 'state UP' | awk '{print $2}' | cut -d : -f 1|grep e))
ETHER_SPEED=($(ethtool ${NAME_UP_ETHER[0]} | grep "Speed:" | awk '{print $2}'))

echo "NAME_UP_ETHER = $NAME_UP_ETHER" >> $Report;
echo "NUM_ETH_CONT = $NUM_ETHER_CONT" >> $Report;
echo "ETH_SPEED = $ETHER_SPEED" >> $Report
}

## IB Function
ib() {
check_command ibstat;
if [ $? != 0 ];then
   return 1;
fi

NUM_IB_CONT=$(lspci | grep 'Mellanox' | wc -l)
IB_FW=($(cat /sys/class/infiniband/mlx*/fw_ver))
NAME_UP_IB=($(ip link show | grep 'state UP' | awk '{print $2}' | cut -d : -f 1|grep ib))
IB_HCA_TYPE=($(cat /sys/class/infiniband/mlx*/hca_type))
IB_DRIVER=`ofed_info | grep OFED-`
IB_STATE=($(cat /sys/class/infiniband/*/ports/1/state | awk -F ":" '{print $2}'))
IB_PHYS_STATE=($(cat /sys/class/infiniband/*/ports/1/phys_state | awk -F ":" '{print $2}'))
IB_RATE=($(cat /sys/class/infiniband/*/ports/1/rate))
IB_PORT=($(ibstat -p))
OPENSMD=$(/etc/init.d/opensmd status | awk -F 'is ' '{print $2}')
CONNECTION_MODE=($(cat /sys/class/net/ib*/mode))

echo "NUM_IB_CONT = $NUM_IB_CONT" >> $Report
echo "IB_FW = $IB_FW" >> $Report
echo "NAME_UP_IB = $NAME_UP_IB" >> $Report
echo "IB_STATE = $IB_STATE" >> $Report
echo "IB_RATE = $IB_RATE" >> $Report
echo "IB_HCA_TYPE = $IB_HCA_TYPE" >> $Report
echo "IB_DIRVER = $IB_DRIVER" >> $Report
echo "IB_LINK_STATE = $IB_PHYS_STATE" >> $Report
echo "IB_PORT = $IB_PORT" >> $Report
echo "OPENSMD = $OPENSMD" >> $Report
echo "CONNECTION_MODE = $CONNECTION_MODE" >> $Report
}

## NFS Mounts Function
nfs() {
NFS_MOUNTS=`mount | grep ':.*nfs' | wc -l`
if [ $NFS_MOUNTS -eq 1 ];then
   NFS_FSNAME=`cat /etc/mtab | grep ':.*nfs' | awk -F ' ' '{print $1}'| sed -n '1p'`
   NFS_DIR=`cat /etc/mtab | grep ':.*nfs' | awk -F ' ' '{print $2}'|sed -n '1p'`
   NFS_TYPE=`cat /etc/mtab | grep ':.*nfs' | awk -F ' ' '{print $3}'| sed -n '1p'`
#   NFS_OPTS=`cat /etc/mtab | grep ':.*nfs' | awk -F ' ' '{print $4}'| sed -n '1p'`
else
   NFS_FSNAME="NULL"
   NFS_DIR="NULL"
   NFS_TYPE="NULL"
#   NFS_OPTS="NULL"
fi

LUSTRE_MOUNTS=`mount | grep lustre | wc -l`
PARASTOR_MOUNTS=`mount | grep parastor | wc -l`

echo "NFS_MOUNTS = $NFS_MOUNTS" >> $Report
echo "NFS_FSNAME = $NFS_FSNAME" >> $Report
echo "NFS_DIR = $NFS_DIR" >> $Report
echo "NFS_TYPE = $NFS_TYPE" >> $Report
echo "ParaStor_MOUNTS = $PARASTOR_MOUNTS" >> $Report
echo "Lustre_MOUNTS = $LUSTRE_MOUNTS" >> $Report
}

lustre_client(){
LUSTRE_MOUNTS=`mount | grep lustre | wc -l`
if [ "$LUSTRE_MOUNTS" == "0" ];then
   exit 0;
fi
FSNAME_MOUNTPOINT=$(lfs getname)
LUSTRE_VERSION=$(lfs --version | awk -F ' ' '{print $2}' )

echo "LUSTRE_VERSION = $LUSTRE_VERSION" >> $Report
echo "LUSTRE_MOUNTS = $LUSTRE_MOUNTS" >> $Report
echo "FSNAME_MOUNTPOINT = $FSNAME_MOUNTPOINT" >> $Report
}

lustre_server(){
LUSTRE_KERNEL=`uname -r | grep lustre | wc -l`
if [ "$LUSTRE_KERNEL" == "0" ];then
   exit 0;
fi

echo "LUSTRE_SERVER = $(hostname)" >> $Report
}

## NIS Function
nis() {
check_command ypwhich;
if [ $? -eq 0 ];then
   ypwhich >/dev/null 2>&1;
   if [  $? -eq 0 ];then
      NIS_TEST=`ypwhich`
   else
     NIS_TEST="NULL"
   fi
else
   NIS_TEST="NULL"
fi

echo "NIS_SERVER = $NIS_TEST" >> $Report
}

## MCELog Test Function
mcelog() {
MCELog=`if [ -s /var/log/mcelog ]; then echo "Check MCELog"; else echo "No MCELog"; fi`

echo "MCE_LOG = $MCELog" >> $Report
}

## User Information Check
userinfo()
{
USER_COUNTS=`grep '/home' /etc/passwd | wc -l`
USER_ONLINE=`uptime | awk -F ' ' '{print $6}'`
echo "USER_COUNTS = $USER_COUNTS" >> $Report
echo "USER_ONLINE = $USER_ONLINE" >> $Report
}

### MAIN SCRIPT

## Get Node Name
Hostname=`hostname -s`
touch ${TOP_DIR}/log/$Hostname-checks.txt
Report=${TOP_DIR}/log/$Hostname-checks.txt
echo " " > $Report
echo "NODE = ${Hostname}" >> $Report
echo "----------------" >> $Report

## Get Cluster Name
Cluster=`echo $Hostname | cut -c1-4`

## Call Function
os
loadavg
sys_time
selinux
memory
cpu
ethernet
ib
nfs
disk
nis
userinfo
mcelog
bios

## Generate Report
echo " " >> $Report
## cat $Report
