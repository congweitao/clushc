#!/bin/bash -e

REMOTE_SERVER_TMP_DIR=/tmp/clushc/log

echo "Reducing Information from the Remote Servers..."
for node in `cat ${CLUSHC_NODELIST}`
do
   rsync  -aqvz  root@$node:$REMOTE_SERVER_TMP_DIR/*.txt ${CLUSHC_LOG} >/dev/null 2>&1;
done
