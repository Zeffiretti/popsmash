@echo off

cd %~f0
cd ..
cmake -S .. -B ../build
cmake --build ../build --config Release