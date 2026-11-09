#pragma once

#include <QWidget>
#include <QString>
#include "ui_TaskWidget.h"
#include <map>
#include <vector>
#include <utility>
#include "Utils.h"

namespace Ui { class TaskWidgetClass; }

// Класс окна с математическими примерами.
// Имеет 3 уровня сложности 
class TaskWidget : public QWidget
{
	Q_OBJECT

public:

	TaskWidget(QWidget* parent = nullptr);
	~TaskWidget();

	void ShowTaskByDifficultyLevel(Difficulty leve); // Показать пример с заданным уровнем сложности 

private slots:
	void CheckingResponse(); // Проверить ответ пользователя


signals:
	void RestartLevel();
	void Exit();
	void FightIsOver(bool result); // Сигнал отправляется после проверки ответа
	// (result = true - Пользователь ответил правильно)
	// (result = false - Пользователь ответил неправильно)

private:
	void ShowEasyTask(); // Показать простой пример
	void ShowMediumtask(); // Показать пример средней сложности
	void ShowHardTask();   // Показать сложный пример

	Difficulty currentDifficulty = Difficulty::Easy; // Уровень сложности текущего примера


	const std::vector<std::pair<QString, QString>> m_tasksEasy =
	{
		{"15 + 27 = ", "42"},
		{"84 - 39 = ", "45"},
		{"12 * 8 = ", "96"},
		{"144 / 12 = ", "12"},
		{"7 + 3 * 4 =", "19"},
		{"67 + 52 =", "119"}
	};

	const std::vector<std::pair<QString, QString>> m_tasksMedium =
	{
		{"log_2(8) = ", "3"},
		{"ln(e^5) = ", "5"},
		{"sin(90) = ", "1"},
		{"cos(0) = ", "1"},
		{"log5(25) + log5(5) = ", "3"}
	};

	const std::vector<std::pair<QString, QString>> m_tasksHard =
	{
		{"f(x) = x^3 - 4x + 1, f'(2) = ", "8"},
		{"f(x) = e^2x, f'(0) = ", "2"},
		{"f(x) = ln(3x + 1), f'(1) = ", "0.75"}
	};

	Ui::TaskWidgetClass* ui;

};
