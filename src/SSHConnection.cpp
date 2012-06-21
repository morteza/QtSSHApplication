#include "SSHConnection.h"

SSHConnection::SSHConnection(QLocalSocket *socket, QObject *parent) :
    QObject(parent),
    m_socket(socket),
    m_messageSize(0),
    m_messagePayload(QByteArray()),
    m_buffer(QByteArray())
{
    Q_ASSERT(m_socket);
    m_socket->setParent(this);

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));

    connect(m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)),
	    this, SLOT(handleSocketError(QLocalSocket::LocalSocketError)));

    connect(m_socket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));

    connect(m_socket, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)),
	    this, SLOT(handleStateChanged(QLocalSocket::LocalSocketState)));

}

SSHConnection::~SSHConnection()
{
    m_socket->abort();
}

void SSHConnection::handleSocketError(QLocalSocket::LocalSocketError socketError)
{
    Q_UNUSED(socketError);
    Q_ASSERT(m_socket);
}

void SSHConnection::handleReadyRead()
{
    Q_ASSERT(m_socket);

    m_buffer.append(m_socket->readAll());

    if ( m_messageSize == 0 && (quint32)m_buffer.size() >= sizeof(quint32))
    {
	QDataStream(m_buffer) >> m_messageSize;
	m_buffer.chop(sizeof(quint32));
	Q_ASSERT(m_messageSize > 0);
    }

    if ( m_messageSize !=0 )
    {
	int remainedBytes = m_messageSize - m_messagePayload.size();
	m_messagePayload.append(m_buffer.right(remainedBytes));
	m_buffer.chop((remainedBytes));

	//! process the message
	if ((quint32)m_messagePayload.size() == m_messageSize) {
	    processMessage();
	    m_messagePayload.clear();
	    m_messageSize = 0;
	}

    }
}


bool SSHConnection::processMessage()
{
    quint8 type;
    QDataStream(m_messagePayload) >> type;

    switch (type) {
	case RequestRsaIdentities:
	    return processRequestRsaIdentities();
	case RsaChallange:
	    return processRsaChallange();
	case AddRsaIdentity:
	    return processAddRsaIdentity();
	case RemoveRsaIdentity:
	    return processRemoveRsaIdentity();
	case RemoveAllRsaIdentities:
	    return processRemoveAllRsaIdentities();
	case AddRsaIdContrained:
	    return processAddRsaIdContrained();
	case RequestIdentities:
	    return processRequestIdentities();
	case SignRequest:
	    return processSignRequest();
	case AddIdentity:
	    return processAddIdentity();
	case RemoveIdentity:
	    return processRemoveIdentity();
	case RemoveAllIdentities:
	    return processRemoveAllIdentities();
	case AddIdConstrained:
	    return processAddIdConstrained();
	case AddSmartCardKey:
	    return processAddSmartCardKey();
	case RemoveSmartCardKey:
	    return processRemoveSmartCardKey();
	case Lock:
	    return(processLock());
	case Unlock:
	    return(processUnlock());
	case AddSmartCardKeyConstrained:
	    return(processAddSmartCardKeyConstrained());
	default:
	    break;
    }
    return false;

}

bool SSHConnection::processRequestRsaIdentities()
{
    return false;
}

bool SSHConnection::processRsaChallange()
{
    return false;
}

bool SSHConnection::processAddRsaIdentity()
{
    return false;
}

bool SSHConnection::processRemoveRsaIdentity()
{
    return false;
}

bool SSHConnection::processRemoveAllRsaIdentities()
{
    return false;
}

bool SSHConnection::processAddRsaIdContrained()
{
    return false;
}

bool SSHConnection::processRequestIdentities()
{
    return false;
}

bool SSHConnection::processSignRequest()
{
    return false;
}

bool SSHConnection::processAddIdentity()
{
    return false;
}

bool SSHConnection::processRemoveIdentity()
{
    return false;
}

bool SSHConnection::processRemoveAllIdentities()
{
    return false;
}

bool SSHConnection::processAddIdConstrained()
{
    return false;
}

bool SSHConnection::processAddSmartCardKey()
{
    return false;
}

bool SSHConnection::processRemoveSmartCardKey()
{
    return false;
}

bool SSHConnection::processLock()
{
    return false;
}

bool SSHConnection::processUnlock()
{
    return false;
}

bool SSHConnection::processAddSmartCardKeyConstrained()
{
    return false;
}


void SSHConnection::handleSocketError(QLocalSocket::LocalSocketError socketError);
void SSHConnection::handleReadyRead();
void SSHConnection::handleDisconnected()
{
}
void SSHConnection::handleStateChanged(QLocalSocket::LocalSocketState socketState)
{
}
