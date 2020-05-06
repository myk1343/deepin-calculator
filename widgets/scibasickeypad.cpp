#include <QTimer>

#include <DPalette>
#include <DImageButton>

#include "dthememanager.h"
#include "scibasickeypad.h"

const SciBasicKeyPad::KeyDescription SciBasicKeyPad::keyDescriptions[] = {
    {"page1", Key_2page, 1, 0, 1, 1}, {"π", Key_PI, 1, 1, 1, 1}, {"e", Key_e, 1, 2, 1, 1},
    {"C", Key_Clear, 1, 3, 1, 1},     {"", Key_Backspace, 1, 4, 1, 1},

    {"x²", Key_x2, 2, 0, 1, 1},       {"1/x", Key_Derivative, 2, 1, 1, 1}, {"|x|", Key_Modulus, 2, 2, 1, 1},
    {"exp", Key_exp, 2, 3, 1, 1},     {"mod", Key_mod, 2, 4, 1, 1},

    {"x³", Key_x3, 3, 0, 1, 1},          {"(", Key_Left, 3, 1, 1, 1}, {")", Key_Right, 3, 2, 1, 1},
    {"n!", Key_Factorials, 3, 3, 1, 1},  {"", Key_Div, 3, 4, 1, 1},

    {"xʸ", Key_xy, 4, 0, 1, 1},       {"7", Key_7, 4, 1, 1, 1}, {"8", Key_8, 4, 2, 1, 1},
    {"9", Key_9, 4, 3, 1, 1},         {"", Key_Mult, 4, 4, 1, 1},

    {"10ˣ", Key_10x, 5, 0, 1, 1},       {"4", Key_4, 5, 1, 1, 1}, {"5", Key_5, 5, 2, 1, 1},
    {"6", Key_6, 5, 3, 1, 1},         {"", Key_Min, 5, 4, 1, 1},

    {"log", Key_log, 6, 0, 1, 1},     {"1", Key_1, 6, 1, 1, 1},         {"2", Key_2, 6, 2, 1, 1},
    {"3", Key_3, 6, 3, 1, 1},         {"", Key_Plus, 6, 4, 1, 1},

    {"ln", Key_ln, 7, 0, 1, 1},     {"%", Key_Percent, 7, 1, 1, 1},   {"0", Key_0, 7, 2, 1, 1},
    {".", Key_Point, 7, 3, 1, 1},     {"=", Key_Equal, 7, 4, 1, 1},
};

const SciBasicKeyPad::KeyDescription1 SciBasicKeyPad::keyDescriptions1[] = {
    {"page2", Key_2page, 1, 0, 1, 1}, {"π", Key_PI, 1, 1, 1, 1}, {"e", Key_e, 1, 2, 1, 1},
    {"C", Key_Clear, 1, 3, 1, 1},     {"", Key_Backspace, 1, 4, 1, 1},

    {"√x", Key_sqrt2, 2, 0, 1, 1},       {"1/x", Key_Derivative, 2, 1, 1, 1}, {"|x|", Key_Modulus, 2, 2, 1, 1},
    {"exp", Key_exp, 2, 3, 1, 1},     {"mod", Key_mod, 2, 4, 1, 1},

    {"³√x", Key_sqrt3, 3, 0, 1, 1},          {"(", Key_Left, 3, 1, 1, 1}, {")", Key_Right, 3, 2, 1, 1},
    {"n!", Key_Factorials, 3, 3, 1, 1},  {"", Key_Div, 3, 4, 1, 1},

    {"ʸ√x", Key_yx, 4, 0, 1, 1},       {"7", Key_7, 4, 1, 1, 1}, {"8", Key_8, 4, 2, 1, 1},
    {"9", Key_9, 4, 3, 1, 1},         {"", Key_Mult, 4, 4, 1, 1},

    {"2ˣ", Key_2x, 5, 0, 1, 1},       {"4", Key_4, 5, 1, 1, 1}, {"5", Key_5, 5, 2, 1, 1},
    {"6", Key_6, 5, 3, 1, 1},         {"", Key_Min, 5, 4, 1, 1},

    {"logᵧx", Key_logyx, 6, 0, 1, 1},     {"1", Key_1, 6, 1, 1, 1},         {"2", Key_2, 6, 2, 1, 1},
    {"3", Key_3, 6, 3, 1, 1},         {"", Key_Plus, 6, 4, 1, 1},

    {"eˣ", Key_ex, 7, 0, 1, 1},     {"%", Key_Percent, 7, 1, 1, 1},   {"0", Key_0, 7, 2, 1, 1},
    {".", Key_Point, 7, 3, 1, 1},     {"=", Key_Equal, 7, 4, 1, 1},
};

