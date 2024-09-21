# Shows how to crash LUAJIT with a tiny encapsulated program and xcode 16

Clone this repo and grab the submodules

```
git clone https://github.com/baconpaul/lua-crash
cd lua-crash
git submodule update --init --recursive
```

then run the build script

```
. ./build.sh
```

this will create two executables, `will_crash` and `wont_crash` which with xcode 16 will and wont crash
respectively
