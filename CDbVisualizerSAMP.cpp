#include "CDbVisualizerSAMP.h"


CDbVisualizerSAMP::CDbVisualizerSAMP()
{
    m_dbVisualizer = std::make_shared<CDbVisualizerSAMP>();
}

void CDbVisualizerSAMP::init()
{
    connect();
}

bool CDbVisualizerSAMP::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./samp.db");
    bool open = db.open();

    return open;
}

void CDbVisualizerSAMP::initializeModel(QSqlRelationalTableModel *model)
{
    //! [0]
    model->setTable("TMP");
    //! [0]

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //! [1]
 //   model->setRelation(0, QSqlRelation("TMP", "TREATMENT_ID", "SHIFT_ID"));
    //! [1] //! [2]
    //model->setRelation(1, QSqlRelation("TMP", "TREATMENT_DT", "TREATMENT_DATE"));
    //! [2]
    //!
    //! [3]
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("TREATMENT_ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("SHIFT_ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PILE_ID"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TREATMENT_DT"));

    //model->setHeaderData(3, Qt::Horizontal, QObject::tr("Country"));
    //! [3]

    model->select();
}

QTableView *CDbVisualizerSAMP::createView(const QString &title, QSqlTableModel *model) const
{
    //! [4]
    QTableView *view = new QTableView;
    view->setModel(model);
    view->setItemDelegate(new QSqlRelationalDelegate(view));
    //! [4]
    view->setWindowTitle(title);
    return view;
}

void CDbVisualizerSAMP::getTreatmentData()
{
    qDebug() << "getTreatmentData";
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
        l_dropQuery.finish();
    }


    QString l_selectQueryStr("SELECT * FROM TREATMENT");
    QSqlQuery l_selectQuery(l_selectQueryStr);

    while (l_selectQuery.next())
    {
        QSqlQuery l_tmpQuery;
        l_tmpQuery.exec("CREATE TABLE TMP (TREATMENT_ID INTEGER, SHIFT_ID INTEGER, PILE_ID INTEGER, TREATMENT_DT,"
                  " TREATMENT_DATE, DEPTH, STATE, LOCALISATION, PRODUCT_NAME, PRECONIZE_DOSAGE, QUANTITY, COMMENT)");
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
        qInfo() << l_tmpQueryStr;
        if (l_tmpQuery.exec(l_tmpQueryStr))
            qInfo() << "CALLED";
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
        QSqlQuery l_dropQuery;
        l_dropQuery.exec("DROP TABLE IF EXISTS TMP;");
        l_dropQuery.finish();
    }

    QString l_selectQueryStr("SELECT * FROM CONTROL");
    QSqlQuery l_selectQuery(l_selectQueryStr);

    while (l_selectQuery.next())
    {
        QSqlQuery l_tmpQuery;
        l_tmpQuery.exec("CREATE TABLE TMP (CONTROL_ID INTEGER, SHIFT_ID INTEGER, PILE_ID INTEGER, CONTROL_DT TEXT, CONTROL_DATE TEXT, DEPTH REAL,"
                        " STATE TEXT, LOCALISATION TEXT, DENSITY REAL, VISCOSITY REAL, SAND REAL, PH REAL, CAKE REAL, FILTRAT REAL, COMMENT TEXT)");
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

        qInfo() << l_tmpQueryStr;
        if (l_tmpQuery.exec(l_tmpQueryStr))
            qInfo() << "CONTROL CALLED";
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
        l_dropQuery.finish();
    }

    QString l_selectQueryStr("SELECT * FROM MEASURES");
    QSqlQuery l_selectQuery(l_selectQueryStr);

    while (l_selectQuery.next())
    {
        QSqlQuery l_tmpQuery;
        l_tmpQuery.exec("CREATE TABLE TMP (MEASURES_ID INTEGER, SHIFT_ID INTEGER, MEASURES_DT TEXT, MEASURES_DATE TEXT, PRIMARY_LEVEL REAL, PRIMARY_DENSITY_INSTANT REAL,"
                        "PRIMARY_DENSITY_AVERAGE REAL, SECONDARY_LEVEL REAL, SECONDARY_DENSITY_INSTANT REAL, SECONDARY_DENSITY_AVERAGE REAL, TRANSFERT_LEVEL REAL,"
                        "TRANSFERT_DENSITY_INSTANT REAL, TRANSFERT_DENSITY_AVERAGE REAL, DATA_DEBIT REAL, DATA_TANK_LEVEL REAL, APP_VERSION TEXT, APP_ID TEXT)");
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
        qInfo() << l_tmpQueryStr;
        if (l_tmpQuery.exec(l_tmpQueryStr))
            qInfo() << "MEASURES CALLED";
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
        l_dropQuery.finish();
    }
    QString l_selectQueryStr("SELECT * FROM PRODUCTION");
    QSqlQuery l_selectQuery(l_selectQueryStr);

    while (l_selectQuery.next())
    {
        QSqlQuery l_tmpQuery;
        l_tmpQuery.exec("CREATE TABLE TMP (PRODUCTION_ID INTEGER, SHIFT_ID INTEGER, PRODUCTION_DT TEXT,"
                        "PRODUCTION_DATE TEXT, QUANTITY REAL, WATER_DOSAGE REAL, BENTONITE_DOSAGE REAL, ADD_ONE_DOSAGE REAL,"
                        "BENTONITE_TYPE TEXT, ADD_ONE_TYPE TEXT, ADD_TWO-TYPE TEXT, COMMENT TEXT)");
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
        qInfo() << l_tmpQueryStr;
        if (l_tmpQuery.exec(l_tmpQueryStr))
            qInfo() << "PRODUCTION CALLED";
    }
}





