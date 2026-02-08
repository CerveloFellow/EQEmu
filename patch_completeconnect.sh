#!/bin/bash
# Insert LoadMulticlassData + SendEdgeStats before the closing brace of CompleteConnect
sed -i '/\/\/ enforce some rules\.\./i\\t// Load and send multiclass data to client\n\tLoadMulticlassData();\n\tSendEdgeStats();\n' /home/eqemu/server_source/zone/client_packet.cpp
echo "Patched."
# Verify
sed -n '1005,1025p' /home/eqemu/server_source/zone/client_packet.cpp

