all:
	g++ -g -DDIR_TEST -o dir_test dir.cpp -std=c++11
	g++ -g -DLOG_TEST -o log_test log.cpp -std=c++11
	g++ -g -DCOMMAND_TEST -o command_test command.cpp dir.cpp log.cpp -std=c++11
	g++ -g -DCMD_GENERATOR_TEST -o cmd_generator_test cmd_generator.cpp log.cpp -std=c++11
	g++ -g -DSINGLE_THREAD_TEST -o single_thread_test single_thread.cpp cmd_generator.cpp command.cpp log.cpp dir.cpp -std=c++11
dir_test:
	g++ -g -DDIR_TEST -o dir_test dir.cpp -std=c++11
log_test:
	g++ -g -DLOG_TEST -o log_test log.cpp -std=c++11
command_test:
	g++ -g -DCOMMAND_TEST -o command_test command.cpp dir.cpp log.cpp -std=c++11
cmd_generator_test:
	g++ -g -DCMD_GENERATOR_TEST -o cmd_generator_test cmd_generator.cpp log.cpp -std=c++11
single_thread_test:
	g++ -g -DSINGLE_THREAD_TEST -o single_thread_test single_thread.cpp cmd_generator.cpp command.cpp log.cpp dir.cpp -std=c++11
clean:
	rm -f dir_test 
	rm -f log_test
	rm -f command_test
	rm -f cmd_generator_test
	rm -f single_thread_test
