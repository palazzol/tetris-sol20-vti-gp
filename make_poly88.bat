@echo off

cd src
zcc +sol20 -pragma-define:REGISTER_SP=16384 -pragma-define CRT_ORG_CODE=4096 tetris.c -o ..\out\tetris_poly88.com -DZCC -DPOLY88 -create-app
cd ..
call node tools\mkent out\tetris_poly88.com 1000 > out\tetris_poly88.ent

