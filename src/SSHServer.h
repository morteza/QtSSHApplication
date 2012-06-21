#ifndef SSHSERVER_H
#define SSHSERVER_H

#include <QLocalSocket>
#include <QLocalServer>
#include "SSHConnection.h"

class SSHServer : public QLocalServer
{
    Q_OBJECT
public:
    explicit SSHServer(QObject *parent = 0);
    virtual ~SSHServer();

private slots:
    void handleNewConnection();

private:
    //! active connections to this server
    QSet<SSHConnection *> m_connections;
};

#endif // SSHSERVER_H
