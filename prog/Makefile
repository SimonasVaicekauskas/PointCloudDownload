CPP= g++
CPPFLAGS = -c -Wall -fpic -m64 -O2 -std=c++0x
LN= g++
AR=ar
LDFLAGS= -m64
SYSLIBS= -ldl -lnsl -lm -lpthread -lrt
DEFINES= 

INCLUDES= -I. -I$(FASTRTPSHOME)/include

LIBS = -L$(FASTRTPSHOME)/lib -L$(FASTRTPSHOME)/lib/x64Linux2.6gcc -lboost_system -lboost_thread -lfastcdr -lfastrtps -lboost_system -lboost_thread -lboost_date_time $(SYSLIBS)

DIRECTORIES= output.dir output/x64Linux2.6gcc.dir lib.dir lib/x64Linux2.6gcc.dir bin.dir bin/x64Linux2.6gcc.dir

all: $(DIRECTORIES) hallo halloPublisherSubscriber


hallo_TARGET= lib/x64Linux2.6gcc/libhallo.so
hallo_TARGET_Z= lib/x64Linux2.6gcc/libhallo.a

hallo_CLIENT_EXAMPLE_TARGET= bin/x64Linux2.6gcc/halloPublisherSubscriber
hallo_COMMON_SRC_CXXFILES = hallo.cxx

hallo_COMMON_SRC_CPPFILES=

hallo_CLIENTSOURCES = halloPubSubTypes.cxx \
	halloPublisher.cxx \
	halloSubscriber.cxx \
	halloPubSubMain.cxx

hallo_COMMONOBJS    = $(hallo_COMMON_SRC_CXXFILES:%.cxx=output/x64Linux2.6gcc/%.o) $(hallo_COMMON_SRC_CPPFILES:%.cpp=output/x64Linux2.6gcc/%.o)

hallo_CLIENTOBJS    = $(hallo_CLIENTSOURCES:%.cxx=output/x64Linux2.6gcc/%.o)

halloOBJS+= $(hallo_COMMONOBJS) $(hallo_CLIENTOBJS)
OBJS+= $(halloOBJS)

$(hallo_TARGET): $(hallo_COMMONOBJS)
	$(LN) $(LDFLAGS) -shared -o $(hallo_TARGET) $(hallo_COMMONOBJS) $(LIBS) -Llib/x64Linux2.6gcc 

$(hallo_TARGET_Z): $(hallo_COMMONOBJS)
	$(AR) -cru $(hallo_TARGET_Z) $(hallo_COMMONOBJS)

$(hallo_CLIENT_EXAMPLE_TARGET): $(halloOBJS) lib/x64Linux2.6gcc/libhallo.a 
	$(LN) $(LDFLAGS) -o $@ $(halloOBJS) -Wl,-Bstatic -Llib/x64Linux2.6gcc -lhallo  -Wl,-Bdynamic $(LIBS)

halloPublisherSubscriber : $(hallo_CLIENT_EXAMPLE_TARGET)
hallo: $(hallo_TARGET) $(hallo_TARGET_Z) halloPublisherSubscriber

output/x64Linux2.6gcc/%.o:%.cxx
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

output/x64Linux2.6gcc/%.o:%.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

.PHONY: hallo halloPublisherSubscriber

clean:
	@rm -f $(OBJS)

%.dir : 
	@echo "Checking directory $*"
	@if [ ! -d $* ]; then \
		echo "Making directory $*"; \
		mkdir -p $* ; \
	fi;
