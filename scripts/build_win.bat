@echo off

cd %~f0
cd ..
mkdir build
cmake -S . -B build
cmake --build build --config Release