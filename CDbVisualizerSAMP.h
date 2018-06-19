#ifndef CDBVISUALIZERSAMP_H
#define CDBVISUALIZERSAMP_H

#include <QTableView>
#include <QSqlRelationalTableModel>
#include <memory>

class CDbVisualizerSAMP
{
public:
    CDbVisualizerSAMP();
    bool init();
    bool connect();
    QTableView *createView(const QString &title, QSqlTableModel *model) const;
    void initializeModel(QSqlRelationalTableModel *model, QString tableName);


    void getData(QString tableName);
    void getTreatmentData();
    void getControlData();
    void getMeasuresData();
    void getProductionData();

    //std::shared_ptr<CDbVisualizerSAMP> m_dbVisualizer;

private:


};
#endif // CDBVISUALIZERSAMP_H
