set -x
#clang++ -std=c++23 -O3 -S -o Tjg_test.s Tjg_test.cpp
##clang++ -std=c++23 -O3 GenericCrc_test.cpp
#clang++ -std=c++23 -Os -march=native GenericCrc_benchmark.cpp # Plain       839ms
#clang++ -std=c++23 -O1 -march=native GenericCrc_benchmark.cpp # Generic     442ms
#clang++ -std=c++23 -O3 -march=native GenericCrc_benchmark.cpp # Traditional 832ms

clang++ -std=c++23 -O0 -march=native GenericCrc_benchmark.cpp
echo -e "\nCompiled with -O0 -march=native" >  test_results.txt
./a.out | tee --append test_results.txt
clang++ -std=c++23 -O1 -march=native GenericCrc_benchmark.cpp
echo -e "\nCompiled with -O1 -march=native" >> test_results.txt
./a.out | tee --append test_results.txt
clang++ -std=c++23 -O2 -march=native GenericCrc_benchmark.cpp
echo -e "\nCompiled with -O2 -march=native" >> test_results.txt
./a.out | tee --append test_results.txt
clang++ -std=c++23 -O3 -march=native GenericCrc_benchmark.cpp
echo -e "\nCompiled with -O3 -march=native" >> test_results.txt
./a.out | tee --append test_results.txt
clang++ -std=c++23 -Os -march=native GenericCrc_benchmark.cpp
echo -e "\nCompiled with -Os -march=native" >> test_results.txt
./a.out | tee --append test_results.txt
