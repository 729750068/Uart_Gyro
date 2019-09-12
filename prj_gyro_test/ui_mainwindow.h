/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QComboBox *cBox_seralSW;
    QComboBox *cBox_gyroRange;
    QPushButton *pButtonOpen;
    QPushButton *pButtonImport;
    QPushButton *pButtonSave;
    QCheckBox *cBoxFileProcess;
    QSplitter *splitter;
    QTextEdit *tEdit_Gro;
    QTextEdit *tEdit_log;
    QLineEdit *lEditFileName;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(548, 415);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cBox_seralSW = new QComboBox(centralWidget);
        cBox_seralSW->setObjectName(QStringLiteral("cBox_seralSW"));

        gridLayout->addWidget(cBox_seralSW, 0, 0, 1, 1);

        cBox_gyroRange = new QComboBox(centralWidget);
        cBox_gyroRange->setObjectName(QStringLiteral("cBox_gyroRange"));

        gridLayout->addWidget(cBox_gyroRange, 0, 1, 1, 1);

        pButtonOpen = new QPushButton(centralWidget);
        pButtonOpen->setObjectName(QStringLiteral("pButtonOpen"));

        gridLayout->addWidget(pButtonOpen, 0, 2, 1, 1);

        pButtonImport = new QPushButton(centralWidget);
        pButtonImport->setObjectName(QStringLiteral("pButtonImport"));

        gridLayout->addWidget(pButtonImport, 0, 3, 1, 1);

        pButtonSave = new QPushButton(centralWidget);
        pButtonSave->setObjectName(QStringLiteral("pButtonSave"));

        gridLayout->addWidget(pButtonSave, 1, 2, 1, 1);

        cBoxFileProcess = new QCheckBox(centralWidget);
        cBoxFileProcess->setObjectName(QStringLiteral("cBoxFileProcess"));

        gridLayout->addWidget(cBoxFileProcess, 1, 3, 1, 1);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tEdit_Gro = new QTextEdit(splitter);
        tEdit_Gro->setObjectName(QStringLiteral("tEdit_Gro"));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        tEdit_Gro->setFont(font);
        splitter->addWidget(tEdit_Gro);
        tEdit_log = new QTextEdit(splitter);
        tEdit_log->setObjectName(QStringLiteral("tEdit_log"));
        splitter->addWidget(tEdit_log);

        gridLayout->addWidget(splitter, 2, 0, 1, 4);

        lEditFileName = new QLineEdit(centralWidget);
        lEditFileName->setObjectName(QStringLiteral("lEditFileName"));

        gridLayout->addWidget(lEditFileName, 1, 0, 1, 2);

        gridLayout->setColumnStretch(0, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 548, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        cBox_gyroRange->clear();
        cBox_gyroRange->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "2000", 0)
         << QApplication::translate("MainWindow", "250", 0)
         << QApplication::translate("MainWindow", "62.5", 0)
        );
        pButtonOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        pButtonImport->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\346\226\207\344\273\266", 0));
        pButtonSave->setText(QApplication::translate("MainWindow", "Save", 0));
        cBoxFileProcess->setText(QApplication::translate("MainWindow", "\345\244\204\347\220\206\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
