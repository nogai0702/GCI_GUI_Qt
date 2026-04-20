#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../core/GciCalculator.h"
#include <QDoubleValidator>
#include <QString>
#include <QLocale>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);

    auto validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);

    ui->lineEditH1->setValidator(validator);
    ui->lineEditPhi1->setValidator(validator);
    ui->lineEditH2->setValidator(validator);
    ui->lineEditPhi2->setValidator(validator);
    ui->lineEditH3->setValidator(validator);
    ui->lineEditPhi3->setValidator(validator);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_pushButtonCalculate_clicked()
{
    GciInput input;
    input.h1 = ui->lineEditH1->text().toDouble();
    input.phi1 = ui->lineEditPhi1->text().toDouble();
    input.h2 = ui->lineEditH2->text().toDouble();
    input.phi2 = ui->lineEditPhi2->text().toDouble();
    input.h3 = ui->lineEditH3->text().toDouble();
    input.phi3 = ui->lineEditPhi3->text().toDouble();

    GciOutput out = GciCalculator::calculate(input);

    if (!out.success) {
        ui->textEditResults->setPlainText(QString::fromStdString(out.message));
        return;
    }

    QString results;
    results += "RESULTS\n\n";
    results += QString("Refinement ratios:\n r₂₁ = %1\n r₃₂ = %2\n\n")
                    .arg(out.r21, 0, 'g', 4)
                    .arg(out.r32, 0, 'g', 4);
    
    results += QString("Apparent order:\n p = %1\n\n")
                    .arg(out.p, 0, 'g', 4);

    if (!out.message.empty()) {
        results += QString("WARNING: %1\n\n").arg(QString::fromStdString(out.message));
    }

    results += QString("Extrapolated values:\n ϕ²¹_ext = %1\n ϕ³²_ext = %2\n\n")
                    .arg(out.phi21ext, 0, 'g', 4)
                    .arg(out.phi32ext, 0, 'g', 4);

    results += QString("Approximate relative error:\n e²¹_a = %1%\n\n")
                    .arg(out.e21a * 100, 0, 'f', 2);

    results += QString("Extrapolated relative error:\n e²¹_ext = %1%\n\n")
                    .arg(out.e21ext * 100, 0, 'f', 2);

    results += QString("Fine grid convergence index:\n GCI²¹ = %1%\n")
                    .arg(out.GCI21 * 100, 0, 'f', 2);

    ui->textEditResults->setPlainText(results);
}
