#ifndef CDBVISUALIZERSAMP_H
#define CDBVISUALIZERSAMP_H

#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QtWidgets>
#include <QtSql>
#include <QSqlQuery>

class CDbVisualizerSAMP
{
public:
    CDbVisualizerSAMP();
    void init();
    bool connect();
    QTableView *createView(const QString &title, QSqlTableModel *model) const;
    void initializeModel(QSqlRelationalTableModel *model);


    void getTreatmentData();
    void getControlData();
    void getMeasuresData();
    void getProductionData();

std::shared_ptr<CDbVisualizerSAMP> m_dbVisualizer;

private:





};

#endif // CDBVISUALIZERSAMP_H
