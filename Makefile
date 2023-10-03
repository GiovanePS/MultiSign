############# CC FLAGS ###############################
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
# SRCS += $(wildcard *.cpp)
# OBJS += $(SRCS:.cpp=.o)

########### AUX TARGETS ##############################
obj/%.o: src/%.cpp
	@mkdir -p ./obj
	$(CC) $(CPPFLAGS) $(DEFS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"

bin/mltsgn: obj/multisign.o
	@mkdir -p ./bin
	$(CC) $(CPPFLAGS) $(DEFS) -o "$@" "$<" $(LIBS)

bin/to_sign: obj/to_sign.o
	@mkdir -p ./bin
	$(CC) $(CPPFLAGS) $(DEFS) -o "$@" "$<" $(LIBS)

########### TARGETS ##################################

all: bin/mltsgn bin/to_sign
	@echo 'Build complete!'

clean:
	rm -rf ./obj ./bin