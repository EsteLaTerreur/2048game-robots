// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "case.h"
#include <iostream>
#include <fstream>
#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include <vector>
#include "listecases.h"
#include <cstdlib>
#include <cerrno>
#include <cstdlib>
#include <ctime>
#include <QKeyEvent>
#include <random>
#include <chrono>

using namespace std;

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(nullptr))); // pour que le random ne soit pas le même à chaque partie
                                                    // (sinon on tombe sur les mêmes tuiles aléatoires à chaque fois)
    set_qt_environment();

    QGuiApplication app(argc, argv);
    ListeCases listeDeCases(16);
    // listeDeCases.lireFichier("../Jeu2048/src/parties/partie.txt"); // initialisation arbitraire pour les tests

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    for (int i = 0; i < 16; ++i) {
        string nomDeLaCase = "case" + to_string(i);
        engine.rootContext()->setContextProperty(nomDeLaCase.c_str(), &(listeDeCases.TAB[i]));
        engine.rootContext()->setContextProperty("listeDeCases",&listeDeCases);
    }
    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
