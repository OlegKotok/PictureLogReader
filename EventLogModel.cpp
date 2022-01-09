/*!   FILENAME:  EventLogModel.cpp
 *    DESCRIPTION:
 *            Implementation of standart virtual function of QAbstractTableModel
 *            getEventLog - get data from database
 */

#include "EventLogModel.h"
#include <QDebug>
#include "DatabaseManager.h"

/// Number of column with the Details-info button
static const int st_kMoreInfoColumnNumber = 5;

/*! Function Description: Implementation of standart virtual function of QAbstractTableModel
 *
 * RETURN: int - current row count
 */
int EventLogModel::rowCount(const QModelIndex &) const
{
    return m_sizeY;
}

/*! Function Description: Implementation of standart virtual function of QAbstractTableModel
 *
 * RETURN:
 *     int - current column count
 *
 */
int EventLogModel::columnCount(const QModelIndex &) const
{
    return m_sizeX;
}

/*! Function Description: Get data of the cell by index
 *
 * INPUTS:
 * PARAMETERS:
 *     const QModelIndex &index - index of current cell
 *
 * OUTPUTS:
 * RETURN:
 *     QVariant - QString of the cell by index
 *
 */
QVariant EventLogModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
        case Qt::DisplayRole:
            if ( index.row() < m_data.size() && index.column() < m_data[index.row()].size() )
            {
                if (index.column() == st_kMoreInfoColumnNumber && !m_data[index.row()].at(index.column()).isEmpty())
                {
                    return "#MOREINFO"; /* special symbol to show button instead text */
                }

                return m_data[index.row()].at(index.column());
            }
            else
            {
                return QString("%1, %2").arg(index.column()).arg(index.row());
            }
        default:
            break;
    }

    return QVariant();
}


/*! Function Description: Implementation of standart virtual function of QAbstractTableModel
 *  RETURN:   QHash<int, QByteArray> - current qhash
 */
QHash<int, QByteArray> EventLogModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

/*! Function Description: Get names of columns of the table
 *
 * INPUTS:
 * PARAMETERS:
 *     int section - numbber of column
 *     Qt::Orientation orientation - Qt::Horizontal
 *     int role - current role
 *
 * OUTPUTS:
 * RETURN:
 *     QVariant - QString of the cell by index
 *
 */
QVariant EventLogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        qDebug()<<"return section "<<section<<" role="<<role;
        return (role < m_headers.size())?m_headers[section]:"";
    }
    return "";
}

/*!  Function Description: Send request to database and put  datas to the model
 *
 * INPUTS:
 * PARAMETERS:
 *     QString timeShift - time shift, '-1 day', '-1 month', etc.
 *                         starting from now and to some time ago
 *
 * USING:
 *      QVector< QVector<QString> > m_data - current model of the data
 *      QVector<QString> m_headers - column names
 *      int m_sizeY - number of rows
 *      int m_sizeY - number of columns
 */
void EventLogModel::getEventLog(QString timeShift)
{
    qDebug()<<"Getting log from now to "<<timeShift;
    beginResetModel();
    DatabaseManager::getInstance()->getEventLog(m_headers, m_data, timeShift);
    m_sizeY = m_data.size();
    m_sizeX = m_headers.size();
    qDebug()<<"Records: "<<m_sizeY;
    endResetModel();

    for (auto headerName: m_headers)
    {
        qDebug()<<headerName;
    }
}

/*! Function Description: Get picture url by record id
 *
 * INPUTS:
 * PARAMETERS:
 *     int id - record id in database
 * OUTPUTS:
 * RETURN:
 *     QStringList - the list of records
 */
QStringList EventLogModel::getPictureUrl(int recordId)
{
    return  DatabaseManager::getInstance()->getUrlById(recordId);
}


