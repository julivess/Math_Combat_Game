#include "TaskWidget.h"
#include <QRandomGenerator>

TaskWidget::TaskWidget(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::TaskWidgetClass())
{
	ui->setupUi(this);

	connect(ui->pushButton, &QPushButton::clicked, this, &TaskWidget::CheckingResponse);
	connect(ui->pushButtonExit, &QPushButton::clicked, this, &TaskWidget::Exit);
	connect(ui->pushButtonNewGame, &QPushButton::clicked, this, &TaskWidget::RestartLevel);
}

TaskWidget::~TaskWidget()
{
	delete ui;
}

// Показать пример с заданным уровнем сложности 
void TaskWidget::ShowTaskByDifficultyLevel(Difficulty level)
{
	ui->pushButtonExit->hide();
	ui->pushButtonNewGame->hide();
	ui->pushButton->show();
	ui->lineEdit->show();
	switch (level)
	{
	case(Difficulty::Easy):
		ShowEasyTask();
		break;
	case(Difficulty::Medium):
		ShowMediumtask();
		break;
	case(Difficulty::Hard):
		ShowHardTask();
		break;
	};

	return;
}

// Показать простой пример
void TaskWidget::ShowEasyTask()
{
	currentDifficulty = Difficulty::Easy;
	int easyInd = QRandomGenerator::global()->bounded(int(m_tasksEasy.size() - 1));
	ui->lineEdit->setText("");
	ui->label->setText(m_tasksEasy[easyInd].first);

	ui->pushButton->setFocus();
	
}

// Показать пример средней сложности
void TaskWidget::ShowMediumtask()
{
	currentDifficulty = Difficulty::Medium;
	int mediumInd = QRandomGenerator::global()->bounded(int(m_tasksMedium.size() - 1));
	ui->lineEdit->setText("");
	ui->label->setText(m_tasksMedium[mediumInd].first);

	ui->pushButton->setFocus();
	
}

void TaskWidget::ShowHardTask()
{
	currentDifficulty = Difficulty::Hard;
	int hardInd = QRandomGenerator::global()->bounded(int(m_tasksHard.size() - 1));
	ui->lineEdit->setText("");
	ui->label->setText(m_tasksHard[hardInd].first);

	ui->pushButton->setFocus();
	
}

// Проверить ответ пользователя
void TaskWidget::CheckingResponse()
{
	QString task = ui->label->text();
	QString response = ui->lineEdit->text();

	bool result = false;

	switch (currentDifficulty) {
	case(Difficulty::Easy):
		for (auto res : m_tasksEasy)
		{
			if (res.first == task && res.second == response)
			{
				result = true;
				break;
			}
		}
		break;
	case(Difficulty::Medium):

		for (auto res : m_tasksMedium)
		{
			if (res.first == task && res.second == response)
			{
				result = true;
				break;
			}
		}
		break;
	case(Difficulty::Hard):
		for (auto res : m_tasksHard)
		{
			if (res.first == task && res.second == response)
			{
				result = true;
				break;
			}
		}
	};
	if (!result)
	{
		ui->lineEdit->hide();
		ui->pushButton->hide();
		ui->pushButtonExit->show();
		ui->pushButtonNewGame->show();
		ui->label->setText("Ответ неверный!");
	}
	emit FightIsOver(result); // Испускаем сигнал с результатом боя
}