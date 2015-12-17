test.out:
	g++ -DUNIT_TEST -o test.out dir.cpp -std=c++11
clean:
	rm -f test.out
