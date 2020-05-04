/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbrir;
    QAction *actionGuardar;
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPlainTextEdit *TextoAnalizar;
    QTableWidget *tabla;
    QTableWidget *tablaErrores;
    QTableWidget *tablaCuadruplos;
    QMenuBar *menubar;
    QMenu *menuArchivo;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(848, 637);
        actionAbrir = new QAction(MainWindow);
        actionAbrir->setObjectName(QString::fromUtf8("actionAbrir"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/iconfinder_Open_1493293.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbrir->setIcon(icon);
        actionGuardar = new QAction(MainWindow);
        actionGuardar->setObjectName(QString::fromUtf8("actionGuardar"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/iconfinder_Save_1493294.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGuardar->setIcon(icon1);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 410, 261, 23));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 16, 211, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(480, 20, 91, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(480, 240, 91, 16));
        TextoAnalizar = new QPlainTextEdit(centralwidget);
        TextoAnalizar->setObjectName(QString::fromUtf8("TextoAnalizar"));
        TextoAnalizar->setGeometry(QRect(30, 40, 421, 351));
        tabla = new QTableWidget(centralwidget);
        if (tabla->columnCount() < 3)
            tabla->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setText(QString::fromUtf8("Estado"));
        tabla->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tabla->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QFont font;
        font.setPointSize(9);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tabla->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tabla->setObjectName(QString::fromUtf8("tabla"));
        tabla->setGeometry(QRect(460, 40, 341, 192));
        tabla->setMinimumSize(QSize(341, 0));
        tabla->setMaximumSize(QSize(341, 16777215));
        tablaErrores = new QTableWidget(centralwidget);
        if (tablaErrores->columnCount() < 3)
            tablaErrores->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablaErrores->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tablaErrores->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tablaErrores->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tablaErrores->setObjectName(QString::fromUtf8("tablaErrores"));
        tablaErrores->setGeometry(QRect(460, 260, 341, 131));
        tablaCuadruplos = new QTableWidget(centralwidget);
        if (tablaCuadruplos->columnCount() < 5)
            tablaCuadruplos->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tablaCuadruplos->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tablaCuadruplos->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tablaCuadruplos->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tablaCuadruplos->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tablaCuadruplos->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        tablaCuadruplos->setObjectName(QString::fromUtf8("tablaCuadruplos"));
        tablaCuadruplos->setGeometry(QRect(300, 410, 501, 161));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 848, 21));
        menuArchivo = new QMenu(menubar);
        menuArchivo->setObjectName(QString::fromUtf8("menuArchivo"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuArchivo->menuAction());
        menuArchivo->addAction(actionAbrir);
        menuArchivo->addAction(actionGuardar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAbrir->setText(QCoreApplication::translate("MainWindow", "Abrir", nullptr));
        actionGuardar->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Analizar", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Texto", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Lista de Tokens", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Errores", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tabla->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Token", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tabla->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Descripcion", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tablaErrores->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Estado", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tablaErrores->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Token", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tablaErrores->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Descripcion", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tablaCuadruplos->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Contador", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tablaCuadruplos->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Operador", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tablaCuadruplos->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Operando1", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tablaCuadruplos->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Operando2", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tablaCuadruplos->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Resultado", nullptr));
        menuArchivo->setTitle(QCoreApplication::translate("MainWindow", "Archivo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
