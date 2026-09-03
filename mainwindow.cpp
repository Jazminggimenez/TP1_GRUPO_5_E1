
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QRegularExpression>

// Validador para que el DNI solamente tenga números
QRegularExpression soloNumeros("^[0-9]+$");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ==================================================
    // DATOS PARA EL LOGIN
    // ==================================================

    usuarioCorrecto = "grupo5";
    contrasenaCorrecta = "utnfrh";

}

MainWindow::~MainWindow()
{
    delete ui;
}


// ======================================================
// LOGIN
// ======================================================

void MainWindow::on_pushButton_Ingresar_clicked()
{
    // Obtengo el usuario ingresado
    QString usuarioIngresado =
        ui->lineEditUsuario->text();

    // Obtengo la contraseña ingresada
    QString contrasenaIngresada =
        ui->lineEditContrasena->text();

    // Comparo usuario y contraseña
    if (usuarioIngresado == usuarioCorrecto &&
        contrasenaIngresada == contrasenaCorrecta)
    {
        QMessageBox::information(
            this,
            "Ingreso correcto",
            "Bienvenido al sistema."
            );

        // Paso de la pantalla de login
        // a la pantalla principal
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        QMessageBox::warning(
            this,
            "Error",
            "Usuario o contraseña incorrectos."
            );

        // Limpio los campos
        ui->lineEditUsuario->clear();
        ui->lineEditContrasena->clear();

        // Vuelvo al usuario
        ui->lineEditUsuario->setFocus();
    }
}


// ======================================================
// GUARDAR PACIENTE
// ======================================================

void MainWindow::on_pushButtonGuardarPaciente_clicked()
{
    // Creo una variable de tipo Paciente
    Paciente nuevoPaciente;

    // Obtengo el nombre
    nuevoPaciente.nombre =
        ui->lineEditNombre->text();

    // Obtengo el apellido
    nuevoPaciente.apellido =
        ui->lineEditApellido->text();

    // Obtengo la edad
    nuevoPaciente.edad =
        ui->spinBoxEdad->value();

    // Obtengo el género seleccionado
    QString generoSeleccionado =
        ui->comboBoxGenero->currentText();

    // Obtengo el DNI
    nuevoPaciente.dni =
        ui->lineEditDni->text();

    // ==================================================
    // VALIDACIÓN DE DATOS
    // ==================================================

    if (nuevoPaciente.nombre.isEmpty() ||
        nuevoPaciente.apellido.isEmpty() ||
        nuevoPaciente.dni.isEmpty() ||
        generoSeleccionado == "Seleccionar")
    {
        QMessageBox::warning(
            this,
            "Datos incompletos",
            "Complete todos los campos."
            );

        return;
    }

    // ==================================================
    // VALIDACIÓN DEL DNI
    // ==================================================

    if (!soloNumeros.match(nuevoPaciente.dni).hasMatch())
    {
        QMessageBox::warning(
            this,
            "DNI incorrecto",
            "El DNI debe contener solamente números."
            );

        return;
    }

    // ==================================================
    // CONVERSIÓN DEL GÉNERO A CHAR
    // ==================================================

    nuevoPaciente.genero =
        generoSeleccionado.at(0).toLatin1();

    // ==================================================
    // AGREGAR A LA LISTA DE ESPERA
    // ==================================================

    pacientesEnEspera.append(nuevoPaciente);

    QMessageBox::information(
        this,
        "Paciente cargado",
        "El paciente fue agregado a la lista de espera."
        );

    // ==================================================
    // LIMPIAR FORMULARIO
    // ==================================================

    ui->lineEditNombre->clear();

    ui->lineEditApellido->clear();

    ui->lineEditDni->clear();

    // La edad vuelve al mínimo
    ui->spinBoxEdad->setValue(1);

    // Vuelve a "Seleccionar"
    ui->comboBoxGenero->setCurrentIndex(0);
}


// ======================================================
// LISTA DE ESPERA
// ======================================================

void MainWindow::on_pushButtonListaDeEspera_clicked()
{
    QString mensaje;

    // Compruebo si la lista está vacía
    if (pacientesEnEspera.isEmpty())
    {
        mensaje = "No hay pacientes en espera.";
    }
    else
    {
        // Recorro la lista desde el primero
        // hasta el último
        for (int i = 0;
             i < pacientesEnEspera.size();
             i++)
        {
            // Número de orden
            mensaje += QString::number(i + 1);
            mensaje += ". ";

            // Nombre y apellido
            mensaje += pacientesEnEspera[i].nombre;
            mensaje += " ";
            mensaje += pacientesEnEspera[i].apellido;

            // Nueva línea
            mensaje += "\n";
        }
    }

    QMessageBox::information(
        this,
        "Pacientes sin atender",
        mensaje
        );
}


