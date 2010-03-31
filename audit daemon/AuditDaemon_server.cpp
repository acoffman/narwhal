#include "generated/gen-cpp/AuditDaemon.h"
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>
#include "daemon support/handler.h"
#include "daemon support/stats_handler.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class AuditDaemonHandler : virtual public AuditDaemonIf {
 public:
  AuditDaemonHandler() {
  }

  bool ping() {
    printf("ping\n");
  }

  void notify(const Message& msg) {
    NotificationHandler n(100);
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<AuditDaemonHandler> handler(new AuditDaemonHandler());
  shared_ptr<TProcessor> processor(new AuditDaemonProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

