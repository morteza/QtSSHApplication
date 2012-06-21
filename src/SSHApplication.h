#ifndef SSHAPPLICATION_H
#define SSHAPPLICATION_H

#include <QCoreApplication>
#include <QSocketNotifier>
#include <signal.h>
#include <sys/socket.h>
#include "SSHConnection.h"
#include "SSHServer.h"

class SSHApplication : public QCoreApplication {
    Q_OBJECT

public:
    explicit SSHApplication(int argc, char **argv);
    virtual ~SSHApplication();
    int exec();

public slots:
    void handleSigInt();

private:
    SSHServer *m_server;

private slots:
    void closeServer();

protected:

    //! Sockets to be used for communication between POSIX signal handler and Qt
    static int m_sigIntSockets[2];

    //! POSIX signal handler for the SIGINT
    static void handlePosixSigInt(int);

    //! used listen for the SIGINT
    QSocketNotifier *m_sigIntSocketNotifier;

};

#endif // SSHAPPLICATION_H
