dir_test:
	g++ -g -DUNIT_TEST -o dir_test dir.cpp -std=c++11
log_test:
	g++ -g -DUNIT_TEST -o log_test log.cpp -std=c++11
command_test:
	g++ -g -DCOMMAND_TEST -o command_test command.cpp dir.cpp log.cpp -std=c++11
clean:
	rm -f dir_test 
	rm -f log_test
	rm -f command_test
