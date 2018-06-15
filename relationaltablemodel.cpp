/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtSql>

#include "../connection.h"

void initializeModel(QSqlRelationalTableModel *model)
{
    //! [0]
    model->setTable("TMP");
    //! [0]

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //! [1]
    model->setRelation(0, QSqlRelation("TMP", "TREATMENT_ID", "SHIFT_ID"));
    //! [1] //! [2]
    model->setRelation(1, QSqlRelation("TMP", "TREATMENT_DT", "TREATMENT_DATE"));
    //! [2]

    //! [3]
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("TREATMENT_ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("SHIFT_ID"));

    //model->setHeaderData(2, Qt::Horizontal, QObject::tr("City"));
    //model->setHeaderData(3, Qt::Horizontal, QObject::tr("Country"));
    //! [3]

    model->select();
}

QTableView *createView(const QString &title, QSqlTableModel *model)
{
    //! [4]
    QTableView *view = new QTableView;
    view->setModel(model);
    view->setItemDelegate(new QSqlRelationalDelegate(view));
    //! [4]
    view->setWindowTitle(title);
    return view;
}

void createRelationalTables()
{

    QSqlDatabase l_db = QSqlDatabase::database();

    if (!l_db.open())
    {
        QString l_errorMessage = "Error : DB isn't opened ...";
        qWarning() << l_errorMessage;
        throw std::runtime_error(l_errorMessage.toStdString());
    }
    else
        qInfo() << "connected to samp";
    QString l_selectQueryStr("SELECT TREATMENT_ID, SHIFT_ID FROM TREATMENT");
    QSqlQuery l_selectQuery(l_selectQueryStr);

    while (l_selectQuery.next())
    {
        QSqlQuery test;
        int t_id = l_selectQuery.value(0).toInt();
        qInfo() << t_id;
        int s_id = l_selectQuery.value(1).toInt();
        test.exec("DROP TABLE IF EXISTS TMP");
        test.exec("CREATE TABLE TMP (TREATMENT_ID INTEGER, SHIFT_ID INTEGER)");
        QString yolo("INSERT INTO TMP (TREATMENT_ID, SHIFT_ID) VALUES ('"+QString::number(t_id)+"',"
                    " '"+QString::number(s_id)+"')");
        qInfo() << yolo;
        if (test.exec(yolo))
            qInfo() << "CALLED";
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!createConnection())
        return EXIT_FAILURE;

    createRelationalTables();

    QSqlRelationalTableModel model;

    initializeModel(&model);

    QScopedPointer<QTableView> view(createView(QObject::tr("Relational Table Model"), &model));
    view->show();

    return app.exec();
}
