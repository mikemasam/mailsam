INSTALL_DIR = ~/bin
APP_NAME = mailsam
src = $(wildcard src/*.cpp src/**/*.cpp)
obj = $(src:.cpp=.o)

#$(ccsrc:.cc=.o)  
sql_libs_s = -l:libmysqlclient.a -l:libmysqlcppconn-static.a
sql_libs = -lmysqlcppconn
boost_libs_s = -l:libboost_program_options.a -l:libboost_system.a -l:libboost_regex.a
boost_libs = -lboost_program_options -lboost_system -lboost_regex
libs = -l:libmailio.a -lcrypto -lssl -lpthread
static = -static
lib_dir = -Llibraries


LDFLAGS = -lrt -lm $(libs) $(lib_dir) $(sql_libs) $(boost_libs) 
CXXFLAGS = -Wall -g
#-O2 



$(APP_NAME): $(obj)
	    $(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm src/**/*.o

install: $(APP_NAME)
	mkdir -p $(INSTALL_DIR)
	cp $< $(INSTALL_DIR)/$(APP_NAME)

uninstall:
	rm -f -R $(INSTALL_DIR)/$(APP_NAME)
