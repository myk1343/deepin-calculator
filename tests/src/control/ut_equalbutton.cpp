#include "ut_equalbutton.h"
#include "../../src/control/equalbutton.h"

Ut_EqualButton::Ut_EqualButton()
{

}

TEST_F(Ut_EqualButton, init)
{
    EqualButton *m_equalButton = new EqualButton;
    m_equalButton->init();
    ASSERT_EQ(m_equalButton->m_font.pixelSize(), 36);
}

TEST_F(Ut_EqualButton, mousePressEvent)
{
    EqualButton *m_equalButton = new EqualButton;
    QMouseEvent *m = new QMouseEvent(QMouseEvent::Type::MouseButtonPress,
                                     m_equalButton->pos(), Qt::MouseButton::LeftButton,
                                     Qt::MouseButton::NoButton, Qt::KeyboardModifier::NoModifier);
    m_equalButton->mousePressEvent(m);
    ASSERT_TRUE(m_equalButton->m_isPress);
    delete m;
}

TEST_F(Ut_EqualButton, mouseReleaseEvent)
{
    EqualButton *m_equalButton = new EqualButton;
    QMouseEvent *m = new QMouseEvent(QMouseEvent::Type::MouseButtonRelease,
                                     m_equalButton->pos(), Qt::MouseButton::LeftButton,
                                     Qt::MouseButton::NoButton, Qt::KeyboardModifier::NoModifier);
    m_equalButton->mouseReleaseEvent(m);
    ASSERT_FALSE(m_equalButton->m_isPress);
    delete m;
}

TEST_F(Ut_EqualButton, enterEvent)
{
    EqualButton *m_equalButton = new EqualButton;
    QEvent *e = new QEvent(QEvent::Type::Enter);
    m_equalButton->enterEvent(e);
    ASSERT_TRUE(m_equalButton->m_isHover);
    delete e;
}

TEST_F(Ut_EqualButton, leaveEvent)
{
    EqualButton *m_equalButton = new EqualButton;
    QEvent *e = new QEvent(QEvent::Type::Leave);
    m_equalButton->leaveEvent(e);
    ASSERT_FALSE(m_equalButton->m_isHover);
    delete e;
}

bool stub_focus_equal()
{
    return true;
}

TEST_F(Ut_EqualButton, paintEvent)
{
    EqualButton *m_equalButton = new EqualButton();
    QPaintEvent *event = new QPaintEvent(m_equalButton->rect());
    DGuiApplicationHelper::instance()->setThemeType(DGuiApplicationHelper::ColorType::LightType);
    m_equalButton->setEnabled(true);
    m_equalButton->m_isHover = true;
    m_equalButton->m_isPress = false;
    m_equalButton->paintEvent(event);
    m_equalButton->update();
    DGuiApplicationHelper::instance()->setThemeType(DGuiApplicationHelper::ColorType::DarkType);
    m_equalButton->paintEvent(event);
    m_equalButton->m_isHover = false;
    m_equalButton->m_isPress = true;
    m_equalButton->paintEvent(event);
    m_equalButton->update();
    m_equalButton->m_isHover = false;
    m_equalButton->m_isPress = false;
    m_equalButton->paintEvent(event);
    m_equalButton->update();

    //focus状态
    Stub stub;
    stub.set(ADDR(EqualButton, hasFocus), stub_focus_equal);
    m_equalButton->m_isHover = true;
    m_equalButton->m_isPress = false;
    m_equalButton->paintEvent(event);
    m_equalButton->update();
    m_equalButton->paintEvent(event);
    m_equalButton->m_isHover = false;
    m_equalButton->m_isPress = true;
    m_equalButton->paintEvent(event);
    m_equalButton->update();
    m_equalButton->m_isHover = false;
    m_equalButton->m_isPress = false;
    m_equalButton->paintEvent(event);
    m_equalButton->update();
    //无ASSERT
    delete event;
}

TEST_F(Ut_EqualButton, keyPressEvent)
{
    EqualButton *m_equalButton = new EqualButton;
    QKeyEvent *k = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    QKeyEvent *k1 = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
    QKeyEvent *k2 = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
    QKeyEvent *k3 = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    QKeyEvent *k4 = new QKeyEvent(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);
    QKeyEvent *k5 = new QKeyEvent(QEvent::KeyPress, Qt::Key_1, Qt::NoModifier);
    m_equalButton->keyPressEvent(k);
    m_equalButton->keyPressEvent(k1);
    m_equalButton->keyPressEvent(k2);
    m_equalButton->keyPressEvent(k3);
    m_equalButton->keyPressEvent(k4);
    m_equalButton->keyPressEvent(k5);
    delete k;
    delete k1;
    delete k2;
    delete k3;
    delete k4;
    delete k5;
    //无ASSERT
}
