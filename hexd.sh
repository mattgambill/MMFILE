#!/bin/bash
# Inspect .bin file from command line.
hexdump -e '1/4 "%08x" "\n"' ./mm.bin