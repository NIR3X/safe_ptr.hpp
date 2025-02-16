CXX = clang++
CXXFLAGS = -std=c++17 -Wall -O3 -march=x86-64 -fno-rtti
LDFLAGS = -s -static

TEST_SRC = safe_ptr_test.cpp
TEST_DEST = safe_ptr_test.exe

build-test:
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_DEST) $(LDFLAGS)

test: build-test
	./$(TEST_DEST)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TEST_DEST)
