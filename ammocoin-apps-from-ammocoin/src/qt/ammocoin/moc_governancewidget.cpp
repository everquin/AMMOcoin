/****************************************************************************
** Meta object code from reading C++ file 'governancewidget.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "qt/ammocoin/governancewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'governancewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.18. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Delegate_t {
    QByteArrayData data[1];
    char stringdata0[9];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Delegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Delegate_t qt_meta_stringdata_Delegate = {
    {
QT_MOC_LITERAL(0, 0, 8) // "Delegate"

    },
    "Delegate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Delegate[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Delegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject Delegate::staticMetaObject = { {
    QMetaObject::SuperData::link<QStyledItemDelegate::staticMetaObject>(),
    qt_meta_stringdata_Delegate.data,
    qt_meta_data_Delegate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Delegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Delegate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Delegate.stringdata0))
        return static_cast<void*>(this);
    return QStyledItemDelegate::qt_metacast(_clname);
}

int Delegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_GovernanceWidget_t {
    QByteArrayData data[18];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GovernanceWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GovernanceWidget_t qt_meta_stringdata_GovernanceWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "GovernanceWidget"
QT_MOC_LITERAL(1, 17, 13), // "tierTwoSynced"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "IsSync"
QT_MOC_LITERAL(4, 39, 15), // "onFilterChanged"
QT_MOC_LITERAL(5, 55, 5), // "value"
QT_MOC_LITERAL(6, 61, 18), // "chainHeightChanged"
QT_MOC_LITERAL(7, 80, 6), // "height"
QT_MOC_LITERAL(8, 87, 20), // "onVoteForPropClicked"
QT_MOC_LITERAL(9, 108, 12), // "ProposalInfo"
QT_MOC_LITERAL(10, 121, 12), // "proposalInfo"
QT_MOC_LITERAL(11, 134, 19), // "onCreatePropClicked"
QT_MOC_LITERAL(12, 154, 13), // "onMenuClicked"
QT_MOC_LITERAL(13, 168, 13), // "ProposalCard*"
QT_MOC_LITERAL(14, 182, 4), // "card"
QT_MOC_LITERAL(15, 187, 9), // "onCopyUrl"
QT_MOC_LITERAL(16, 197, 13), // "onOpenClicked"
QT_MOC_LITERAL(17, 211, 17) // "onMoreInfoClicked"

    },
    "GovernanceWidget\0tierTwoSynced\0\0IsSync\0"
    "onFilterChanged\0value\0chainHeightChanged\0"
    "height\0onVoteForPropClicked\0ProposalInfo\0"
    "proposalInfo\0onCreatePropClicked\0"
    "onMenuClicked\0ProposalCard*\0card\0"
    "onCopyUrl\0onOpenClicked\0onMoreInfoClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GovernanceWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       4,    1,   62,    2, 0x0a /* Public */,
       6,    1,   65,    2, 0x0a /* Public */,
       8,    1,   68,    2, 0x0a /* Public */,
      11,    0,   71,    2, 0x0a /* Public */,
      12,    1,   72,    2, 0x0a /* Public */,
      15,    0,   75,    2, 0x0a /* Public */,
      16,    0,   76,    2, 0x0a /* Public */,
      17,    0,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GovernanceWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GovernanceWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->tierTwoSynced((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->onFilterChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->chainHeightChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onVoteForPropClicked((*reinterpret_cast< const ProposalInfo(*)>(_a[1]))); break;
        case 4: _t->onCreatePropClicked(); break;
        case 5: _t->onMenuClicked((*reinterpret_cast< ProposalCard*(*)>(_a[1]))); break;
        case 6: _t->onCopyUrl(); break;
        case 7: _t->onOpenClicked(); break;
        case 8: _t->onMoreInfoClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ProposalCard* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GovernanceWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<PWidget::staticMetaObject>(),
    qt_meta_stringdata_GovernanceWidget.data,
    qt_meta_data_GovernanceWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GovernanceWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GovernanceWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GovernanceWidget.stringdata0))
        return static_cast<void*>(this);
    return PWidget::qt_metacast(_clname);
}

int GovernanceWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
