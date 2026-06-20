#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MathCombat.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MathCombatClass; };
QT_END_NAMESPACE

class MathCombat : public QMainWindow
{
    Q_OBJECT

public:
    MathCombat(QWidget *parent = nullptr);
    ~MathCombat();

public slots:
  void StartNewGame();

private:
    Ui::MathCombatClass* ui;
};
