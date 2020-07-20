#!/bin/bash

mkdir -p folder
mkdir -p ./folder/A
mkdir -p ./folder/A/B
mkdir -p ./folder/empty_folder
mkdir -p ./folder/level_1
mkdir -p ./folder/level_1/level_2
mkdir -p ./folder/level_1/level_2/level_3
mkdir -p ./folder/level_1/level_2/level_3/empty_folder


cd test_executables_src
g++ Hello_my_PID.cpp -o ../folder/Hello_my_PID
g++ raise_SIGINT.cpp -o ../folder/level_1/level_2/level_3/raise_SIGINT
g++ raise_SIGKILL.cpp -o ../folder/level_1/level_2/level_3/raise_SIGKILL
g++ return_-1.cpp -o ../folder/level_1/level_2/return_-1
g++ return_42.cpp -o ../folder/return_42
g++ sleep_2_seconds.cpp -o ../folder/sleep_2_seconds
g++ write_stderr.cpp -o ../folder/level_1/level_2/write_stderr
cd ..


cd folder
ln -sf /bin/ls ls
ln -sf /bin/echo echo
ln -sf /bin/echo symlink
touch empty_non_executable
echo BlaBlaBla > non_executable
touch empty_executable
chmod +x empty_executable
cp empty_executable ./level_1/level_2/level_3/empty_executable
cp return_42 ./A
cp Hello_my_PID ./A
cp empty_non_executable ./A
cp empty_executable ./A
cp empty_folder ./A
cp ls ./A/B
cp empty_non_executable ./A/B
cd ..
