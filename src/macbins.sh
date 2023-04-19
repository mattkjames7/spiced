#!/bin/bash
CC=$1
BINDIR=$2
echo $CC
echo $BINDIR
echo $(pwd)
lst="mavh mavcps mavcpt mavhann mavcpsann mavcptann mavlambda ps pt prob psann ptann probann"
for v in $lst; do
	xxd -i $v.bin > $v"_binary.cc"
	sed -i .bak s/"$v"_bin/_binary_"$v"_bin_start/g "$v"_binary.cc
	sed -i .bak s/_binary_"$v"_bin_start_len/_binary_"$v"_bin_size/g "$v"_binary.cc
	echo $CC "$v"_binary.cc -o "$BINDIR"/"$v"_binary.o
	g++ -c -fPIC -std=c++17 -Wextra -O3 "$v"_binary.cc -o "$BINDIR"/"$v"_binary.o
	echo "CC: $v"_binary.cc
	rm -v "$v"_binary.cc
	rm -v "$v"_binary.cc.bak
done
