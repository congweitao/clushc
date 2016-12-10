# Definition of the installation path
INSTALL_PATH=/opt/clushc/


# ------------------
CC=gcc
CXX=g++

exe=clushc

SRC_PATH=$(shell pwd)/src
BIN_PATH=$(shell pwd)/bin

setup:
	/bin/rm -f config/clushc_conf.sh
	/bin/echo "export CLUSHC_PATH=${INSTALL_PATH}" >>  config/clushc_conf.sh
	/bin/echo "export CLUSHC_NODELIST=${INSTALL_PATH}/nodelist" >>  config/clushc_conf.sh
	/bin/echo "export CLUSHC_SCP=${INSTALL_PATH}/scripts/scp_file.sh" >>  config/clushc_conf.sh
	/bin/echo "export CLUSHC_SYNCDO=${INSTALL_PATH}/scripts/sync_do.sh" >>  config/clushc_conf.sh
	/bin/echo "export CLUSHC_SYNCFILE=${INSTALL_PATH}/scripts/sync_file.sh" >>  config/clushc_conf.sh
	/bin/echo "export CLUSHC_CHECK_SYSTEM=${INSTALL_PATH}/scripts/check_system.sh" >> config/clushc_conf.sh
	/bin/echo "export CLUSHC_LOG=${INSTALL_PATH}/log/" >>  config/clushc_conf.sh
	/bin/echo "export CLUSHC_CREATE_NODELIST=${INSTALL_PATH}/scripts/create_nodelist.sh" >> config/clushc_conf.sh
	/bin/cp -a  config/clushc_conf.sh  /etc/profile.d/
	source /etc/profile.d/clushc_conf.sh to use clushc!
clushc:
	${CC} -o ${BIN_PATH}/${exe} -g ${SRC_PATH}/*.c
install:
	/bin/mkdir -p ${INSTALL_PATH}
	/bin/mkdir -p ${INSTALL_PATH}/log
	/bin/mkdir -p ${INSTALL_PATH}/postgresql/data
	/bin/mkdir -p ${INSTALL_PATH}/postgresql/log
	/bin/mkdir -p ${INSTALL_PATH}/config
	/bin/cp -a bin ${INSTALL_PATH}
	/bin/cp -a scripts ${INSTALL_PATH}
	/bin/cp -a config ${INSTALL_PATH}
	/bin/sed -i "s%{INSTALL_PATH}%${INSTALL_PATH}%g" ${INSTALL_PATH}/scripts/check_system.sh
	/bin/sed -i "s%{INSTALL_PATH}%${INSTALL_PATH}%g" ${INSTALL_PATH}/scripts/scp_file.sh
	/bin/sed -i "s%{INSTALL_PATH}%${INSTALL_PATH}%g" ${INSTALL_PATH}/scripts/sync_file.sh
	/bin/rm -f /usr/bin/clushc
	/bin/ln -s ${INSTALL_PATH}/bin/clushc /usr/bin/clushc
clean:
	rm -rf ${SRC_PATH}/*.o 
