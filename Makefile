# ============================================================
# Makefile — Smart Transport & Navigation System
# ============================================================
# Usage:
#   make          → Compile the project
#   make run      → Compile and run
#   make clean    → Remove compiled files
# ============================================================

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = SmartTransport

# Source files (order doesn't matter for compilation)
SRCS = main.cpp \
       Location.cpp \
       City.cpp \
       Stop.cpp \
       TransportNetwork.cpp \
       DijkstraFinder.cpp \
       BFSFinder.cpp \
       Trie.cpp

# Object files (auto-generated from source files)
OBJS = $(SRCS:.cpp=.o)

# Header-only files (for dependency tracking)
HEADERS = Location.h City.h Stop.h TransportNetwork.h \
          RouteFinder.h DijkstraFinder.h BFSFinder.h \
          Trie.h Stack.h HashMap.h

# ============================================================
# Build Rules
# ============================================================

# Default target: build the executable
$(TARGET): $(OBJS)
	@echo "🔗 Linking $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "✅ Build successful! Run with: ./$(TARGET)"

# Compile each .cpp to .o
%.o: %.cpp $(HEADERS)
	@echo "⚙️  Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile and run
run: $(TARGET)
	@echo ""
	@./$(TARGET)

# Clean up compiled files
clean:
	@echo "🧹 Cleaning up..."
	rm -f $(OBJS) $(TARGET)
	@echo "✅ Clean complete."

# Phony targets (not actual files)
.PHONY: clean run
