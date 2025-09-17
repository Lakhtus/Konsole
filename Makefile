CXX      ?= g++
SRC      := $(wildcard src/*.cc)
HEADERS  := $(wildcard src/*.h)
TARGET   := main.exe

# Flags
DEBUG_CXXFLAGS   = -Wall -Wextra -std=c++17 -O0 -g -pthread -Ivendor -Isrc -I.
RELEASE_CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -pthread -Ivendor -Isrc -I.
LDFLAGS          = -lgdi32 -pthread

# Config-specific dirs
DEBUG_BUILDDIR   = build/debug
DEBUG_BINDIR     = bin/debug
RELEASE_BUILDDIR = build/release
RELEASE_BINDIR   = bin/release

# Map sources -> objects (strip src/)
DEBUG_OBJS   := $(patsubst src/%.cc,$(DEBUG_BUILDDIR)/%.o,$(SRC))
RELEASE_OBJS := $(patsubst src/%.cc,$(RELEASE_BUILDDIR)/%.o,$(SRC))

.PHONY: all debug release clean

all: release

# --- Debug build ---
debug: $(DEBUG_BINDIR)/$(TARGET)

$(DEBUG_BINDIR)/$(TARGET): $(DEBUG_OBJS)
	@if not exist "$(DEBUG_BINDIR)" mkdir "$(DEBUG_BINDIR)"
	$(CXX) $(DEBUG_CXXFLAGS) $^ -o "$@" $(LDFLAGS)

$(DEBUG_BUILDDIR)/%.o: src/%.cc $(HEADERS)
	@if not exist "$(DEBUG_BUILDDIR)" mkdir "$(DEBUG_BUILDDIR)"
	$(CXX) $(DEBUG_CXXFLAGS) -c "$<" -o "$@"


# --- Release build ---
release: $(RELEASE_BINDIR)/$(TARGET)

$(RELEASE_BINDIR)/$(TARGET): $(RELEASE_OBJS)
	@if not exist "$(RELEASE_BINDIR)" mkdir "$(RELEASE_BINDIR)"
	$(CXX) $(RELEASE_CXXFLAGS) $^ -o "$@" $(LDFLAGS)

$(RELEASE_BUILDDIR)/%.o: src/%.cc $(HEADERS)
	@if not exist "$(RELEASE_BUILDDIR)" mkdir "$(RELEASE_BUILDDIR)"
	$(CXX) $(RELEASE_CXXFLAGS) -c "$<" -o "$@"


# --- Clean ---
clean:
	@if exist build rmdir /S /Q build
	@if exist bin   rmdir /S /Q bin