static DPushButton *createSpecialKeyButton(SciBasicKeyPad::Buttons key)
{
    IconButton *button = new IconButton;

    QString path;
    if (DGuiApplicationHelper::instance()->themeType() == 2)
        path = QString(":/images/%1/").arg("dark");
    else
        path = QString(":/images/%1/").arg("light");

    if (key == SciBasicKeyPad::Key_Div) {
        button->setIconUrl(path + "divide_normal.svg", path + "divide_hover.svg", path + "divide_press.svg");
    } else if (key == SciBasicKeyPad::Key_Mult) {
        button->setIconUrl(path + "x_normal.svg", path + "x_hover.svg", path + "x_press.svg");
    } else if (key == SciBasicKeyPad::Key_Min) {
        button->setIconUrl(path + "-_normal.svg", path + "-_hover.svg", path + "-_press.svg");
    } else if (key == SciBasicKeyPad::Key_Plus) {
        button->setIconUrl(path + "+_normal.svg", path + "+_hover.svg", path + "+_press.svg");
    } else if (key == SciBasicKeyPad::Key_Backspace) {
        button->setIconUrl(path + "clear_normal.svg", path + "clear_hover.svg", path + "clear_press.svg");
    } else if (key == SciBasicKeyPad::Key_Clear) {
        button->setIconUrl(path + "AC_normal.svg", path + "AC_hover.svg", path + "AC_press.svg");
    } else if (key == SciBasicKeyPad::Key_Percent) {
        button->setIconUrl(path + "%_normal.svg", path + "%_hover.svg", path + "%_press.svg");
    }
    //connect(button, &IconButton::updateInterface, this, &SciBasicKeyPad::updateInterface);
    return button;
}

SciBasicKeyPad::SciBasicKeyPad(QWidget *parent)
    : DWidget(parent),
      m_hlayout(new QHBoxLayout(this)),
      m_mapper(new QSignalMapper(this)),
      m_stacklayout(new QStackedLayout),
      m_gridlayout1(new QGridLayout),
      m_gridlayout2(new QGridLayout)
{
    QWidget *page1 = new QWidget(this);
    QWidget *page2 = new QWidget(this);
    page1->setLayout(m_gridlayout1);
    page2->setLayout(m_gridlayout2);
    m_stacklayout->addWidget(page1);
    m_stacklayout->addWidget(page2);
    m_hlayout->addLayout(m_stacklayout);
    m_hlayout->setMargin(0);
    m_hlayout->setSpacing(0);
    m_hlayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(m_hlayout);

    initButtons();
    initUI();

    connect(m_mapper, SIGNAL(mapped(int)), SIGNAL(buttonPressed(int)));
    connect(this, &SciBasicKeyPad::buttonPressed, this,
            &SciBasicKeyPad::turnPage);
    //connect(DThemeManager::instance(), &DThemeManager::themeChanged, this, &SciBasicKeyPad::handleThemeChanged);
}

SciBasicKeyPad::~SciBasicKeyPad()
{
}

DPushButton *SciBasicKeyPad::button(Buttons key)
{
    return m_keys.value(key).first;
}

DSuggestButton *SciBasicKeyPad::button()
{
    //return m_equal;
}

void SciBasicKeyPad::animate(Buttons key)
{
    if (button(key)->text().isEmpty()) {
        IconButton *btn = static_cast<IconButton *>(button(key));
        btn->animate();
    } else {
        if (button(key)->text() == "=") {
            EqualButton *btn = dynamic_cast<EqualButton *>(button(key));
            btn->animate();
        } else {
            TextButton *btn = static_cast<TextButton *>(button(key));
            btn->animate();
        }
    }

}

void SciBasicKeyPad::animate()
{
    //m_equal->setChecked(true);

    //QTimer::singleShot(100, this, [=] { m_equal->setChecked(false); });
}

