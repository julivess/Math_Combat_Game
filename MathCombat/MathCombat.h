#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MathCombat.h"
#include "Utils.h"
#include "GameScene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MathCombatClass; };
QT_END_NAMESPACE

class MathCombat : public QMainWindow
{
	Q_OBJECT

public:
	MathCombat(QWidget* parent = nullptr);
	~MathCombat();

	bool IsLevelPassed(); //пройлен ли этот уровень 

	void ShowFirstLevel();
	void ShowSecondLevel();
	void ShowThirdLevel();

	void ShowCongratulation();


public slots:
	void StartNewGame();
	void StartCombat(Difficulty diff);
	void EndCombat(bool result); 

private:
	void ContinueGame();
	void ShowErrorDialog();

	int currentLevel = 1;
	int height;
	int width;

	GameScene* m_scene;

	Ui::MathCombatClass* ui;
};
