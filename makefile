STD = -std=c++17
MAIN = Multithreading_26.9.1_SC-04

thread : $(MAIN).cpp threading.cpp
	g++ $(STD) -o $@ -pthread $(MAIN).cpp threading.cpp

exec:
	./thread
