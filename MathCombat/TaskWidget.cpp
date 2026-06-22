#include "TaskWidget.h"

TaskWidget::TaskWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, &QPushButton::clicked, this, &TaskWidget::CheckingResponse);
}

TaskWidget::~TaskWidget()
{}

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
	}
}

void TaskWidget::ShowEasyTask()
{
	currentDifficulty = Difficulty::Easy;
	ui.label->setText(m_tasksEasy[m_easyInd].first);

	if (m_easyInd < m_tasksEasy.size())
	{
		++m_easyInd;
	}
	else {
		m_easyInd = 0;
	}
}

void TaskWidget::ShowMediumtask()
{
	currentDifficulty = Difficulty::Medium;
	ui.label->setText(m_tasksMedium[m_mediumInd].first);

	if (m_mediumInd < m_tasksMedium.size())
	{
		++m_mediumInd;
	}
	else {
		m_mediumInd = 0;
	}
}

void TaskWidget::ShowHardTask()
{
	currentDifficulty = Difficulty::Hard;
	ui.label->setText(m_tasksHard[m_hardInd].first);

	if (m_hardInd < m_tasksHard.size())
	{
		++m_hardInd;
	}
	else {
		m_hardInd = 0;
	}
}

void TaskWidget::CheckingResponse()
{
	QString task = ui.label->text();
	QString response = ui.lineEdit->text();

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
		break;
	};

	//return result;
}