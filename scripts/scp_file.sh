#!/bin/bash

TOP_DIR=${CLUSHC_PATH}

pssh -h ${CLUSHC_NODELIST} "mkdir -p /tmp/clushc/bin"  >/dev/null 2>&1
pssh -h ${CLUSHC_NODELIST} "mkdir -p /tmp/clushc/scripts" >/dev/null 2>&1
pssh -h ${CLUSHC_NODELIST} "mkdir -p /tmp/clushc/log" >/dev/null 2>&1

echo "Syncing Scripts to All Nodes..."
for node in `cat ${CLUSHC_NODELIST}`
do
   scp -r  ${CLUSHC_NODELIST}  $node:/tmp/clushc/ >/dev/null 2>&1;
   scp -r  $TOP_DIR/bin/*  $node:/tmp/clushc/bin >/dev/null 2>&1;
   scp -r  $TOP_DIR/scripts/*  $node:/tmp/clushc/scripts >/dev/null 2>&1;
done
pssh -h ${CLUSHC_NODELIST} "sed -i 's%TOP_DIR=%TOP_DIR=/tmp/clushc ##%g' /tmp/clushc/scripts/check_system.sh" >/dev/null 2>&1
pssh -h ${CLUSHC_NODELIST} "sed -i 's%TOP_DIR=%TOP_DIR=/tmp/clushc ##%g' /tmp/clushc/scripts/sync_do.sh" >/dev/null 2>&1
pssh -h ${CLUSHC_NODELIST} "sed -i 's%TOP_DIR=%TOP_DIR=/tmp/clushc ##%g' /tmp/clushc/scripts/scp_file.sh" >/dev/null 2>&1
