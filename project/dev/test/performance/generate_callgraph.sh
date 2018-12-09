#!/bin/bash

cp ../../integration/8bH_cli/gmon.out ./gmon.out
gprof ../../integration/8bH_cli/8_bit_Hubble_cli.exe ./gmon.out | python ./gprof2dot.py > 8bH_callgraph.dot