void SciBasicKeyPad::initButtons()
{
    const int count = sizeof(keyDescriptions) / sizeof(keyDescriptions[0]);
    for (int i = 0; i < count; ++i) {
        const KeyDescription *desc = keyDescriptions + i;
        DPushButton *button;

        if (desc->text.isEmpty()) {
            button = createSpecialKeyButton(desc->button);
        } else {
            if (desc->text == "=")
                button = new EqualButton(desc->text);
            else {
                button = new TextButton(desc->text);
                QFont font = button->font();
                font.setFamily("HelveticaNeue");
                button->setFont(font);
            }
        }

        m_gridlayout1->addWidget(button, desc->row, desc->column, desc->rowcount, desc->columncount,
                                 Qt::AlignHCenter | Qt::AlignBottom);
        const QPair<DPushButton *, const KeyDescription *> hashValue(button, desc);
        m_keys.insert(desc->button, hashValue);

        connect(static_cast<TextButton *>(button), &TextButton::updateInterface, [ = ] {update();});
        connect(button, &DPushButton::clicked, m_mapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
        connect(static_cast<TextButton *>(button), &TextButton::moveLeft, this, &SciBasicKeyPad::moveLeft);
        connect(static_cast<TextButton *>(button), &TextButton::moveRight, this, &SciBasicKeyPad::moveRight);
        m_mapper->setMapping(button, desc->button);
    }
    const int count1 = sizeof(keyDescriptions1) / sizeof(keyDescriptions1[0]);
    for (int i = 0; i < count1; ++i) {
        const KeyDescription1 *desc1 = keyDescriptions1 + i;
        DPushButton *button;

        if (desc1->text.isEmpty()) {
            button = createSpecialKeyButton(desc1->button);
        } else {
            if (desc1->text == "=")
                button = new EqualButton(desc1->text);
            else {
                button = new TextButton(desc1->text);
                QFont font = button->font();
                font.setFamily("HelveticaNeue");
                button->setFont(font);
            }
        }

        m_gridlayout2->addWidget(button, desc1->row, desc1->column, desc1->rowcount, desc1->columncount,
                                 Qt::AlignHCenter | Qt::AlignBottom);
        const QPair<DPushButton *, const KeyDescription1 *> hashValue(button, desc1);
        m_keys1.insert(desc1->button, hashValue);

        connect(static_cast<TextButton *>(button), &TextButton::updateInterface, [ = ] {update();});
        connect(button, &DPushButton::clicked, m_mapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
        connect(static_cast<TextButton *>(button), &TextButton::moveLeft, this, &SciBasicKeyPad::moveLeft);
        connect(static_cast<TextButton *>(button), &TextButton::moveRight, this, &SciBasicKeyPad::moveRight);
        m_mapper->setMapping(button, desc1->button);
    }
}

void SciBasicKeyPad::initUI()
{
    QHashIterator<Buttons, QPair<DPushButton *, const KeyDescription *>> i(m_keys);

    while (i.hasNext()) {
        i.next();
        i.value().first->setFocusPolicy(Qt::NoFocus);
    }

    QHashIterator<Buttons, QPair<DPushButton *, const KeyDescription1 *>> i1(m_keys1);

    while (i1.hasNext()) {
        i1.next();
        i1.value().first->setFocusPolicy(Qt::NoFocus);
    }

    button(Key_Div)->setObjectName("SymbolButton");
    button(Key_Mult)->setObjectName("SymbolButton");
    button(Key_Min)->setObjectName("SymbolButton");
    button(Key_Plus)->setObjectName("SymbolButton");

    this->setContentsMargins(12, 0, 13, 0);
}

void SciBasicKeyPad::buttonThemeChanged(int type)
{
    QString path;
    if (type == 2)
        path = QString(":/images/%1/").arg("dark");
    else
        path = QString(":/images/%1/").arg("light");

    IconButton *btn = static_cast<IconButton *>(button(Key_Div));
    btn->setIconUrl(path + "divide_normal.svg", path + "divide_hover.svg", path + "divide_press.svg");
    btn = static_cast<IconButton *>(button(Key_Mult));
    btn->setIconUrl(path + "x_normal.svg", path + "x_hover.svg", path + "x_press.svg");
    btn = static_cast<IconButton *>(button(Key_Min));
    btn->setIconUrl(path + "-_normal.svg", path + "-_hover.svg", path + "-_press.svg");
    btn = static_cast<IconButton *>(button(Key_Plus));
    btn->setIconUrl(path + "+_normal.svg", path + "+_hover.svg", path + "+_press.svg");
    btn = static_cast<IconButton *>(button(Key_Backspace));
    btn->setIconUrl(path + "clear_normal.svg", path + "clear_hover.svg", path + "clear_press.svg");
}

void SciBasicKeyPad::turnPage(int key)
{
    if (key == Key_2page) {
        if (m_stacklayout->currentIndex() == 0)
            m_stacklayout->setCurrentIndex(1);
        else {
            m_stacklayout->setCurrentIndex(0);
        }
    }
}