compile = g++

driver:
	$(compile) -I$$BOOST_ROOT -I$$CPPCON -I$$THRIFT generated/gen-cpp/daemon_types.cpp generated/gen-cpp/daemon_constants.cpp generated/gen-cpp/AuditDaemon.cpp AuditDaemon_server.cpp -o server -lmysqlcppconn -lthrift

.PHONY: clean
clean: 
	rm  server

