/********************************************************************************
** Form generated from reading UI file 'GraphicView.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICVIEW_H
#define UI_GRAPHICVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphicViewClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GraphicViewClass)
    {
        if (GraphicViewClass->objectName().isEmpty())
            GraphicViewClass->setObjectName(QStringLiteral("GraphicViewClass"));
        GraphicViewClass->resize(600, 400);
        menuBar = new QMenuBar(GraphicViewClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        GraphicViewClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GraphicViewClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GraphicViewClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GraphicViewClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GraphicViewClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GraphicViewClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GraphicViewClass->setStatusBar(statusBar);

        retranslateUi(GraphicViewClass);

        QMetaObject::connectSlotsByName(GraphicViewClass);
    } // setupUi

    void retranslateUi(QMainWindow *GraphicViewClass)
    {
        GraphicViewClass->setWindowTitle(QApplication::translate("GraphicViewClass", "GraphicView", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GraphicViewClass: public Ui_GraphicViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICVIEW_H
