#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// ======================================================
// ESTRUCTURA PACIENTE
// ======================================================

struct Paciente
{
    QString nombre;
    QString apellido;
    int edad;
    char genero;
    QString dni;
};

// ======================================================
// CLASE MAINWINDOW
// ======================================================

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:

    // LOGIN
    void on_pushButton_Ingresar_clicked();

    // SISTEMA
    void on_pushButtonGuardarPaciente_clicked();

    void on_pushButtonListaDeEspera_clicked();

    void on_pushButtonProximoEnAtender_clicked();

    void on_pushButtonAtenderPaciente_clicked();

    void on_pushButtonPacientesAtendidos_clicked();

    void on_pushButton_CerrarSesion_clicked();

private:

    Ui::MainWindow *ui;

    // ==================================================
    // DATOS DEL LOGIN
    // ==================================================

    QString usuarioCorrecto;
    QString contrasenaCorrecta;

    // ==================================================
    // LISTAS DE PACIENTES
    // ==================================================

    // Pacientes que todavía no fueron atendidos
    QList<Paciente> pacientesEnEspera;

    // Pacientes que ya fueron atendidos
    QList<Paciente> pacientesAtendidos;
};

#endif // MAINWINDOW_H