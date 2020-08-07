@echo off
win_flex -Pdnayy -o dna_lxx.cxx dna.lxx
win_bison -y -d -p dnayy -o dna_yxx.cxx dna.yxx
pause
