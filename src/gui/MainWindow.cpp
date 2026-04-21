#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../core/GciCalculator.h"
#include <QDoubleValidator>
#include <QString>
#include <QLocale>
#include <QPalette>
#include <QFile>
#include <QStyleHints>
#include <QGuiApplication>
#include <QMenuBar>
#include <QMenu>
#include <QActionGroup>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);

    // Initial theme setup
    applyTheme(isSystemDarkMode());

    // Connect to system theme changes
    connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged,
            this, &MainWindow::updateTheme);

    // Theme Menu
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    auto *themeGroup = new QActionGroup(this);
    
    QAction *systemAction = viewMenu->addAction(tr("System Default"));
    systemAction->setCheckable(true);
    systemAction->setChecked(true);
    themeGroup->addAction(systemAction);

    QAction *lightAction = viewMenu->addAction(tr("Light Mode"));
    lightAction->setCheckable(true);
    themeGroup->addAction(lightAction);
    
    QAction *darkAction = viewMenu->addAction(tr("Dark Mode"));
    darkAction->setCheckable(true);
    themeGroup->addAction(darkAction);
    
    connect(lightAction, &QAction::triggered, this, [this](){ applyTheme(false); });
    connect(darkAction, &QAction::triggered, this, [this](){ applyTheme(true); });
    connect(systemAction, &QAction::triggered, this, [this](){ updateTheme(); });

    auto validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);

    ui->lineEditH1->setValidator(validator);
    ui->lineEditPhi1->setValidator(validator);
    ui->lineEditH2->setValidator(validator);
    ui->lineEditPhi2->setValidator(validator);
    ui->lineEditH3->setValidator(validator);
    ui->lineEditPhi3->setValidator(validator);

    // Tooltips (using tr() for localization)
    ui->lineEditH1->setToolTip(tr("Grid spacing for the finest grid (h₁)"));
    ui->lineEditPhi1->setToolTip(tr("Numerical solution on the finest grid (ϕ₁)"));
    ui->lineEditH2->setToolTip(tr("Grid spacing for the medium grid (h₂)"));
    ui->lineEditPhi2->setToolTip(tr("Numerical solution on the medium grid (ϕ₂)"));
    ui->lineEditH3->setToolTip(tr("Grid spacing for the coarsest grid (h₃)"));
    ui->lineEditPhi3->setToolTip(tr("Numerical solution on the coarsest grid (ϕ₃)"));

    ui->labelR21_text->setToolTip(tr("Grid refinement ratio between fine and medium grids (r₂₁ = h₂/h₁ binary)"));
    ui->labelR32_text->setToolTip(tr("Grid refinement ratio between medium and coarse grids (r₃₂ = h₃/h₂)"));
    ui->labelP_text->setToolTip(tr("Apparent order of convergence (p)"));
    ui->labelGCI_text->setToolTip(tr("Grid Convergence Index for the fine grid. Lower is better."));
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
        ui->statusbar->showMessage(tr("Calculation failed: %1").arg(QString::fromStdString(out.message)), 5000);
        ui->textEditLog->setPlainText(QString::fromStdString(out.message));
        
        // Reset values
        ui->labelR21_val->setText("-");
        ui->labelR32_val->setText("-");
        ui->labelP_val->setText("-");
        ui->labelGCI_val->setText("-");
        return;
    }

    ui->statusbar->showMessage(tr("Analysis complete"), 3000);

    // Update Dashboard Metrics
    ui->labelR21_val->setText(QString::number(out.r21, 'g', 4));
    ui->labelR32_val->setText(QString::number(out.r32, 'g', 4));
    ui->labelP_val->setText(QString::number(out.p, 'g', 4));
    ui->labelGCI_val->setText(QString("%1%").arg(out.GCI21 * 100, 0, 'f', 2));

    // Detailed Log
    QString log;
    log += tr("DETAILED REPORT\n");
    log += "==============================\n";
    log += tr("Refinement ratios:\n  r₂₁ = %1\n  r₃₂ = %2\n\n")
                    .arg(out.r21, 0, 'g', 6)
                    .arg(out.r32, 0, 'g', 6);
    
    log += tr("Apparent order:\n  p = %1\n\n")
                    .arg(out.p, 0, 'g', 6);

    log += tr("Extrapolated values:\n  ϕ²¹_ext = %1\n  ϕ³²_ext = %2\n\n")
                    .arg(out.phi21ext, 0, 'g', 6)
                    .arg(out.phi32ext, 0, 'g', 6);

    log += tr("Errors:\n  Approx. relative error e²¹_a = %1%\n")
                    .arg(out.e21a * 100, 0, 'f', 4);
    log += tr("  Extrap. relative error e²¹_ext = %1%\n\n")
                    .arg(out.e21ext * 100, 0, 'f', 4);

    log += tr("Fine grid convergence index:\n  GCI²¹ = %1%\n")
                    .arg(out.GCI21 * 100, 0, 'f', 4);

    if (!out.message.empty()) {
        log += tr("\nWARNINGS:\n%1\n").arg(QString::fromStdString(out.message));
    }

    ui->textEditLog->setPlainText(log);
}

void MainWindow::on_pushButtonClear_clicked()
{
    ui->lineEditH1->clear();
    ui->lineEditPhi1->clear();
    ui->lineEditH2->clear();
    ui->lineEditPhi2->clear();
    ui->lineEditH3->clear();
    ui->lineEditPhi3->clear();
    
    ui->labelR21_val->setText("-");
    ui->labelR32_val->setText("-");
    ui->labelP_val->setText("-");
    ui->labelGCI_val->setText("-");
    
    ui->textEditLog->clear();
    ui->statusbar->clearMessage();

void MainWindow::applyTheme(bool isDark)
{
    QString path = isDark ? ":/src/gui/style_dark.qss" : ":/src/gui/style_light.qss";
    QFile styleFile(path);
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }
}

bool MainWindow::isSystemDarkMode() const
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    return QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
#else
    const QPalette palette = QGuiApplication::palette();
    return palette.color(QPalette::WindowText).lightness() > palette.color(QPalette::Window).lightness();
#endif
}
