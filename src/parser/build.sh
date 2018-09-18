#!/bin/bash

flex -Pdnayy -o dna_lxx.cxx dna.lxx
bison -y -d -p dnayy -o dna_yxx.cxx dna.yxx
