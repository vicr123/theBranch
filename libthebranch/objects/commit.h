#ifndef COMMIT_H
#define COMMIT_H

#include "forward_declares.h"
#include <QObject>

class CommitModel;
struct CommitPrivate;
class Commit : public QObject,
               public tbSharedFromThis<Commit> {
        Q_OBJECT
    public:
        ~Commit();

        bool equal(CommitPtr other);

        QString commitMessage();
        QString commitHash();
        QString shortCommitHash();
        QString authorName();

        QList<CommitPtr> parents();

    signals:

    protected:
        friend CommitModel;
        friend Repository;
        friend Branch;
        static CommitPtr commitForLgCommit(LGCommitPtr commit);
        LGCommitPtr gitCommit();

    private:
        explicit Commit(QObject* parent = nullptr);
        CommitPrivate* d;
};

typedef QSharedPointer<Commit> CommitPtr;

#endif // COMMIT_H
