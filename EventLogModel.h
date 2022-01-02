#include <qqml.h>
#include <QAbstractTableModel>

class EventLogModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void getEventLog(QString timeShift = "-100 years");
    Q_INVOKABLE QStringList getPictureUrl(int recordId);


private:
    QVector<QString> m_headers;
    QVector< QVector<QString> > m_data;
    int m_sizeX=0;
    int m_sizeY=0;
};
