#ifndef BRANCHMODEL_H
#define BRANCHMODEL_H

#include "forward_declares.h"
#include <QAbstractListModel>

struct BranchModelPrivate;
class BranchModel : public QAbstractListModel {
        Q_OBJECT

    public:
        explicit BranchModel(QObject* parent = nullptr);
        ~BranchModel();

        enum BranchModelRole {
            Branch = Qt::UserRole,
            FakeRemoteName
        };

        // Basic functionality:
        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

        QModelIndex index(BranchPtr branch);

        void setFakePushBranchName(QString name);
        QStringList nonexistentRemoteNames() const;

        void setRepository(RepositoryPtr repo);
        void reloadData();
        void setBranchFlags(THEBRANCH::ListBranchFlags flags);

    private:
        BranchModelPrivate* d;

        // QAbstractItemModel interface
    public:
        QModelIndex index(int row, int column = 0, const QModelIndex& parent = QModelIndex()) const override;
};

#endif // BRANCHMODEL_H
