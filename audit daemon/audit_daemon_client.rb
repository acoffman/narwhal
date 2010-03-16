require 'rubygems'
require 'thrift'
require File.dirname(__FILE__) + '/generated/gen-rb/audit_daemon'
 
include AuditDaemon

class DaemonClient
  def initialize
      @transport = Thrift::BufferedTransport.new(Thrift::Socket.new('127.0.0.1', 9090))
      protocol = Thrift::BinaryProtocol.new(@transport)
      @client = Client.new(protocol)
      
      @transport.open()
  end

  def send(message)
    @client.notify(message)
  end

  def close
    @transport.close()
  end

  def ping
    @client.ping
  end
end

msg = Message.new
msg.msg = "Hi brent"

client = DaemonClient.new
client.send(msg)


