g++ -std=c++17 -Wall -O2 fast.cpp -o fast
g++ -std=c++17 -Wall -O2 slow.cpp -o slow
 
while [ 1 ]; do
    python ./gen.py > input
    ./slow < input > answer
    ./fast < input > output
    diff output answer || break
    echo "done"
done
