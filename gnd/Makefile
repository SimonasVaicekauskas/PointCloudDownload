CPP = g++
CPPFLAGS = -c -Wall -fpic -O2 -std=c++1y
LN = g++
AR = ar
LDFLAGS =
SYSLIBS = -ldl -lnsl -lm -lpthread -lrt
DEFINES = 

INCLUDES = -I. -I$(FASTRTPSHOME)/include
LIBS = -L$(FASTRTPSHOME)/lib -lboost_system -lboost_thread -lfastcdr -lfastrtps -lboost_system -lboost_thread -lboost_date_time $(SYSLIBS)

DIRECTORIES = output.dir lib.dir bin.dir

all: $(DIRECTORIES) image_exchange

TARGET = lib/libimage_exchange.so
TARGET_Z = lib/libimage_exchange.a
CLIENT_TARGET = bin/image_exchange_client

COMMON_SOURCE = image_exchange.cxx
CLIENT_SOURCE = image_exchangePubSubTypes.cxx \
	image_exchangeMain.cxx \
	image_exchangeClientTest.cxx \
	image_exchangeClient.cxx

COMMON_OBJS = $(COMMON_SOURCE:%.cxx=output/%.o)
CLIENT_OBJS = $(CLIENT_SOURCE:%.cxx=output/%.o)

OBJS+= $(COMMON_OBJS) $(CLIENT_OBJS)

$(image_exchange_TARGET): $(COMMON_OBJS)
	$(LN) $(LDFLAGS) -shared -o $(TARGET) $(COMMON_OBJS) $(LIBS) -Llib

$(TARGET): $(COMMON_OBJS)
	$(LN) $(LDFLAGS) -shared -o $(TARGET) $(COMMON_OBJS) $(LIBS) -Llib

$(TARGET_Z): $(COMMON_OBJS)
	$(AR) -cr $(TARGET_Z) $(COMMON_OBJS)

$(CLIENT_TARGET): $(OBJS) lib/libimage_exchange.a
	$(LN) $(LDFLAGS) -o $@ $(OBJS) -Wl,-Bstatic -Llib -limage_exchange  -Wl,-Bdynamic $(LIBS)

image_exchangeClient : $(CLIENT_TARGET)
image_exchange: $(TARGET) $(TARGET_Z) image_exchangeClient

output/%.o:%.cxx
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

output/%.o:%.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

.PHONY: image_exchange

clean:
	@rm -f $(OBJS)

%.dir :
	@echo "Checking directory $*"
	@if [ ! -d $* ]; then \
		echo "Making directory $*"; \
		mkdir -p $* ; \
	fi;

