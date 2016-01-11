###############################################################
# File Name     : Makefile
# Author        : skytrails
# Email         : skytrails@163.com
# Create Time   : 2015-09-20 17:51
################################################################
# 

_MK_DEBUG = 0
ifeq ($(_MK_DEBUG), 1)
	CC := @g++
	MKDIR := @mkdir
else
	CC := g++
	MKDIR := mkdir
endif
RM = rm -f
BIN = $(shell pwd)/bin
UTIL_LIB = $(BIN)/libUtil.so
PUB_LIB = $(BIN)/libPubClass.so
BUS_LIB = $(BIN)/libBusiness.so
TARGET=$(BIN)/startapp.1.0
TEST=$(BIN)/tst
#CFLAGS = -O2 -I$(HOME)/back_trunk/src/
CFLAGS = -O2 -I./src/
export OBJSDIR=$(shell pwd)/objs
#----------------------------test
TEST_DIRS = src/test
TEST_FILES = $(foreach dir, $(TEST_DIRS), $(wildcard $(dir)/*.cpp))
TEST_OBJS = $(patsubst src%, objs%, $(patsubst %.cpp, %.o, $(TEST_FILES)))
#----------------------------util
UTILDIRS = src/util\
src/util/deamon 
PUBFILES = $(foreach dir, $(UTILDIRS), $(wildcard $(dir)/*.cpp $(dir)/*.c))
UTIL_DEP = $(patsubst src%, objs%, $(patsubst %.cpp, %.d, $(patsubst %.c, %.cpp, $(PUBFILES))))
UTIL_DDIRS = $(patsubst src%, objs%, $(UTILDIRS))
PUBOBJS = $(patsubst %.d, %.o, $(UTIL_DEP))
#---------------------------util end
#---------------------------pubclass
PUB_DIRS = src/pubclass\
src/pubclass/log
PUB_FILES = $(foreach dir, $(PUB_DIRS), $(wildcard $(dir)/*.cpp))
PUB_OBJS_DIRS = $(patsubst src%, objs%, $(PUB_FILES))
PUB_OBJS = $(patsubst src%, objs%, $(patsubst %.cpp, %.o, $(PUB_FILES)))
PUB_DEP = $(patsubst %.o, %.d, $(PUB_OBJS))
#---------------------------pubclass end

#---------------------------platform begin
PLATFORM_DIRS = src/platform\
src/platform/SNServer
PLATFORM_FILES = $(foreach dir, $(PLATFORM_DIRS), $(wildcard $(dir)/*.cpp))
PLATFORM_OBJS_DIRS = $(patsubst src%, objs%, $(PLATFORM_FILES))
PLATFORM_OBJS = $(patsubst src%, objs%, $(patsubst %.cpp, %.o, $(PLATFORM_FILES)))
PLATFORM_DEP = $(patsubst %.o, %.d, $(PLATFORM_OBJS))
#---------------------------platform end

#---------------------------business begin
BUS_DIRS = src/business\
src/business/client\
src/business/service\
src/business/SNServer
BUS_FILES = $(foreach dir, $(BUS_DIRS), $(wildcard $(dir)/*.cpp))
BUS_OBJS_DIRS = $(patsubst src%, objs%, $(BUS_DIRS))
BUS_OBJS = $(patsubst src%, objs%, $(patsubst %.cpp, %.o, $(BUS_FILES)))
BUS_DEP = $(patsubst %.o, %.d, $(BUS_OBJS))
#---------------------------business end
all:$(UTIL_DEP) $(PUB_DEP) $(BUS_DEP) $(UTIL_LIB) $(PUB_LIB) $(BUS_LIB) $(TARGET) $(TEST)
	@ln -sf $(TARGET) $(BIN)/exp
	@ln -sf $(TARGET) $(BIN)/client
	@ln -sf $(TARGET) $(BIN)/service
	@ln -sf $(TARGET) $(BIN)/SNService
	@ln -sf $(TARGET) $(BIN)/SNClient
#	@ctags -R  --sort=yes --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++

$(PUB_DEP):objs/%.d:src/%.cpp
	$(MKDIR) -p ./bin
	$(MKDIR) -p $(dir $@)
	$(CC) -MM $< |\
	sed "$ s+$(patsubst %.d,%.o, $(notdir $@))+$(patsubst %.d,%.o,$@)+g" |\
	sed '$$ a\\tg++ -fPIC -shared -c -o $(patsubst %.d, %.o, $@) $<' > $@

$(UTIL_DEP):objs/%.d:src/%.cpp
	$(MKDIR) -p ./bin
	$(MKDIR) -p $(dir $@)
	$(CC) -MM $< |\
	sed "$ s+$(patsubst %.d,%.o, $(notdir $@))+$(patsubst %.d,%.o,$@)+g" |\
	sed '$$ a\\tg++ -fPIC -shared -c -o $(patsubst %.d, %.o, $@) $<' > $@

$(BUS_DEP):objs/%.d:src/%.cpp
	$(MKDIR) -p ./bin
	$(MKDIR) -p $(dir $@)
	$(CC) $(CFLAGS) -MM $< |\
	sed "$ s+$(patsubst %.d,%.o, $(notdir $@))+$(patsubst %.d,%.o,$@)+g" |\
	sed '$$ a\\tg++ $(CFLAGS) -fPIC -shared -c -o $(patsubst %.d, %.o, $@) $<' > $@
#-----库
$(UTIL_LIB):$(PUBOBJS)
	$(CC) -shared -fPIC $< -o $@ $(CFLAGS)

$(PUB_LIB):$(PUB_OBJS)
	$(CC) -shared -fPIC $^ -o $@ $(CFLAGS) -L$(BIN) -lUtil

$(BUS_LIB):$(BUS_OBJS)
	$(CC) -shared -fPIC $^ -o $@ $(CFLAGS) -L$(BIN) -lPubClass -lUtil

$(TARGET):src/startApp.cpp
	#$(CC) -rdynamic $< -o $@ -ldl -L$(BIN) -lPubClass -lUtil
	$(CC) $< -o $@ -L$(BIN) -ldl -lUtil

-include $(UTIL_DEP)
-include $(PUB_DEP)
-include $(BUS_DEP)

.PHONY : clean touch
$(TEST):$(TEST_FILES)
	$(CC) $^ -o $@ -L$(BIN) -lPubClass -lUtil
clean:
	find objs/ -type f | xargs rm -f;
	find bin/ -type f | xargs rm -f;
touch:

