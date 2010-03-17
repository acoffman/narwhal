compile = g++

driver:
	$(compile) -I$$BOOST_ROOT -I/usr/local/include/cppconn/ -I/usr/local/include/thrift/ generated/gen-cpp/*.cpp AuditDaemon_server.cpp -o server -lmysqlcppconn -lthrift

.PHONY: clean
clean: 
	rm  server

