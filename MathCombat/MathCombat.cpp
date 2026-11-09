#include "MathCombat.h"
#include <QMessageBox>
#include <QScreen>
#include <QDialog>
#include <QSettings>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

MathCombat::MathCombat(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MathCombatClass())
{
	ui->setupUi(this);

	LoadProgress();

	ui->previewWidget->SetContinueVisible(hasSavedProgress);

	connect(ui->previewWidget, &PreviewWidget::ContinueSavedGame, this, &MathCombat::ContinueSavedGame);

	// Нужно чтобы сцена получала события с клавиатуры

	ui->graphicsView->setFocus();
	ui->graphicsView->setFocusPolicy(Qt::StrongFocus);

	ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);

	ui->graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);

	CreateHUD();
	UpdateHUD();

	ui->stackedWidget->setCurrentWidget(ui->previewWidget);
	connect(ui->previewWidget, &PreviewWidget::StartNewGame, this, &MathCombat::StartNewGame);
	connect(ui->taskWidget, &TaskWidget::FightIsOver, this, &MathCombat::EndCombat);
	connect(ui->taskWidget, &TaskWidget::Exit, this, &MathCombat::ShowPreview);
	connect(ui->taskWidget, &TaskWidget::RestartLevel, this, &MathCombat::RestartLevel);
}

MathCombat::~MathCombat()
{
	delete ui;
}

bool MathCombat::IsLevelPassed()
{
	return m_scene->AllMonstersDefeated();
}

void MathCombat::ShowFirstLevel()
{
	currentLevel = 1;
	ui->graphicsView->setScene(nullptr);
	if (m_scene)
	{
		m_scene->deleteLater();
	}
	m_scene = new GameScene({ {new Monster(Difficulty::Easy), QPointF{900, 485}} }, ":/MathCombat/Resource/Level1.png", QPoint{ 120, 550 }, this);
	connect(m_scene, &GameScene::CombatSignal, this, &MathCombat::StartCombat);
	ui->graphicsView->setScene(m_scene);
	UpdateHUD();

}

void MathCombat::ShowSecondLevel()
{
	currentLevel = 2;
	ui->graphicsView->setScene(nullptr);
	if (m_scene)
	{
		m_scene->deleteLater();
	}

	m_scene = new GameScene({ {new Monster(Difficulty::Medium), QPointF{600, 470}},
													 {new Monster(Difficulty::Medium), QPointF{1200, 470}} },
		":/MathCombat/Resource/Level3.png", QPoint{ 120, 600 }, this);

	connect(m_scene, &GameScene::CombatSignal, this, &MathCombat::StartCombat);
	ui->graphicsView->setScene(m_scene);
	UpdateHUD();
}

void MathCombat::ShowThirdLevel()
{
	currentLevel = 3;
	ui->graphicsView->setScene(nullptr);
	if (m_scene)
	{
		m_scene->deleteLater();
	}

	m_scene = new GameScene({ {new Monster(Difficulty::Hard), QPointF{800, 420}} }, ":/MathCombat/Resource/level2.png", QPoint{ 120, 550 }, this);

	connect(m_scene, &GameScene::CombatSignal, this, &MathCombat::StartCombat);
	ui->graphicsView->setScene(m_scene);
	UpdateHUD();

}

void MathCombat::ShowCongratulation()
{
	QDialog* dialog = new QDialog(this);
	//dialog->setWindowTitle("Поздравляем!");
	dialog->setFixedSize(700, 550);
	dialog->setModal(true);

	// Создаем вертикальный layout
	QVBoxLayout* layout = new QVBoxLayout(dialog);
	layout->setSpacing(20);
	layout->setContentsMargins(30, 30, 30, 30);

	// Текст поздравления
	QString congratulationText =
		"ПОЗДРАВЛЯЕМ!\n\n"
		"Вы победили всех монстров\n"
		"и прошли MATH COMBAT!\n\n";

	QLabel* label = new QLabel(congratulationText);
	label->setAlignment(Qt::AlignCenter);
	label->setProperty("style_type", "TASK_LABEL");
	// Кнопка закрытия
	QPushButton* closeButton = new QPushButton("✕ Закрыть");
	closeButton->setFixedSize(200, 70);
	closeButton->setProperty("style_type", "ANSWER_BUTTON");
	// Подключаем кнопку к закрытию диалога
	QObject::connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);

	// Добавляем виджеты в layout
	layout->addWidget(label);
	layout->addWidget(closeButton, 0, Qt::AlignCenter);

	// Показываем диалог
	dialog->exec();

	// Автоматическое удаление после закрытия
	dialog->deleteLater();

}


void MathCombat::StartCombat(Difficulty diff)
{
	ui->stackedWidget->setCurrentWidget(ui->taskWidget);
	ui->taskWidget->ShowTaskByDifficultyLevel(diff);
	UpdateHUD();
}

void MathCombat::EndCombat(bool result)
{
   if (result)
   {
       m_scene->ResolveCombat(true);
			 UpdateHUD();
       ContinueGame();
   }
   else
   {
       lives--;
       UpdateHUD();
       SaveProgress();

       if (lives <= 0)
       {
           GameOver();
       }
   }
	 
}

void MathCombat::ShowPreview()
{
	ui->stackedWidget->setCurrentWidget(ui->previewWidget);
}

void MathCombat::RestartLevel()
{
	if (currentLevel == 1)
	{
		ShowFirstLevel();
	}
	else if (currentLevel == 2)
	{
		ShowSecondLevel();
	}
	else if (currentLevel == 3)
	{
		ShowThirdLevel();
	}
	
	SaveProgress();
	ui->stackedWidget->setCurrentWidget(ui->levelsWidget);
}

