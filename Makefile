INSTALL_DIR = ~/bin
APP_NAME = mailsam
src = $(wildcard src/*.cpp src/**/*.cpp)
obj = $(src:.cpp=.o)

#$(ccsrc:.cc=.o)

LDFLAGS = -lrt -lm -pthread -lboost_program_options -lmysqlcppconn

$(APP_NAME): $(obj)
	    $(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm src/**/*.o

install: $(APP_NAME)
	mkdir -p $(INSTALL_DIR)
	cp $< $(INSTALL_DIR)/$(APP_NAME)

uninstall:
	rm -f -R $(INSTALL_DIR)/$(APP_NAME)
