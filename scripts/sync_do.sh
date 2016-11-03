#!/bin/bash -e

echo "Checking system information on all nodes..."
pssh -h ${CLUSHC_NODELIST} "cd /tmp/clushc;sh scripts/check_system.sh" >/dev/null 2>&1;