void MathCombat::CreateHUD()
{
    m_hud = new QWidget(ui->graphicsView);
    m_hud->setAttribute(Qt::WA_TransparentForMouseEvents);

    QHBoxLayout* layout = new QHBoxLayout(m_hud);
    layout->setContentsMargins(15, 10, 15, 10);
    layout->setSpacing(20);

    m_levelLabel = new QLabel(m_hud);
    m_levelLabel->setProperty("style_type", "LEVEL_LABEL");
    m_levelLabel->setMinimumSize(180, 45);
    m_levelLabel->setAlignment(Qt::AlignCenter);

   

    m_livesLabel = new QLabel(m_hud);
    m_livesLabel->setProperty("style_type", "LIVES_LABEL");
    m_livesLabel->setMinimumSize(180, 45);
    m_livesLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(m_levelLabel);
    layout->addStretch();
    layout->addWidget(m_livesLabel);

    UpdateHUDGeometry();

    m_hud->show();
    m_hud->raise();

    UpdateHUD();
}

void MathCombat::UpdateHUD()
{
	m_levelLabel->setText(" УРОВЕНЬ: " + QString::number(currentLevel));
  QString hearts;

   for (int i = 0; i < MAX_LIVES; i++)
   {
      if (i < lives)
          hearts += "♥ ";
      else
          hearts += "♡ ";
   }

   m_livesLabel->setText("ЖИЗНИ: " + hearts);
}

void MathCombat::UpdateHUDGeometry()
{
	if (!m_hud)
		return;
  m_hud->setGeometry(0, 0, 600, 75);

  m_hud->raise();
}

void MathCombat::SaveProgress()
{
	 QSettings settings("MathCombat", "Game");

   settings.setValue("currentLevel", currentLevel);
   settings.setValue("lives", lives);
   settings.setValue("hasProgress", true);

   settings.sync();

	 hasSavedProgress = true;
	 ui->previewWidget->SetContinueVisible(true);
}

void MathCombat::LoadProgress()
{
	 QSettings settings("MathCombat", "Game");

   hasSavedProgress =
       settings.value("hasProgress", false).toBool();

   currentLevel =
       settings.value("currentLevel", 1).toInt();

   lives =
       settings.value("lives", MAX_LIVES).toInt();

   if (currentLevel < 1 || currentLevel > 3 ||
       lives < 1 || lives > MAX_LIVES)
   {
       currentLevel = 1;
       lives = MAX_LIVES;
       hasSavedProgress = false;
   }
}

void MathCombat::GameOver()
{
    // Удаляем сохранённый прогресс
    QSettings settings("MathCombat", "Game");
    settings.clear();
    settings.sync();

    hasSavedProgress = false;
    ui->previewWidget->SetContinueVisible(false);

    // Создаём диалог
    QDialog dialog(this);
    dialog.setWindowTitle("Игра окончена");
    dialog.setFixedSize(420, 280);
    dialog.setModal(true);


    // Основной текст
    QLabel* message = new QLabel(
        "У вас закончились жизни!\n"
        "Попробуйте ещё раз!",
        &dialog
    );

    message->setProperty("style_type", "RULE_LABEL");
    message->setAlignment(Qt::AlignCenter);
    message->setWordWrap(true);

    // Кнопка возврата в меню
    QPushButton* menuButton = new QPushButton(
        "ВЕРНУТЬСЯ В МЕНЮ", &dialog
    );

    menuButton->setProperty("style_type", "ANSWER_BUTTON");
    menuButton->setCursor(Qt::PointingHandCursor);

    connect(menuButton, &QPushButton::clicked,
        &dialog, &QDialog::accept);

    // Расположение элементов
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->setContentsMargins(25, 50, 25, 50);
    layout->setSpacing(22);

    layout->addWidget(message);
    layout->addStretch();
    layout->addWidget(menuButton);


    // Показываем диалог и ждём его закрытия
    dialog.exec();

    // Сбрасываем прогресс текущей игры
    lives = MAX_LIVES;
    currentLevel = 1;

		UpdateHUD();

    // Возвращаем игрока в главное меню
    ui->stackedWidget->setCurrentWidget(ui->previewWidget);
}

void MathCombat::ContinueSavedGame()
{
	if (!hasSavedProgress)
		return;

  if (currentLevel == 1)
		ShowFirstLevel();

	else if (currentLevel == 2)
    ShowSecondLevel();

	else if (currentLevel == 3)
		ShowThirdLevel();

   UpdateHUD();

    ui->stackedWidget->setCurrentWidget(ui->levelsWidget);
}

void MathCombat::ContinueGame()
{
	if (currentLevel == 1)
	{
		bool thisLevelPassed = IsLevelPassed();
		if (thisLevelPassed) {
			ShowSecondLevel();
			SaveProgress();
		}
	}
	if (currentLevel == 2)
	{
		bool thisLevelPassed = IsLevelPassed();
		if (thisLevelPassed)
		{
			ShowThirdLevel();
			SaveProgress();
		}
		else {
			m_scene->ContinueGame();
		}
	}
	if (currentLevel == 3)
	{
		bool thisLevelPassed = IsLevelPassed();
		if (thisLevelPassed)
		{
			ShowCongratulation();
			ui->stackedWidget->setCurrentWidget(ui->previewWidget);
			ui->previewWidget->SetContinueVisible(false);
			return;
		}
	}
	ui->stackedWidget->setCurrentWidget(ui->levelsWidget);
}

void MathCombat::StartNewGame()
{
	lives = MAX_LIVES;
  currentLevel = 1;

  hasSavedProgress = false;

  QSettings settings("MathCombat", "Game");
  settings.clear();

  SaveProgress();
  UpdateHUD();

  ui->stackedWidget->setCurrentWidget(ui->levelsWidget);

  ShowFirstLevel();
}

