compile = g++

driver:
	$(compile) -I$$BOOST_ROOT -I$$CPPCON -I$$THRIFT generated/gen-cpp/*.cpp AuditDaemon_server.cpp -o server -lmysqlcppconn -lthrift

.PHONY: clean
clean: 
	rm  server

