#include "ut_programmerarrowdelegate.h"

#include "../../src/views/programmeritemwidget.h"
#include "../../src/views/memorylistwidget.h"
#include <QPainter>

Ut_ProgrammerArrowDelegate::Ut_ProgrammerArrowDelegate()
{

}

void Ut_ProgrammerArrowDelegate::SetUp()
{
    m_memoryItemDelegate = new ProgrammerArrowDelegate;
}

void Ut_ProgrammerArrowDelegate::TearDown()
{
    delete m_memoryItemDelegate;
}

//bool stub_focus_proarrowdelegateT()
//{
//    return true;
//}

bool stub_focus_proarrowdelegateF()
{
    return false;
}

TEST_F(Ut_ProgrammerArrowDelegate, paint)
{
    MemoryListWidget *listwidget = new MemoryListWidget;
    listwidget->setItemDelegate(m_memoryItemDelegate);

    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(20, 20));
    ProgrammerItemWidget *widget = new ProgrammerItemWidget("WORD");
    widget->setFixedSize(QSize(20, 20));

    listwidget->insertItem(0, item);
    listwidget->setItemWidget(item, widget);

    QPainter *painter = new QPainter();
    QStyleOptionViewItem option;
    option.styleObject = listwidget;
    QModelIndex index;
    Stub stub;
    stub.set(ADDR(MemoryListWidget, hasFocus), stub_focus_proarrowdelegateF);
//    Stub stub1;
//    stub1.set(ADDR(MemoryListWidget, rect), stub_rect_memdelegate);
    DGuiApplicationHelper::instance()->setThemeType(DGuiApplicationHelper::ColorType::DarkType);
    m_memoryItemDelegate->paint(painter, option, index);
    DGuiApplicationHelper::instance()->setThemeType(DGuiApplicationHelper::ColorType::LightType);
    m_memoryItemDelegate->paint(painter, option, index);
    delete painter;
}

TEST_F(Ut_ProgrammerArrowDelegate, updateEditorGeometry)
{
    m_memoryItemDelegate->updateEditorGeometry(new QWidget(), QStyleOptionViewItem(), QModelIndex());
}
