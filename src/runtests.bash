set -x

#g++ -std=c++23 -O3 -march=native -S lsb32.cpp -o lsb32.s

g++ -std=c++23 -O0 -march=native lsb32.cpp -o lsb32.exe
echo -e "\nCompiled with -O0 -march=native" >  test_results.txt
./lsb32.exe | tee --append test_results.txt
g++ -std=c++23 -O1 -march=native lsb32.cpp -o lsb32.exe
echo -e "\nCompiled with -O1 -march=native" >> test_results.txt
./lsb32.exe | tee --append test_results.txt
g++ -std=c++23 -O2 -march=native lsb32.cpp -o lsb32.exe
echo -e "\nCompiled with -O2 -march=native" >> test_results.txt
./lsb32.exe | tee --append test_results.txt
g++ -std=c++23 -O3 -march=native lsb32.cpp -o lsb32.exe
echo -e "\nCompiled with -O3 -march=native" >> test_results.txt
./lsb32.exe | tee --append test_results.txt
g++ -std=c++23 -Os -march=native lsb32.cpp -o lsb32.exe
echo -e "\nCompiled with -Os -march=native" >> test_results.txt
./lsb32.exe | tee --append test_results.txt
g++ -std=c++23 -Og -march=native lsb32.cpp -o lsb32.exe
echo -e "\nCompiled with -Og -march=native" >> test_results.txt
./lsb32.exe | tee --append test_results.txt
