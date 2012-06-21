#ifndef SSHCONNECTION_H
#define SSHCONNECTION_H

#include <QLocalSocket>

class SSHConnection : public QObject
{
    Q_OBJECT

public:
    //! Protocol message types
    enum MessageType {
	// 3.1 Requests from client to agent for protocol 1 key operations.
	RequestRsaIdentities = 1,           /**< SSH_AGENTC_REQUEST_RSA_IDENTITIES */
	RsaChallange = 3,                   /**< SSH_AGENTC_RSA_CHALLENGE */
	AddRsaIdentity = 7,                 /**< SSH_AGENTC_ADD_RSA_IDENTITY */
	RemoveRsaIdentity = 8,              /**< SSH_AGENTC_REMOVE_RSA_IDENTITY */
	RemoveAllRsaIdentities = 9,         /**< SSH_AGENTC_REMOVE_ALL_RSA_IDENTITIES */
	AddRsaIdContrained = 24,            /**< SSH_AGENTC_ADD_RSA_ID_CONSTRAINED */

	// 3.2 Requests from client to agent for protocol 2 key operations.
	RequestIdentities = 11,             /**< SSH2_AGENTC_REQUEST_IDENTITIES */
	SignRequest = 13,                   /**< SSH2_AGENTC_SIGN_REQUEST */
	AddIdentity = 17,                   /**< SSH2_AGENTC_ADD_IDENTITY */
	RemoveIdentity = 18,                /**< SSH2_AGENTC_REMOVE_IDENTITY */
	RemoveAllIdentities = 19,           /**< SSH2_AGENTC_REMOVE_ALL_IDENTITIES */
	AddIdConstrained = 25,              /**< SSH2_AGENTC_ADD_ID_CONSTRAINED */

	// 3.3 Key-type independent requests from client to agent.
	AddSmartCardKey = 20,               /**< SSH_AGENTC_ADD_SMARTCARD_KEY */
	RemoveSmartCardKey = 21,            /**< SSH_AGENTC_REMOVE_SMARTCARD_KEY */
	Lock = 22,                          /**< SSH_AGENTC_LOCK */
	Unlock = 23,                        /**< SSH_AGENTC_UNLOCK */
	AddSmartCardKeyConstrained = 26,    /**< SSH_AGENTC_ADD_SMARTCARD_KEY_CONSTRAINED */

	// 3.4 Generic replies from agent to client.
	Failure = 5,                        /**< SSH_AGENT_FAILURE */
	Success = 6,                        /**< SSH_AGENT_SUCCESS */

	// 3.5 Replies from agent to client for protocol 1 key operations.
	RsaIdentitiesAnswer = 2,            /**< SSH_AGENT_RSA_IDENTITIES_ANSWER */
	RsaResponse = 4,                    /**< SSH_AGENT_RSA_RESPONSE */

	// 3.6 Replies from agent to client for protocol 2 key operations.
	IdentitiesAnswer = 12,              /**< SSH2_AGENT_IDENTITIES_ANSWER */
	SignResponse = 14                   /**< SSH2_AGENT_SIGN_RESPONSE */
    };

    //! SSH Key constraint identifiers
    enum ContraintIdentifier {
	ConstrainLifetime = 1,   /**< SSH_AGENT_CONSTRAIN_LIFETIME */
	ConstrainConfirm = 2     /**< SSH_AGENT_CONSTRAIN_CONFIRM */
    };


    explicit SSHConnection(QLocalSocket *socket, QObject *parent = 0);
    virtual ~SSHConnection();

private:
    bool processMessage();
    bool processRequestRsaIdentities();
    bool processRsaChallange();
    bool processAddRsaIdentity();
    bool processRemoveRsaIdentity();
    bool processRemoveAllRsaIdentities();
    bool processAddRsaIdContrained();
    bool processRequestIdentities();
    bool processSignRequest();
    bool processAddIdentity();
    bool processRemoveIdentity();
    bool processRemoveAllIdentities();
    bool processAddIdConstrained();
    bool processAddSmartCardKey();
    bool processRemoveSmartCardKey();
    bool processLock();
    bool processUnlock();
    bool processAddSmartCardKeyConstrained();

    QLocalSocket *m_socket;         // Underlying socket
    quint32 m_messageSize;          // Current message size
    QByteArray m_messagePayload;    // Current message payload
    QByteArray m_buffer;            // Buffer for current message data

private slots:
    void handleSocketError(QLocalSocket::LocalSocketError socketError);
    void handleReadyRead();
    void handleDisconnected();
    void handleStateChanged(QLocalSocket::LocalSocketState socketState);
};

#endif // SSHCONNECTION_H
