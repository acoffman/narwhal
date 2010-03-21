#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(int argc, const char **argv)
{
	try {
		sql::Driver * driver = get_driver_instance();
		/* Using the Driver to create a connection */
		std::auto_ptr< sql::Connection > con(driver->connect("localhost", "root", ""));

		std::auto_ptr< sql::Statement > stmt(con->createStatement());
    stmt->execute("use juggernaut_production"); 
		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT id, name FROM tasks ORDER BY id ASC"));
		while (res->next()) {
      cout << "id = '" << res->getInt("id") << "', name = '" <<  res->getString("name") << endl;
		}

	} catch (sql::SQLException &e) {
		/*
		The MySQL Connector/C++ throws three different exceptions:

		- sql::MethodNotImplementedException (derived from sql::SQLException)
		- sql::InvalidArgumentException (derived from sql::SQLException)
		- sql::SQLException (derived from std::runtime_error)
		*/
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		/* Use what() (derived from std::runtime_error) to fetch the error message */
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;

	}

}

