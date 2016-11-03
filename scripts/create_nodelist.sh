#!/bin/bash
#
# Script: Get Available Nodes Script 
# Created By: Weitao Cong (congwt@sugon.com) www.sugon.com
# Created On: 30th Oct. 2016
# Detail: To Get Available Nodes in the Cluster 
# HowTo Run: chmod +x get_avail_nodes; ./get_avail_nodes.sh
# License: GPL
#


IP_LIST_TMP=$(grep -oP '\d+\.\d+\.\d+\.\d+' /etc/hosts)

create_nodelist(){
  rm -f ${INSTALL_PATH}/.nodelist_tmp
  rm -f ${INSTALL_PATH}/nodelist
  for  ip in ${IP_LIST_TMP[@]}
  do
     ping -c 1 -w 1 $ip >/dev/null 2>&1;
     if [ $? -eq 0 ];then
        echo -e "[\033[34mWARNING\033[0m] Trying ssh $ip...(If processing holds on more than 5 sec, Press [Ctrl+C] to continue.)"
        ssh -q -o NumberOfPasswordPrompts=0 -o ConnectTimeout=2 $ip "hostname" >/dev/null 2>&1;
        if [ $? -eq 0 ];then
           echo $(ssh $ip "hostname") >> ${INSTALL_PATH}/.nodelist_tmp
        fi
     fi
  done
  sort ${INSTALL_PATH}/.nodelist_tmp | uniq >> ${INSTALL_PATH}/nodelist;
}

create_nodelist
