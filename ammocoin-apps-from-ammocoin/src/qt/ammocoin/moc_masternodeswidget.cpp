/****************************************************************************
** Meta object code from reading C++ file 'masternodeswidget.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "qt/ammocoin/masternodeswidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'masternodeswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.18. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MasterNodesWidget_t {
    QByteArrayData data[19];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MasterNodesWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MasterNodesWidget_t qt_meta_stringdata_MasterNodesWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "MasterNodesWidget"
QT_MOC_LITERAL(1, 18, 20), // "onCoinControlClicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 17), // "onCreateMNClicked"
QT_MOC_LITERAL(4, 58, 17), // "onStartAllClicked"
QT_MOC_LITERAL(5, 76, 4), // "type"
QT_MOC_LITERAL(6, 81, 11), // "changeTheme"
QT_MOC_LITERAL(7, 93, 12), // "isLightTheme"
QT_MOC_LITERAL(8, 106, 8), // "QString&"
QT_MOC_LITERAL(9, 115, 5), // "theme"
QT_MOC_LITERAL(10, 121, 11), // "onMNClicked"
QT_MOC_LITERAL(11, 133, 11), // "QModelIndex"
QT_MOC_LITERAL(12, 145, 5), // "index"
QT_MOC_LITERAL(13, 151, 15), // "onEditMNClicked"
QT_MOC_LITERAL(14, 167, 17), // "onDeleteMNClicked"
QT_MOC_LITERAL(15, 185, 15), // "onInfoMNClicked"
QT_MOC_LITERAL(16, 201, 15), // "updateListState"
QT_MOC_LITERAL(17, 217, 20), // "updateModelAndInform"
QT_MOC_LITERAL(18, 238, 10) // "informText"

    },
    "MasterNodesWidget\0onCoinControlClicked\0"
    "\0onCreateMNClicked\0onStartAllClicked\0"
    "type\0changeTheme\0isLightTheme\0QString&\0"
    "theme\0onMNClicked\0QModelIndex\0index\0"
    "onEditMNClicked\0onDeleteMNClicked\0"
    "onInfoMNClicked\0updateListState\0"
    "updateModelAndInform\0informText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MasterNodesWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    1,   66,    2, 0x08 /* Private */,
       6,    2,   69,    2, 0x08 /* Private */,
      10,    1,   74,    2, 0x08 /* Private */,
      13,    0,   77,    2, 0x08 /* Private */,
      14,    0,   78,    2, 0x08 /* Private */,
      15,    0,   79,    2, 0x08 /* Private */,
      16,    0,   80,    2, 0x08 /* Private */,
      17,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 8,    7,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

void MasterNodesWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MasterNodesWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onCoinControlClicked(); break;
        case 1: _t->onCreateMNClicked(); break;
        case 2: _t->onStartAllClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changeTheme((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->onMNClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->onEditMNClicked(); break;
        case 6: _t->onDeleteMNClicked(); break;
        case 7: _t->onInfoMNClicked(); break;
        case 8: _t->updateListState(); break;
        case 9: _t->updateModelAndInform((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MasterNodesWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<PWidget::staticMetaObject>(),
    qt_meta_stringdata_MasterNodesWidget.data,
    qt_meta_data_MasterNodesWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MasterNodesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MasterNodesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MasterNodesWidget.stringdata0))
        return static_cast<void*>(this);
    return PWidget::qt_metacast(_clname);
}

int MasterNodesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
