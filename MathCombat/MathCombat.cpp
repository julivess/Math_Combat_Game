#include "MathCombat.h"

MathCombat::MathCombat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MathCombatClass())
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->previewWidget);

    connect(ui->previewWidget, &PreviewWidget::StartNewGame, this, &MathCombat::StartNewGame);
}

MathCombat::~MathCombat()
{
    delete ui;
}

void MathCombat::StartNewGame()
{
  ui->stackedWidget->setCurrentWidget(ui->firstLevelWidget);
}