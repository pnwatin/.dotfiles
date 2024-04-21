#!/bin/bash

TOTAL_MEMORY=$(sysctl -n hw.memsize)

TOTAL_BLOCKS=$(
	vm_stat | grep -E 'free|inactive|speculative' | awk '{ sum+=$3 } END { printf "%d", sum }'
)

USED_MEMORY=$((TOTAL_MEMORY - TOTAL_BLOCKS * $(pagesize)))

USED_PERCENTAGE=$((USED_MEMORY * 100 / TOTAL_MEMORY))

sketchybar --set $NAME label="${USED_PERCENTAGE}%"
