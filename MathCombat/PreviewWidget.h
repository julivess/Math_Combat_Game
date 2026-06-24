#pragma once

#include <QWidget>
#include "ui_PreviewWidget.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class PreviewWidgetClass; };
QT_END_NAMESPACE

class PreviewWidget : public QWidget
{
	Q_OBJECT

public:
	PreviewWidget(QWidget* parent = nullptr);
	~PreviewWidget();
	void ShowRules();

signals:
	void StartNewGame();//Сигнал, что пользователь нажал на кнопку Начать новую игру

private:
	Ui::PreviewWidgetClass* ui;
};
