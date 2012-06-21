#include "SSHApplication.h"

SSHApplication::SSHApplication(int argc, char **argv) : QCoreApplication(argc, argv)
{

    setApplicationName("qt-ssh-application");
    setApplicationVersion("1.0");
    setOrganizationName("UNINOVA-CA3");

    this->m_server = new SSHServer();


    //! Create the UNIX socket pair to handle POSIX <-> Qt signals
    socketpair(AF_UNIX, SOCK_STREAM, 0, m_sigIntSockets);


    //! Create the socket notifier to handle POSIX <-> Qt signals
    m_sigIntSocketNotifier = new QSocketNotifier(m_sigIntSockets[1], QSocketNotifier::Read, this);

    connect(this, SIGNAL(aboutToQuit()), this, SLOT(closeServer()));
    connect(m_sigIntSocketNotifier, SIGNAL(activated(int)), this, SLOT(handleSigInt()));

    //! Install SIGINT (^C) signal
    struct sigaction sigIntAction;
    sigIntAction.sa_handler = handlePosixSigInt;
    sigemptyset(&sigIntAction.sa_mask);
    sigIntAction.sa_flags = SA_RESTART;

    sigaction(SIGINT, &sigIntAction, NULL);

   }

SSHApplication::~SSHApplication()
{
    delete m_sigIntSocketNotifier;
    delete m_server;

    close(this->m_sigIntSockets[0]);
    close(this->m_sigIntSockets[1]);

}

int SSHApplication::exec()
{
    return QCoreApplication::exec();
}

void SSHApplication::closeServer()
{
    m_server->close();
}

//! to be used for static members below
int SSHApplication::m_sigIntSockets[2];

void SSHApplication::handlePosixSigInt(int)
{
    char sigIntChar = 1;
    ssize_t n = write(m_sigIntSockets[0], &sigIntChar, sizeof(sigIntChar));
    Q_UNUSED(n);
}

void SSHApplication::handleSigInt()
{
    char sigIntChar;
    m_sigIntSocketNotifier->setEnabled(false);
    ssize_t n = read(m_sigIntSockets[1], &sigIntChar, sizeof(sigIntChar));
    Q_UNUSED(n);
    m_sigIntSocketNotifier->setEnabled(true);
}
