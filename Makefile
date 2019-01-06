INSTALL_DIR = ~/bin
APP_NAME = mailsam
src = $(wildcard src/*.cpp src/**/*.cpp)
obj = $(src:.cpp=.o)

#$(ccsrc:.cc=.o)

LDFLAGS = -lrt -lm -pthread -Llibraries -l boost_program_options

$(APP_NAME): $(obj)
	    $(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm src/*.o
	rm src/**/*.o

install: $(APP_NAME)
	mkdir -p $(INSTALL_DIR)
	cp $< $(INSTALL_DIR)/$(APP_NAME)

uninstall:
	rm -f -R $(INSTALL_DIR)/$(APP_NAME)
