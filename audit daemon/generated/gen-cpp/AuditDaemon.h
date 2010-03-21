/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */
#ifndef AuditDaemon_H
#define AuditDaemon_H

#include <TProcessor.h>
#include "daemon_types.h"



class AuditDaemonIf {
 public:
  virtual ~AuditDaemonIf() {}
  virtual bool ping() = 0;
  virtual void notify(const Message& msg) = 0;
};

class AuditDaemonNull : virtual public AuditDaemonIf {
 public:
  virtual ~AuditDaemonNull() {}
  bool ping() {
    bool _return = false;
    return _return;
  }
  void notify(const Message& /* msg */) {
    return;
  }
};

class AuditDaemon_ping_args {
 public:

  AuditDaemon_ping_args() {
  }

  virtual ~AuditDaemon_ping_args() throw() {}


  bool operator == (const AuditDaemon_ping_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const AuditDaemon_ping_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const AuditDaemon_ping_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class AuditDaemon_ping_pargs {
 public:


  virtual ~AuditDaemon_ping_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class AuditDaemon_ping_result {
 public:

  AuditDaemon_ping_result() : success(0) {
  }

  virtual ~AuditDaemon_ping_result() throw() {}

  bool success;

  struct __isset {
    __isset() : success(false) {}
    bool success;
  } __isset;

  bool operator == (const AuditDaemon_ping_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const AuditDaemon_ping_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const AuditDaemon_ping_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class AuditDaemon_ping_presult {
 public:


  virtual ~AuditDaemon_ping_presult() throw() {}

  bool* success;

  struct __isset {
    __isset() : success(false) {}
    bool success;
  } __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class AuditDaemon_notify_args {
 public:

  AuditDaemon_notify_args() {
  }

  virtual ~AuditDaemon_notify_args() throw() {}

  Message msg;

  struct __isset {
    __isset() : msg(false) {}
    bool msg;
  } __isset;

  bool operator == (const AuditDaemon_notify_args & rhs) const
  {
    if (!(msg == rhs.msg))
      return false;
    return true;
  }
  bool operator != (const AuditDaemon_notify_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const AuditDaemon_notify_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class AuditDaemon_notify_pargs {
 public:


  virtual ~AuditDaemon_notify_pargs() throw() {}

  const Message* msg;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class AuditDaemonClient : virtual public AuditDaemonIf {
 public:
  AuditDaemonClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  AuditDaemonClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool ping();
  void send_ping();
  bool recv_ping();
  void notify(const Message& msg);
  void send_notify(const Message& msg);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class AuditDaemonProcessor : virtual public ::apache::thrift::TProcessor {
 protected:
  boost::shared_ptr<AuditDaemonIf> iface_;
  virtual bool process_fn(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, std::string& fname, int32_t seqid);
 private:
  std::map<std::string, void (AuditDaemonProcessor::*)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*)> processMap_;
  void process_ping(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot);
  void process_notify(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot);
 public:
  AuditDaemonProcessor(boost::shared_ptr<AuditDaemonIf> iface) :
    iface_(iface) {
    processMap_["ping"] = &AuditDaemonProcessor::process_ping;
    processMap_["notify"] = &AuditDaemonProcessor::process_notify;
  }

  virtual bool process(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot);
  virtual ~AuditDaemonProcessor() {}
};

class AuditDaemonMultiface : virtual public AuditDaemonIf {
 public:
  AuditDaemonMultiface(std::vector<boost::shared_ptr<AuditDaemonIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~AuditDaemonMultiface() {}
 protected:
  std::vector<boost::shared_ptr<AuditDaemonIf> > ifaces_;
  AuditDaemonMultiface() {}
  void add(boost::shared_ptr<AuditDaemonIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  bool ping() {
    uint32_t sz = ifaces_.size();
    for (uint32_t i = 0; i < sz; ++i) {
      if (i == sz - 1) {
        return ifaces_[i]->ping();
      } else {
        ifaces_[i]->ping();
      }
    }
  }

  void notify(const Message& msg) {
    uint32_t sz = ifaces_.size();
    for (uint32_t i = 0; i < sz; ++i) {
      ifaces_[i]->notify(msg);
    }
  }

};



#endif