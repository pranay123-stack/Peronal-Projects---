all:           main algorithm_unit_tester mean_reversion_unit_tester momentum_unit_tester
comp_version = -std=c++0x
CC           = g++
TARGETS      = mean_reversion_unit_tester momentum_unit_tester algorithm_unit_tester main *.o
CFLAGS       = 

main:  main.cpp MeanReversion.o Momentum.o AlgorithmTester.o Portfolio.o Stock.o 
	$(CC)  $^ -o $@ -lcurl $(CFLAGS)

algorithm_unit_tester: algorithm_unit_tester.cpp Stock.o Portfolio.o AlgorithmTester.o
	$(CC) $^ -o $@ -lcurl $(CFLAGS)

momentum_unit_tester:  momentum_unit_tester.cpp Momentum.o AlgorithmTester.o Portfolio.o Stock.o 
	$(CC)  $^ -o $@ -lcurl $(CFLAGS)

mean_reversion_unit_tester: mean_reversion_unit_tester.cpp MeanReversion.o AlgorithmTester.o Portfolio.o Stock.o 
	$(CC)  $^ -o $@ -lcurl $(CFLAGS)

Momentum.o: Momentum.cpp Stock.o Portfolio.o AlgorithmTester.o 
	$(CC) -c $< -o $@ $(CFLAGS)

MeanReversion.o: MeanReversion.cpp Stock.o Portfolio.o AlgorithmTester.o 
	$(CC) -c $< -o $@ $(CFLAGS)

AlgorithmTester.o: AlgorithmTester.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

Portfolio.o: Portfolio.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

Stock.o: Stock.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(TARGETS)
