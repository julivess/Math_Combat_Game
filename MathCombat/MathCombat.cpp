#include "MathCombat.h"
#include <QMessageBox>
#include <QScreen>

MathCombat::MathCombat(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MathCombatClass())
{
	ui->setupUi(this);

		// Нужно чтобы сцена получала события с клавиатуры

	ui->graphicsView->setFocus();
	ui->graphicsView->setFocusPolicy(Qt::StrongFocus);

	ui->graphicsView->setTransformationAnchor(
		QGraphicsView::NoAnchor);

	ui->graphicsView->setResizeAnchor(
		QGraphicsView::NoAnchor);


	QScreen* screen = QGuiApplication::primaryScreen();
	if (screen)
	{
		QRect geometry = screen->geometry();

		width = geometry.width();
		height = geometry.height();

		ui->graphicsView->setFixedSize(width, height);
	}

	ui->stackedWidget->setCurrentWidget(ui->previewWidget);
	connect(ui->previewWidget, &PreviewWidget::StartNewGame, this, &MathCombat::StartNewGame);
	connect(ui->taskWidget, &TaskWidget::FightIsOver, this, &MathCombat::EndCombat);
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
	m_scene = new GameScene({{new Monster(Difficulty::Easy), QPointF{900, 485}}}, ":/MathCombat/Resource/Level1.png", this);
	connect(m_scene, &GameScene::CombatSignal, this, &MathCombat::StartCombat);
	ui->graphicsView->setScene(m_scene);

}

void MathCombat::ShowSecondLevel()
{
	currentLevel = 2;
	ui->graphicsView->setScene(nullptr);
	if (m_scene)
	{
		m_scene->deleteLater();
	}

	m_scene = new GameScene({{new Monster(Difficulty::Medium), QPointF{600, 430}}, 
		                       {new Monster(Difficulty::Medium), QPointF{1000, 430}}}, ":/MathCombat/Resource/level2.png", this);

	connect(m_scene, &GameScene::CombatSignal, this, &MathCombat::StartCombat);
	ui->graphicsView->setScene(m_scene);
}


void MathCombat::StartCombat(Difficulty diff)
{
	ui->stackedWidget->setCurrentWidget(ui->taskWidget);
	ui->taskWidget->ShowTaskByDifficultyLevel(diff);
}

void MathCombat::EndCombat(bool result)
{
	if (result)
	{
		ContinueGame();
	}
	else {
		ShowErrorDialog();
	}
}

void MathCombat::ContinueGame()
{
	if (currentLevel == 1)
	{
		bool thisLevelPassed = IsLevelPassed();
		if (thisLevelPassed) {
			ShowSecondLevel();
			//ui->stackedWidget->setCurrentWidget(ui->)
		}
	}
	if (currentLevel == 2)
	{
		bool thisLevelPassed = IsLevelPassed();
		if (thisLevelPassed)
		{
			//ShowThirdLevel()
		}
		else {
			m_scene->ContinueGame();
		}
	}
	ui->stackedWidget->setCurrentWidget(ui->levelsWidget);
}

void MathCombat::ShowErrorDialog()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setWindowTitle("Ошибка!");
	msgBox.setText("Произошла ошибка в игре!");
	msgBox.setInformativeText("Что вы хотите сделать?");

	// Создаём кнопки
	QPushButton* restartBtn = msgBox.addButton("Начать заново", QMessageBox::AcceptRole);
	QPushButton* exitBtn = msgBox.addButton("Выход", QMessageBox::RejectRole);

	msgBox.setDefaultButton(restartBtn);

	// Показываем диалог и обрабатываем выбор
	msgBox.exec();

	if (msgBox.clickedButton() == restartBtn) {
		// Перезапуск игры
		if (currentLevel == 1) {
			ShowFirstLevel();
		}
		else if (currentLevel == 2)
		{
			ShowSecondLevel();
		}
		ui->stackedWidget->setCurrentWidget(ui->levelsWidget);
	}
	else if (msgBox.clickedButton() == exitBtn) {
		// Переключение на другой стек виджет
		ui->stackedWidget->setCurrentWidget(ui->previewWidget);
	}
}

void MathCombat::StartNewGame()
{
	ui->stackedWidget->setCurrentWidget(ui->levelsWidget);
	ShowFirstLevel();
}

