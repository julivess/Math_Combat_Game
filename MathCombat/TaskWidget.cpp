#include "TaskWidget.h"

TaskWidget::TaskWidget(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::TaskWidgetClass())
{
	ui->setupUi(this);

	connect(ui->pushButton, &QPushButton::clicked, this, &TaskWidget::CheckingResponse);
}

TaskWidget::~TaskWidget()
{
	delete ui;
}

// Показать пример с заданным уровнем сложности 
void TaskWidget::ShowTaskByDifficultyLevel(Difficulty level)
{
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
	ui->lineEdit->setText("");
	ui->label->setText(m_tasksEasy[m_easyInd].first);

	ui->pushButton->setFocus();
	if (m_easyInd < m_tasksEasy.size())
	{
		++m_easyInd;
	}
	else {
		m_easyInd = 0;
	}
}

// Показать пример средней сложности
void TaskWidget::ShowMediumtask()
{
	currentDifficulty = Difficulty::Medium;
	ui->lineEdit->setText("");
	ui->label->setText(m_tasksMedium[m_mediumInd].first);

	ui->pushButton->setFocus();
	if (m_mediumInd < m_tasksMedium.size())
	{
		++m_mediumInd;
	}
	else {
		m_mediumInd = 0;
	}
}

//Показать сложный пример
void TaskWidget::ShowHardTask()
{
	currentDifficulty = Difficulty::Hard;
	ui->lineEdit->setText("");
	ui->label->setText(m_tasksHard[m_hardInd].first);

	ui->pushButton->setFocus();
	if (m_hardInd < m_tasksHard.size())
	{
		++m_hardInd;
	}
	else {
		m_hardInd = 0;
	}
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

	emit FightIsOver(result); // Испускаем сигнал с результатом боя (Его поймает класс MathCombat)
	//return result;
}