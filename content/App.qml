// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import Jeu2048

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "Jeu2048"

    Screen01 {
        id: mainScreen
    }

}

