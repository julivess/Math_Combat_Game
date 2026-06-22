#include "FirstLevelWidget.h"
#include "Monster.h"

FirstLevelWidget::FirstLevelWidget(QWidget* parent)
	: QWidget(parent)
	, m_ui(new Ui::FirstLevelWidgetClass())
{
	m_ui->setupUi(this);

	// Нужно чтобы сцена получала события с клавиатуры
	m_ui->graphicsView->setFocus();
	m_ui->graphicsView->setFocusPolicy(Qt::StrongFocus);

	m_ui->graphicsView->setTransformationAnchor(
		QGraphicsView::NoAnchor);

	m_ui->graphicsView->setResizeAnchor(
		QGraphicsView::NoAnchor);

	m_scene = new GameScene({{new Monster(Monster::Difficulty::Easy, this), QPointF{900, 485}}}, ":/MathCombat/Resource/Level1.png", this);

	m_ui->graphicsView->setScene(m_scene);

	connect(m_scene, &GameScene::CombatSignal, this, &FirstLevelWidget::CombatSignal);

}

FirstLevelWidget::~FirstLevelWidget()
{
	delete m_ui;
}
