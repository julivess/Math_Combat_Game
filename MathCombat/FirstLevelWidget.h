#pragma once

#include <QWidget>
#include "ui_FirstLevelWidget.h"
#include "GameScene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FirstLevelWidgetClass; };
QT_END_NAMESPACE

class FirstLevelWidget : public QWidget
{
	Q_OBJECT

public:
	FirstLevelWidget(QWidget *parent = nullptr);
	~FirstLevelWidget();

signals:
	void CombatSignal();
private:
	Ui::FirstLevelWidgetClass *m_ui;
	GameScene* m_scene;
};
