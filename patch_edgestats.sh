#!/bin/bash
set -e

echo "=== Multiclass EdgeStat Patch Script ==="
echo ""

# --- PATCH 1: client.h - add SendEdgeStats declaration ---
echo "Patching client.h..."
if grep -q "SendEdgeStats" /home/eqemu/server_source/zone/client.h; then
    echo "  SKIP: SendEdgeStats already declared in client.h"
else
    sed -i '/void LoadMulticlassData();/a\\tvoid SendEdgeStats();' /home/eqemu/server_source/zone/client.h
    echo "  OK: Added SendEdgeStats() declaration"
fi

# --- PATCH 2: client.h - add include for edge_stats.h ---
echo "Patching client.h include..."
if grep -q "edge_stats.h" /home/eqemu/server_source/zone/client.h; then
    echo "  SKIP: edge_stats.h already included"
else
    sed -i '/#include.*eq_packet_structs.h/a #include "../common/edge_stats.h"' /home/eqemu/server_source/zone/client.h
    # If that didn't match, try adding after the first #include block
    if ! grep -q "edge_stats.h" /home/eqemu/server_source/zone/client.h; then
        sed -i '1,/^#include/{/^#include/a #include "../common/edge_stats.h"
        }' /home/eqemu/server_source/zone/client.h
    fi
    echo "  OK: Added #include for edge_stats.h"
fi

# --- PATCH 3: client_packet.cpp - add LoadMulticlassData + SendEdgeStats to CompleteConnect ---
echo "Patching client_packet.cpp (CompleteConnect)..."
if grep -q "SendEdgeStats" /home/eqemu/server_source/zone/client_packet.cpp; then
    echo "  SKIP: SendEdgeStats already called in client_packet.cpp"
else
    # Insert before the closing brace of CompleteConnect, after CanEnterZone block
    sed -i '/GoToBind();/{
        n
        /return;/{
            n
            /[[:space:]]*}/{
                i\\
\t// Load and send multiclass data to client\
\tLoadMulticlassData();\
\tSendEdgeStats();
            }
        }
    }' /home/eqemu/server_source/zone/client_packet.cpp
    echo "  OK: Added LoadMulticlassData() and SendEdgeStats() calls"
fi

# --- Verify all patches ---
echo ""
echo "=== Verification ==="
echo ""
echo "--- client.h: SendEdgeStats declaration ---"
grep -n "SendEdgeStats\|LoadMulticlassData\|edge_stats.h" /home/eqemu/server_source/zone/client.h
echo ""
echo "--- client_packet.cpp: CompleteConnect calls ---"
grep -n "SendEdgeStats\|LoadMulticlassData" /home/eqemu/server_source/zone/client_packet.cpp
echo ""
echo "--- edge_stats.h exists ---"
ls -la /home/eqemu/server_source/common/edge_stats.h
echo ""
echo "=== Done ==="

