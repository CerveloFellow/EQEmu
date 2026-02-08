#!/bin/bash
set -e

echo "=== Appending SendEdgeStats to client.cpp ==="

# Add include for edge_stats.h to client.cpp
if grep -q "edge_stats.h" /home/eqemu/server_source/zone/client.cpp; then
    echo "SKIP: edge_stats.h already included in client.cpp"
else
    # Add it near the top includes
    sed -i '/#include "client.h"/a #include "../common/edge_stats.h"' /home/eqemu/server_source/zone/client.cpp
    echo "OK: Added #include for edge_stats.h to client.cpp"
fi

# Append SendEdgeStats function to client.cpp
if grep -q "Client::SendEdgeStats" /home/eqemu/server_source/zone/client.cpp; then
    echo "SKIP: SendEdgeStats already exists in client.cpp"
else
    cat /home/eqemu/server_source/zone/send_edge_stats.cpp.snippet >> /home/eqemu/server_source/zone/client.cpp
    echo "OK: Appended SendEdgeStats() to client.cpp"
fi

# Verify
echo ""
echo "--- Verification ---"
grep -n "SendEdgeStats\|edge_stats.h" /home/eqemu/server_source/zone/client.cpp
echo ""
echo "Done!"

