#include "SSHServer.h"

SSHServer::SSHServer(QObject *parent) : QLocalServer(parent)
{
    connect(this, SIGNAL(newConnection()), SLOT(handleNewConnection()));
}

SSHServer::~SSHServer()
{
}

void SSHServer::handleNewConnection()
{
    QLocalSocket *socket = nextPendingConnection();
    Q_ASSERT(socket);

    //! Create a new connection
    SSHConnection *connection = new SSHConnection(socket, this);
    this->m_connections.insert(connection);
}

