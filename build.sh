BD=`pwd`/bld
mkdir ${BD}
pushd lib/
./build-macos-luajit.sh "${BD}"
popd

clang++ -o will_crash -Ibld/include -std=c++17 -O3 src/test.cpp -Lbld/bin -lluajit
clang++ -o wont_crash -Ibld/include -std=c++17 -O3 src/test.cpp -Wl,-no_deduplicate -Lbld/bin -lluajit

