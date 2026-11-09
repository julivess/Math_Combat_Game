#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MathCombat.h"
#include "Utils.h"
#include "GameScene.h"

#include <QSettings>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class MathCombatClass; };
QT_END_NAMESPACE

// Основное окно игры, на котором находятся все виджеты 
class MathCombat : public QMainWindow
{
	Q_OBJECT

public:
	MathCombat(QWidget* parent = nullptr);
	~MathCombat();

	bool IsLevelPassed(); //пройлен ли этот уровень 

	// Функции показывают сцену на уровнях
	void ShowFirstLevel();
	void ShowSecondLevel();
	void ShowThirdLevel();

	// Показывает окно с поздравлениями для пользователя в конце игры
	void ShowCongratulation();


public slots:
	void StartNewGame(); // Начинает новую игру с первого уровня
	void StartCombat(Difficulty diff); // Начинает математический бой с заданным уровнем сложности
	void EndCombat(bool result);  // Обрабатывает результат боя
	void ShowPreview();
	void RestartLevel();

private:
	QWidget* m_hud = nullptr;

	QLabel* m_levelLabel = nullptr;
	QLabel* m_livesLabel = nullptr;

	void CreateHUD();
	void UpdateHUD();
	void UpdateHUDGeometry();
	
	int lives = 3;
	const int MAX_LIVES = 3;


	bool hasSavedProgress = false;

	void SaveProgress();
	void LoadProgress();
	void GameOver();
	void ContinueSavedGame();


	void ContinueGame(); // Продолжить игру

	int currentLevel = 1; // текущий уровень игры

	GameScene* m_scene = nullptr; // сцена

	Ui::MathCombatClass* ui;
};
