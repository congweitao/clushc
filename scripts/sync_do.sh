#!/bin/bash -e

echo "Checking System on All Nodes..."
pssh -h ${CLUSHC_NODELIST} "cd /tmp/clushc;sh scripts/check_system.sh" >/dev/null 2>&1;

