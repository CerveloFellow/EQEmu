#!/bin/bash
# Patch client.h - add SendEdgeStats declaration after LoadMulticlassData
sed -i '/void LoadMulticlassData();/a\\tvoid SendEdgeStats();' /home/eqemu/server_source/zone/client.h
echo "Patched client.h"

# Verify
grep -n "SendEdgeStats\|LoadMulticlassData" /home/eqemu/server_source/zone/client.h

