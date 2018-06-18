QT           += sql widgets

HEADERS = CDbVisualizerSAMP.h \
        C:\Qt\Qt5.9.1\Examples\Qt-5.9.1\sql\connection.h
SOURCES = CDbVisualizerSAMP.cpp \
    main.c

requires(qtConfig(tableview))

target.path = $$[QT_INSTALL_EXAMPLES]/sql/relationaltablemodel
INSTALLS += target
