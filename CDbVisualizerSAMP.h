#ifndef CDBVISUALIZERSAMP_H
#define CDBVISUALIZERSAMP_H

#include <QMainWindow>
#include <QTableView>
#include <QHeaderView>
#include <QtSql/QSqlRelationalTableModel>
#include <memory>
#include <QCheckBox>

namespace Ui {
class CDbVisualizerSAMP;
}

class CDbVisualizerSAMP : public QMainWindow
{
    Q_OBJECT

public:
    explicit CDbVisualizerSAMP(QWidget *parent = 0);
    ~CDbVisualizerSAMP();


    bool init();
    bool connect();
    QTableView *createView(const QString &title, QSqlTableModel *model) const;
    void initializeModel(QSqlRelationalTableModel *model, QString tableName);


    void getData(QString tableName);
    void getTreatmentData();
    void getControlData();
    void getMeasuresData();
    void getProductionData();
    void setModel(QSqlQueryModel *model, QSqlQuery *query) const;
    void getTableToDisplay(QString tableName, int event) const;
    void getCheckBoxState(QCheckBox *currentCheckBox, QCheckBox *toUncheck, QCheckBox *toUncheck2, QCheckBox *toUncheck3) const;


private slots:

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

private:
    Ui::CDbVisualizerSAMP *ui;
};

#endif // CDBVISUALIZERSAMP_H
