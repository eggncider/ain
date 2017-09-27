###############################################################################
# Created By	: dark
# Date Created	: 2017.04.05
###############################################################################

####### YOU CAN EDIT FROM HERE ################################################
SRC=\
	tcp_echo_server.cpp	\

OBJ=$(SRC:.cpp=.o)

TARGET=tcp_echo_server.exe
####### YOU CAN EDIT TO HERE ##################################################
include ../../../ain.mk

all: $(TARGET)

$(TARGET) : $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LIB)

.cpp.o :
	$(CXX) -g $(CXX_FLAG) $(INC) -I../ -c  $<
#
# for linking shared lib (libain.so.1.1)
#	$(CXX) -DAIN_SEPARATE_COMPILATION -g $(CXX_FLAG) $(INC) -I../ -c  $<

clean:
	rm -f $(TARGET) $(OBJ)
