#!/bin/bash

# env vars

export BOOST_HOME=/Users/dark/work/study/depend/boost
export AIN_HOME=/Users/dark/work/study/ain
# for Linux
#export LD_LIBRARY_PATH=$BOOST_HOME/lib
# for Mac OS X
export DYLD_LIBRARY_PATH=$BOOST_HOME/lib:$AIN_HOME/lib

echo "$LD_LIBRARY_PATH"

if [ $1 ]
then
	$1
else
	tcp_echo_server.exe
fi
