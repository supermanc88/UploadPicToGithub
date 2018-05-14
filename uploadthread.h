#ifndef UPLOADTHREAD_H
#define UPLOADTHREAD_H

#include <QThread>

class UploadThread : public QThread
{
public:
    UploadThread(QObject *parent);

    virtual void run();

};

#endif // UPLOADTHREAD_H
