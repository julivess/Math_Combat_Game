#pragma once

#include <QWidget>
#include <QString>
#include "ui_TaskWidget.h"
#include <map>
#include <vector>
#include <utility>

class TaskWidget : public QWidget
{
	Q_OBJECT

public:

	enum Difficulty
	{
		Easy,
		Medium,
		Hard
	};

	TaskWidget(QWidget* parent = nullptr);
	~TaskWidget();

	void ShowTaskByDifficultyLevel(Difficulty leve);

private slots:
	void CheckingResponse();

private:
	void ShowEasyTask();
	void ShowMediumtask();
	void ShowHardTask();

	Difficulty currentDifficulty = Difficulty::Easy;

	Ui::TaskWidgetClass ui;
	const std::vector<std::pair<QString, QString>> m_tasksEasy =
	{
		{"15 + 27 = ", "42"},
		{"84 - 39 = ", "45"},
		{"12 * 8 = ", "96"},
		{"144 / 12 = ", "12"},
		{"7 + 3 * 4 =", "19"}
	};

	const std::vector<std::pair<QString, QString>> m_tasksMedium =
	{
		{"log_2(8) = ", "3"},
		{"ln(e^5) = ", "5"},
		{"sin(90) = ", "1"},
		{"cos(0) = ", "1"},
		{"log_5(25) + log_5(5) = ", "3"}
	};

	const std::vector<std::pair<QString, QString>> m_tasksHard =
	{
		{"f(x) = x^3 - 4x + 1, f'(2) = ", "8"},
		{"f(x) = e^2x, f'(0) = ", "2"},
		{"f(x) = ln(3x + 1), f'(1) = ", "0.75"}
	};

	int m_easyInd = 0;
	int m_mediumInd = 0;
	int m_hardInd = 0;

};
