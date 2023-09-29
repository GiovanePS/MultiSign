############# CC FLAGS ###############################
NAME = default
CC = g++
CPPFLAGS = -g -std=c++98
DEFS = -DFIPS

############# ENVIRONMENT ###############################
OPENSSL_PREFIX ?= /usr/local/ssl
OPENSSL_LIBDIR ?= $(OPENSSL_PREFIX)/lib
OPENSSL_INCLUDEDIR ?= $(OPENSSL_PREFIX)/include
LIBCRYPTOSEC_PREFIX ?= /usr/local
LIBCRYPTOSEC ?= $(LIBCRYPTOSEC_PREFIX)/lib64/libcryptosec.so
LIBCRYPTOSEC_INCLUDEDIR ?= $(LIBCRYPTOSEC_PREFIX)/include/libcryptosec/
LIBP11_PREFIX ?= /opt/libp11/
LIBP11_INCLUDEDIR ?= $(LIBP11_PREFIX)/include/

############ DEPENDENCIES ############################
LIBS = $(LIBCRYPTOSEC) -L$(OPENSSL_LIBDIR) -Wl,-rpath,$(OPENSSL_LIBDIR) -lcrypto -pthread
INCLUDES = -I$(OPENSSL_INCLUDEDIR) -I$(LIBCRYPTOSEC_INCLUDEDIR) -I$(LIBP11_INCLUDEDIR)

########### OBJECTS ##################################
SRCS += $(wildcard *.cpp)
OBJS += $(SRCS:.cpp=.o)

########### AUX TARGETS ##############################
%.o: %.cpp
	$(CC) $(CPPFLAGS) $(DEFS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"

.comp: multisign.o to_sign.o
	$(CC) $(CPPFLAGS) $(DEFS) -o mltsgn multisign.o $(LIBS)
	$(CC) $(CPPFLAGS) $(DEFS) -o to_sign to_sign.o $(LIBS)
	@echo 'Build complete!'

########### TARGETS ##################################

all: .comp

clean:
	rm -rf *.o mltsgn to_sign