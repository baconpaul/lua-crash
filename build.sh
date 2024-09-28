BD=`pwd`/bld
rm -f will_crash
rm -f wont_crash
rm -rf ${BD}
mkdir -p ${BD}/luabld

pushd lib/LuaJIT
cp -r . ${BD}/luabld
popd

pushd ${BD}/luabld
export MACOSX_DEPLOYMENT_TARGET=10.9
make amalg TARGET_CCFLAGS="-O3"
mkdir -p ../lib
mv src/libluajit.a ../lib
popd


clang++ -o will_crash -Ibld/luabld/src -std=c++17 -O3 src/test.cpp -Lbld/lib -lluajit
clang++ -o wont_crash -Ibld/luabld/src -std=c++17 -O3 src/test.cpp -Wl,-no_deduplicate -Lbld/lib -lluajit

