#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "branch.h"
#include "errorresponse.h"
#include "forward_declares.h"
#include "libthebranch_global.h"
#include <QObject>
#include <tpromise.h>

class BranchModel;
class CommitModel;
class CommitSnapIn;

struct RepositoryPrivate;
class RepositoryOperation;
class LIBTHEBRANCH_EXPORT Repository : public QObject {
        Q_OBJECT
    public:
        ~Repository();

        static RepositoryPtr cloneRepository(QString cloneUrl, QString directory, QVariantMap options);
        static tPromise<RepositoryPtr>* repositoryForDirectoryUi(QWidget* parent);
        static RepositoryPtr repositoryForDirectory(QString directory);
        static QString gitRepositoryRootForDirectory(QString directory);

        enum RepositoryState {
            Invalid,
            Cloning,
            Idle
        };
        RepositoryState state();

        QString stateDescription();
        QString stateInformationalText();
        int stateProgress();
        int stateTotalProgress();
        bool stateProvidesProgress();

        ReferencePtr head();
        QList<BranchPtr> branches(THEBRANCH::ListBranchFlags flags);

        ReferencePtr reference(QString name);

        ErrorResponse setHeadAndCheckout(ReferencePtr reference);

        void reloadRepositoryState();
        IndexPtr index();

        struct StatusItem {
                enum StatusFlag {
                    NoStatusFlag = 0x00,
                    Current = 0x01,
                    New = 0x02,
                    Modified = 0x04,
                    Deleted = 0x08,
                    TypeChanged = 0x10,
                    Renamed = 0x20,
                    Ignored = 0x40,
                    Conflicting = 0x80,

                    FirstStatusFlag = Current,
                    LastStatusFlag = Conflicting
                };

                QString path;
                int flags = NoStatusFlag;
        };

        QList<StatusItem> fileStatus();

        QString repositoryPath();

    signals:
        void stateChanged();
        void stateDescriptionChanged();
        void stateInformationalTextChanged();
        void stateProgressChanged();
        void repositoryUpdated();

    protected:
        friend CommitModel;
        friend BranchModel;
        friend Merge;
        friend CommitSnapIn;
        LGRepositoryPtr git_repository();

    private:
        explicit Repository(QObject* parent = nullptr);
        RepositoryPrivate* d;

        void putRepositoryOperation(RepositoryOperation* operation);
        void updateWatchedDirectories();
};

#endif // REPOSITORY_H
