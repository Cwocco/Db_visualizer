#include "CDbVisualizerSAMP.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CDbVisualizerSAMP start;
    if (!start.init())
        return EXIT_FAILURE;
/*    start.getData("CONTROL");
    QSqlRelationalTableModel model;

    start.initializeModel(&model, "CONTROL");

    QScopedPointer<QTableView> view(start.createView(QObject::tr("Database visualizer for SAMP"), &model));
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
    view->window()->resize(view->window()->width() * 1.5, view->window()->height() * 1.2);
    view->contentsRect().left();*/
    //view->show();

    start.setFixedWidth(835);
    start.setFixedHeight(460);
    start.show();

    return a.exec();
}
