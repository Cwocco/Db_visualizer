#include "CDbVisualizerSAMP.h"
#include "ui_CDbVisualizerSAMP.h"

#include <QtSql/QSqlDatabase>
//#include <QtSql/QSqlRelationalTableModel>
//#include <QTableView>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtSql/QSqlRelationalDelegate>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>

CDbVisualizerSAMP::CDbVisualizerSAMP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CDbVisualizerSAMP)
{
    ui->setupUi(this);
}

CDbVisualizerSAMP::~CDbVisualizerSAMP()
{
    delete ui;
}

bool CDbVisualizerSAMP::init()
{
    return connect();
}

bool CDbVisualizerSAMP::connect()
{
    qDebug() << "Connect";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/alexis.dacunha/Desktop/SAMP/release/samp.db");
    bool open = db.open();

    if (open)
        qDebug() << "Db correctly opened";
    else
        qDebug () << "Db open failed";

    return open;
}

void CDbVisualizerSAMP::setModel(QSqlQueryModel *model, QSqlQuery *query) const
{
    qDebug() << "setModel";

    model->setQuery(*query);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void CDbVisualizerSAMP::getTableToDisplay(QString tableName, int event) const
{
    qDebug() << "getTableToDisplay";

    QSqlDatabase l_db = QSqlDatabase::database();
    if (!l_db.isOpen())
    {
       QString l_errorMessage = "Error : DB isn't opened ...";
       qWarning() << l_errorMessage;
       throw std::runtime_error(l_errorMessage.toStdString());
    }
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *l_selectQuery = new QSqlQuery();

    l_selectQuery->exec("SELECT * FROM '"+tableName+"'");
    setModel(model, l_selectQuery);
    //qDebug() << event;
    if (event == 0)
    {
        model->clear();
        ui->tableView->setModel(model);
    }
}

bool CDbVisualizerSAMP::getState(QCheckBox *currentCheckBox, QCheckBox *toUncheck, QCheckBox *toUncheck2, QCheckBox *toUncheck3) const
{
    qInfo() << "getState";

    bool ret = false;
    if (currentCheckBox->isChecked())
    {
        ret = true;
        toUncheck->setChecked(false);
        toUncheck2->setChecked(false);
        toUncheck3->setChecked(false);
        //qDebug() << "Checkbox unchecked";
    }
    return ret;
}

void CDbVisualizerSAMP::on_checkBox_stateChanged(int arg1)
{
    bool isChecked = getState(ui->checkBox, ui->checkBox_2, ui->checkBox_3, ui->checkBox_4);
    if (isChecked)
        getTableToDisplay("PRODUCTION", arg1);
}

void CDbVisualizerSAMP::on_checkBox_2_stateChanged(int arg1)
{
   bool isChecked = getState(ui->checkBox_2, ui->checkBox, ui->checkBox_3, ui->checkBox_4);
   if (isChecked)
        getTableToDisplay("CONTROL", arg1);
}

void CDbVisualizerSAMP::on_checkBox_3_stateChanged(int arg1)
{
    bool isChecked = getState(ui->checkBox_3, ui->checkBox, ui->checkBox_2, ui->checkBox_4);
    if (isChecked)
        getTableToDisplay("TREATMENT", arg1);
}

void CDbVisualizerSAMP::on_checkBox_4_stateChanged(int arg1)
{
    bool isChecked = getState(ui->checkBox_4, ui->checkBox, ui->checkBox_2, ui->checkBox_3);
    if (isChecked)
        getTableToDisplay("MEASURES", arg1);
}


/*void CDbVisualizerSAMP::initializeModel(QSqlRelationalTableModel *model, QString tableName)
{
    qDebug() << "initializeModel";
    model->setTable("TMP");

    QString l_id = "_ID";
    std::string l_tmpTableName = tableName.toStdString();
    std::string l_convert = l_id.toStdString();

    const char* l_tmp = strcat((char*)l_tmpTableName.c_str(), l_convert.c_str());
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setRelation(0, QSqlRelation("TMP", l_tmp, "SHIFT_ID"));
    //model->setRelation(1, QSqlRelation("TMP", tableName +"_DT", tableName +"_DATE"));

    model->setHeaderData(0, Qt::Horizontal, QObject::tr(l_tmp));
    model->select();
}

QTableView *CDbVisualizerSAMP::createView(const QString &title, QSqlTableModel *model) const
{
    qDebug() << "createView";
    //! [4]
    QTableView *view = new QTableView;
    view->setModel(model);
    view->setItemDelegate(new QSqlRelationalDelegate(view));
    //! [4]
    view->setWindowTitle(title);
    return view;
}

void CDbVisualizerSAMP::getData(QString tableName)
{
    qDebug() << "getData";

    if (tableName == "TREATMENT")
        getTreatmentData();
    else if (tableName == "MEASURES")
        getMeasuresData();
    else if (tableName == "CONTROL")
        getControlData();
    else if (tableName == "PRODUCTION")
        getProductionData();
}

void CDbVisualizerSAMP::getTreatmentData()
{
    qDebug() << "getTreatmentData";
    QSqlDatabase l_db = QSqlDatabase::database();

    if (!l_db.open())
    {
        QString l_errorMessage = "Error : DB isn't opened ...";
        qDebug() << l_errorMessage;
        throw std::runtime_error(l_errorMessage.toStdString());
    }
    else
    {
        QSqlQuery l_dropQuery;
        l_dropQuery.exec("DROP TABLE IF EXISTS TMP");
        if (l_dropQuery.lastError().isValid())
            qDebug() << l_dropQuery.lastError();
        l_dropQuery.finish();
    }

    QString l_selectQueryStr("SELECT * FROM TREATMENT");
    qDebug() << l_selectQueryStr;
    QSqlQuery l_selectQuery(l_selectQueryStr);
    if (l_selectQuery.lastError().isValid())
        qDebug() << l_selectQuery.lastError();

    QSqlQuery l_tmpQuery;
    l_tmpQuery.exec("CREATE TABLE TMP (TREATMENT_ID INTEGER, SHIFT_ID INTEGER, PILE_ID INTEGER, TREATMENT_DT TEXT,"
              " TREATMENT_DATE TEXT, DEPTH REAL, STATE TEXT, LOCALISATION TEXT, PRODUCT_NAME TEXT, PRECONIZE_DOSAGE TEXT, QUANTITY REAL, COMMENT TEXT)");
    if (l_tmpQuery.lastError().isValid())
        qDebug() << l_tmpQuery.lastError();

    while (l_selectQuery.next())
    {
        QString l_tmpQueryStr("INSERT INTO TMP (TREATMENT_ID, SHIFT_ID, PILE_ID, TREATMENT_DT, TREATMENT_DATE,"
                    "DEPTH, STATE, LOCALISATION, PRODUCT_NAME, PRECONIZE_DOSAGE, QUANTITY, COMMENT) VALUES "
                    "('"+QString::number(l_selectQuery.value(0).toInt())+"',"
                    " '"+QString::number(l_selectQuery.value(1).toInt())+"',"
                    " '"+QString::number(l_selectQuery.value(2).toInt())+ "',"
                    " '"+l_selectQuery.value(3).toString()+"',"
                    " '"+l_selectQuery.value(4).toString()+"',"
                    " '"+QString::number(l_selectQuery.value(5).toDouble())+"',"
                    " '"+l_selectQuery.value(6).toString()+"',"
                    " '"+l_selectQuery.value(7).toString()+"',"
                    " '"+l_selectQuery.value(8).toString()+"',"
                    " '"+l_selectQuery.value(9).toString()+"',"
                    " '"+QString::number(l_selectQuery.value(10).toDouble())+"',"
                    " '"+l_selectQuery.value(11).toString()+"');");
        l_tmpQuery.exec(l_tmpQueryStr);
        if (l_tmpQuery.lastError().isValid())
            qDebug() << l_tmpQuery.lastError();
    }
}

void CDbVisualizerSAMP::getControlData()
{
    qDebug() << "getControlData";
    QSqlDatabase l_db = QSqlDatabase::database();

    if (!l_db.open())
    {
        QString l_errorMessage = "Error : DB isn't opened ...";
        qWarning() << l_errorMessage;
        throw std::runtime_error(l_errorMessage.toStdString());
    }
    else
    {
        QSqlQuery l_dropQuery("DROP TABLE IF EXISTS TMP;");
        l_dropQuery.exec();
        if (l_dropQuery.lastError().isValid())
            qDebug() << l_dropQuery.lastError();
        l_dropQuery.finish();
    }

    QString l_selectQueryStr("SELECT * FROM CONTROL");
    QSqlQuery l_selectQuery(l_selectQueryStr);

    QSqlQuery l_tmpQuery;
    l_tmpQuery.exec("CREATE TABLE TMP (CONTROL_ID INTEGER, SHIFT_ID INTEGER, PILE_ID INTEGER, CONTROL_DT TEXT, CONTROL_DATE TEXT, DEPTH REAL,"
                    " STATE TEXT, LOCALISATION TEXT, DENSITY REAL, VISCOSITY REAL, SAND REAL, PH REAL, CAKE REAL, FILTRAT REAL, COMMENT TEXT)");
    if (l_tmpQuery.lastError().isValid())
        qDebug() << l_tmpQuery.lastError();

    while (l_selectQuery.next())
    {

        QString l_tmpQueryStr("INSERT INTO TMP (CONTROL_ID, SHIFT_ID, PILE_ID, CONTROL_DT, CONTROL_DATE, DEPTH,"
                              " STATE, LOCALISATION, DENSITY, VISCOSITY, SAND, PH, CAKE, FILTRAT, COMMENT) VALUES"
                              "('"+QString::number(l_selectQuery.value(0).toInt())+"',"
                              " '"+QString::number(l_selectQuery.value(1).toInt())+"',"
                              " '"+QString::number(l_selectQuery.value(2).toInt())+"',"
                              " '"+l_selectQuery.value(3).toString()+"',"
                              " '"+l_selectQuery.value(4).toString()+"',"
                              " '"+QString::number(l_selectQuery.value(5).toDouble())+"',"
                              " '"+l_selectQuery.value(6).toString()+"',"
                              " '"+l_selectQuery.value(7).toString()+"',"
                              " '"+QString::number(l_selectQuery.value(8).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(9).toDouble())+"', "
                              " '"+QString::number(l_selectQuery.value(10).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(11).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(12).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(13).toDouble())+"',"
                              " '"+l_selectQuery.value(14).toString()+"');");
        l_tmpQuery.exec(l_tmpQueryStr);
        //qInfo() << l_tmpQueryStr;
        if (l_tmpQuery.lastError().isValid())
            qDebug() << l_tmpQuery.lastError();
    }

}

void CDbVisualizerSAMP::getMeasuresData()
{
    qDebug() << "getMeasuresData";

    QSqlDatabase l_db = QSqlDatabase::database();
    if (!l_db.open())
    {
        QString l_errorMessage = "Error : DB isn't opened ...";
        qWarning() << l_errorMessage;
        throw std::runtime_error(l_errorMessage.toStdString());
    }
    else
    {
        QSqlQuery l_dropQuery;
        l_dropQuery.exec("DROP TABLE IF EXISTS TMP");
        if (l_dropQuery.lastError().isValid())
            qDebug() << l_dropQuery.lastError();
        l_dropQuery.finish();
    }

    QString l_selectQueryStr("SELECT * FROM MEASURES");
    QSqlQuery l_selectQuery(l_selectQueryStr);

    QSqlQuery l_tmpQuery;
    l_tmpQuery.exec("CREATE TABLE TMP (MEASURES_ID INTEGER, SHIFT_ID INTEGER, MEASURES_DT TEXT, MEASURES_DATE TEXT, PRIMARY_LEVEL REAL, PRIMARY_DENSITY_INSTANT REAL,"
                    "PRIMARY_DENSITY_AVERAGE REAL, SECONDARY_LEVEL REAL, SECONDARY_DENSITY_INSTANT REAL, SECONDARY_DENSITY_AVERAGE REAL, TRANSFERT_LEVEL REAL,"
                    "TRANSFERT_DENSITY_INSTANT REAL, TRANSFERT_DENSITY_AVERAGE REAL, DATA_DEBIT REAL, DATA_TANK_LEVEL REAL, APP_VERSION TEXT, APP_ID TEXT)");

    if (l_tmpQuery.lastError().isValid())
        qDebug() << l_tmpQuery.lastError();

    while (l_selectQuery.next())
    {

        QString l_tmpQueryStr("INSERT INTO TMP (MEASURES_ID, SHIFT_ID, MEASURES_DT, MEASURES_DATE, PRIMARY_LEVEL, PRIMARY_DENSITY_INSTANT,"
                              "PRIMARY_DENSITY_AVERAGE, SECONDARY_LEVEL, SECONDARY_DENSITY_INSTANT, SECONDARY_DENSITY_AVERAGE, TRANSFERT_LEVEL,"
                              "TRANSFERT_DENSITY_INSTANT, TRANSFERT_DENSITY_AVERAGE, DATA_DEBIT, DATA_TANK_LEVEL, APP_VERSION, APP_ID) VALUES"
                              " ('"+QString::number(l_selectQuery.value(0).toInt())+"',"
                              " '"+QString::number(l_selectQuery.value(1).toInt())+"',"
                              " '"+l_selectQuery.value(2).toString()+"',"
                              " '"+l_selectQuery.value(3).toString()+"',"
                              " '"+QString::number(l_selectQuery.value(4).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(5).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(6).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(7).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(8).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(9).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(10).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(11).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(12).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(13).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(14).toDouble())+"',"
                              " '"+l_selectQuery.value(15).toString()+"',"
                              " '"+l_selectQuery.value(16).toString()+"');");
        l_tmpQuery.exec(l_tmpQueryStr);
        //qInfo() << l_tmpQueryStr;
        if (l_tmpQuery.lastError().isValid())
            qDebug() << l_tmpQuery.lastError();
    }
}

void CDbVisualizerSAMP::getProductionData()
{
    qDebug() << "getProductionData";
    QSqlDatabase l_db = QSqlDatabase::database();

    if (!l_db.open())
    {
        QString l_errorMessage = "Error : DB isn't opened ...";
        qWarning() << l_errorMessage;
        throw std::runtime_error(l_errorMessage.toStdString());
    }
    else
    {
        QSqlQuery l_dropQuery;
        l_dropQuery.exec("DROP TABLE IF EXISTS TMP");
        if (l_dropQuery.lastError().isValid())
            qDebug() << l_dropQuery.lastError();
        l_dropQuery.finish();
    }
    QString l_selectQueryStr("SELECT * FROM PRODUCTION");
    QSqlQuery l_selectQuery(l_selectQueryStr);

    QSqlQuery l_tmpQuery;
    l_tmpQuery.exec("CREATE TABLE TMP (PRODUCTION_ID INTEGER, SHIFT_ID INTEGER, PRODUCTION_DT TEXT,"
                    "PRODUCTION_DATE TEXT, QUANTITY REAL, WATER_DOSAGE REAL, BENTONITE_DOSAGE REAL, ADD_ONE_DOSAGE REAL, ADD_TWO_DOSAGE REAL,"
                    "BENTONITE_TYPE TEXT, ADD_ONE_TYPE TEXT, ADD_TWO_TYPE TEXT, COMMENT TEXT)");

    if (l_tmpQuery.lastError().isValid())
        qDebug() << l_tmpQuery.lastError();

    while (l_selectQuery.next())
    {

        QString l_tmpQueryStr("INSERT INTO TMP (PRODUCTION_ID, SHIFT_ID, PRODUCTION_DT, PRODUCTION_DATE, QUANTITY, WATER_DOSAGE,"
                              "BENTONITE_DOSAGE, ADD_ONE_DOSAGE, ADD_TWO_DOSAGE, BENTONITE_TYPE, ADD_ONE_TYPE, ADD_TWO_TYPE, COMMENT) VALUES"
                              "('"+QString::number(l_selectQuery.value(0).toInt())+"',"
                              " '"+QString::number(l_selectQuery.value(1).toInt())+"',"
                              " '"+l_selectQuery.value(2).toString()+"',"
                              " '"+l_selectQuery.value(3).toString()+"',"
                              " '"+QString::number(l_selectQuery.value(4).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(5).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(6).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(7).toDouble())+"',"
                              " '"+QString::number(l_selectQuery.value(8).toDouble())+"',"
                              " '"+l_selectQuery.value(9).toString()+"',"
                              " '"+l_selectQuery.value(10).toString()+"',"
                              " '"+l_selectQuery.value(11).toString()+"',"
                              " '"+l_selectQuery.value(12).toString()+"');");
        l_tmpQuery.exec(l_tmpQueryStr);
        //qInfo() << l_tmpQueryStr;
        if (l_tmpQuery.lastError().isValid())
            qDebug() << l_tmpQuery.lastError();
    }
}*/

