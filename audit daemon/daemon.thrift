struct Message {
  1: i32 userid,
  2: string msg
}

service AuditDaemon {
  /**
  * Returns true if the server is alive and running
  */
  bool ping(),

  /**
  * Send a message to the audit daemon server to update a user
  */
  oneway void notify(1: Message msg)
}
