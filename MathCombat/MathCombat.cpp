#include "MathCombat.h"
#include <QMessageBox>

MathCombat::MathCombat(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MathCombatClass())
{
	ui->setupUi(this);

	ui->stackedWidget->setCurrentWidget(ui->previewWidget);
	connect(ui->previewWidget, &PreviewWidget::StartNewGame, this, &MathCombat::StartNewGame);
	connect(ui->firstLevelWidget, &FirstLevelWidget::CombatSignal, this, [this] {
		ui->stackedWidget->setCurrentWidget(ui->taskWidget);
		});


}

MathCombat::~MathCombat()
{
	delete ui;
}

void MathCombat::ShowErrorDialog()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Ошибка!");
	msgBox.setText("Произошла ошибка в игре!");
	msgBox.setInformativeText("Что вы хотите сделать?");

	// Создаём кнопки
	QPushButton* restartBtn = msgBox.addButton("Начать заново", QMessageBox::AcceptRole);
	QPushButton* exitBtn = msgBox.addButton("Выход", QMessageBox::RejectRole);

	msgBox.setDefaultButton(restartBtn);

	// Показываем диалог и обрабатываем выбор
	msgBox.exec();

	if (msgBox.clickedButton() == restartBtn) {
		// Перезапуск игры
		ui->stackedWidget->setCurrentWidget(ui->firstLevelWidget);
	}
	else if (msgBox.clickedButton() == exitBtn) {
		// Переключение на другой стек виджет
		ui->stackedWidget->setCurrentWidget(ui->previewWidget);
	}
}

void MathCombat::StartNewGame()
{
	ui->stackedWidget->setCurrentWidget(ui->firstLevelWidget);
}