// ======================================================
// PRÓXIMO EN ATENDER
// ======================================================

void MainWindow::on_pushButtonProximoEnAtender_clicked()
{
    // Compruebo si hay pacientes
    if (pacientesEnEspera.isEmpty())
    {
        QMessageBox::information(
            this,
            "Próximo paciente",
            "No hay pacientes en espera."
            );

        return;
    }

    // Obtengo el primer paciente
    // SIN eliminarlo de la lista
    Paciente proximo =
        pacientesEnEspera.first();

    // Creo el mensaje
    QString mensaje;

    mensaje += "Nombre: ";
    mensaje += proximo.nombre;
    mensaje += "\n";

    mensaje += "Apellido: ";
    mensaje += proximo.apellido;
    mensaje += "\n";

    mensaje += "Edad: ";
    mensaje += QString::number(proximo.edad);
    mensaje += "\n";

    mensaje += "Género: ";
    mensaje += QString(proximo.genero);
    mensaje += "\n";

    mensaje += "DNI: ";
    mensaje += proximo.dni;

    // Muestro el próximo paciente
    QMessageBox::information(
        this,
        "Próximo paciente",
        mensaje
        );
}


// ======================================================
// ATENDER PACIENTE
// ======================================================

void MainWindow::on_pushButtonAtenderPaciente_clicked()
{
    // Compruebo si hay pacientes
    if (pacientesEnEspera.isEmpty())
    {
        QMessageBox::information(
            this,
            "Atención",
            "No hay pacientes en espera."
            );

        return;
    }

    // Tomo el primer paciente
    Paciente pacienteAtendido =
        pacientesEnEspera.first();

    // Creo el mensaje
    QString mensaje;

    mensaje += "Paciente atendido:\n\n";

    mensaje += "Nombre: ";
    mensaje += pacienteAtendido.nombre;
    mensaje += "\n";

    mensaje += "Apellido: ";
    mensaje += pacienteAtendido.apellido;
    mensaje += "\n";

    mensaje += "Edad: ";
    mensaje += QString::number(pacienteAtendido.edad);
    mensaje += "\n";

    mensaje += "Género: ";
    mensaje += QString(pacienteAtendido.genero);
    mensaje += "\n";

    mensaje += "DNI: ";
    mensaje += pacienteAtendido.dni;

    // ==================================================
    // PASAR PACIENTE A ATENDIDOS
    // ==================================================

    pacientesAtendidos.append(pacienteAtendido);

    // Elimino el primero de la lista de espera
    pacientesEnEspera.removeFirst();

    // Muestro quién fue atendido
    QMessageBox::information(
        this,
        "Atención del paciente",
        mensaje
        );
}


// ======================================================
// PACIENTES ATENDIDOS
// ======================================================

void MainWindow::on_pushButtonPacientesAtendidos_clicked()
{
    QString mensaje;

    // Compruebo si hay pacientes atendidos
    if (pacientesAtendidos.isEmpty())
    {
        mensaje = "No hay pacientes atendidos.";
    }
    else
    {
        // Recorro la lista
        for (int i = 0;
             i < pacientesAtendidos.size();
             i++)
        {
            // Número de orden de atención
            mensaje += QString::number(i + 1);
            mensaje += ". ";

            // Nombre y apellido
            mensaje += pacientesAtendidos[i].nombre;
            mensaje += " ";
            mensaje += pacientesAtendidos[i].apellido;

            // Nueva línea
            mensaje += "\n";
        }
    }

    QMessageBox::information(
        this,
        "Pacientes atendidos",
        mensaje
        );
}


// ======================================================
// SALIR
// ======================================================

void MainWindow::on_pushButton_CerrarSesion_clicked()
{
    // Vuelvo a la pantalla de login
    ui->stackedWidget->setCurrentIndex(0);

    // Limpio usuario
    ui->lineEditUsuario->clear();

    // Limpio contraseña
    ui->lineEditContrasena->clear();

    // Coloco el cursor en usuario
    ui->lineEditUsuario->setFocus();
}