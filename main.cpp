#include <QCoreApplication>
#include "CDbVisualizerSAMP.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    CDbVisualizerSAMP start;
    QApplication app(argc, argv);
    if (!start.init())
        return EXIT_FAILURE;
    start.getData("MEASURES");
    QSqlRelationalTableModel model;

    start.initializeModel(&model, "MEASURES");

    QScopedPointer<QTableView> view(start.createView(QObject::tr("Database visualizer for SAMP"), &model));
    view->show();

    return app.exec();
}
