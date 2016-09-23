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

all: $(DIRECTORIES) smt smtPublisherSubscriber


smt_TARGET= lib/x64Linux2.6gcc/libsmt.so
smt_TARGET_Z= lib/x64Linux2.6gcc/libsmt.a

smt_CLIENT_EXAMPLE_TARGET= bin/x64Linux2.6gcc/smtPublisherSubscriber
smt_COMMON_SRC_CXXFILES = smt.cxx

smt_COMMON_SRC_CPPFILES=

smt_CLIENTSOURCES = smtPubSubTypes.cxx \
	smtPublisher.cxx \
	smtSubscriber.cxx \
	smtPubSubMain.cxx

smt_COMMONOBJS    = $(smt_COMMON_SRC_CXXFILES:%.cxx=output/x64Linux2.6gcc/%.o) $(smt_COMMON_SRC_CPPFILES:%.cpp=output/x64Linux2.6gcc/%.o)

smt_CLIENTOBJS    = $(smt_CLIENTSOURCES:%.cxx=output/x64Linux2.6gcc/%.o)

smtOBJS+= $(smt_COMMONOBJS) $(smt_CLIENTOBJS)
OBJS+= $(smtOBJS)

$(smt_TARGET): $(smt_COMMONOBJS)
	$(LN) $(LDFLAGS) -shared -o $(smt_TARGET) $(smt_COMMONOBJS) $(LIBS) -Llib/x64Linux2.6gcc 

$(smt_TARGET_Z): $(smt_COMMONOBJS)
	$(AR) -cru $(smt_TARGET_Z) $(smt_COMMONOBJS)

$(smt_CLIENT_EXAMPLE_TARGET): $(smtOBJS) lib/x64Linux2.6gcc/libsmt.a 
	$(LN) $(LDFLAGS) -o $@ $(smtOBJS) -Wl,-Bstatic -Llib/x64Linux2.6gcc -lsmt  -Wl,-Bdynamic $(LIBS)

smtPublisherSubscriber : $(smt_CLIENT_EXAMPLE_TARGET)
smt: $(smt_TARGET) $(smt_TARGET_Z) smtPublisherSubscriber

output/x64Linux2.6gcc/%.o:%.cxx
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

output/x64Linux2.6gcc/%.o:%.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

.PHONY: smt smtPublisherSubscriber

clean:
	@rm -f $(OBJS)

%.dir : 
	@echo "Checking directory $*"
	@if [ ! -d $* ]; then \
		echo "Making directory $*"; \
		mkdir -p $* ; \
	fi;
