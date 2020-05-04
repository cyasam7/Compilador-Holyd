#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QToken.h"

#include <QMainWindow>
#include <QStack>
#include <QQueue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void analiza();
    void Token(QString token,int e);
    void Error(QString token,int e);
    int Relaciona(QChar car);
    void insertarDatoEnTabla(QString numero,QString token, QString descripcion);
    void insertarDatoEnTablaError(QString numero,QString token, QString descripcion);
    void insertarDatoEnTablaCuadruplos();
    void AnalizadorSintactico();

    int TablaProducciones(int valor);

    void Semantico();
    QString validarTipos(QString tipo1,QString tipo2,QString signo);
    int tipoANumero(QString tipo);
    bool existeIdentificador(QString id);

private slots:
    void on_pushButton_clicked();
    void on_actionAbrir_triggered();
    void on_actionGuardar_triggered();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
