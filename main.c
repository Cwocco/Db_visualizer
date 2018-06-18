#include "CDbVisualizerSAMP.h"

int main(int argc, char *argv[])
{

    CDbVisualizerSAMP start;
    QApplication app(argc, argv);
    if (!start.init())
        return EXIT_FAILURE;
    start.getTreatmentData();
    QSqlRelationalTableModel model;

    start.initializeModel(&model);

    QScopedPointer<QTableView> view(start.createView(QObject::tr("TEST"), &model));
    view->show();

    return app.exec();
}
