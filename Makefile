

# Directories
SRC = src
BUILD = build
BIN = bin

# Files
SRCS = $(shell find $(notdir $(SRC)) | grep "\.c")
OBJECTS = $(patsubst %.c,%.o,$(subst $(notdir $(SRC)),$(notdir $(BUILD)),$(SRCS)))
SUBSTRUCT = $(sort $(dir $(OBJECTS)))
BINARY = $(BIN)/$(notdir $(CURDIR))


# Toolvars
CC = gcc
CFLAGS = -c -g
CPPFLAGS =

LD = gcc
LDFLAGS = -g
LDPFLAGS =

.PHONY: all
all: init compile

.PHONY: compile
compile: $(OBJECTS) $(BINARY)

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $< -o $@ $(CPPFLAGS)	

$(BINARY): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LDPFLAGS)

.PHONY: init
init: | $(BIN) $(BUILD) $(SUBSTRUCT)

%:
	mkdir $@


.PHONY: clean
clean:
	rm -rf $(BUILD)
	rm -rf $(BIN)
