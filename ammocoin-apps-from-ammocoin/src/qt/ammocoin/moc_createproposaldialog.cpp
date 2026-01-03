/****************************************************************************
** Meta object code from reading C++ file 'createproposaldialog.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "qt/ammocoin/createproposaldialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createproposaldialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.18. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CreateProposalDialog_t {
    QByteArrayData data[13];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateProposalDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateProposalDialog_t qt_meta_stringdata_CreateProposalDialog = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CreateProposalDialog"
QT_MOC_LITERAL(1, 21, 13), // "onNextClicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 13), // "onBackClicked"
QT_MOC_LITERAL(4, 50, 15), // "propNameChanged"
QT_MOC_LITERAL(5, 66, 7), // "newText"
QT_MOC_LITERAL(6, 74, 14), // "propUrlChanged"
QT_MOC_LITERAL(7, 89, 17), // "propAmountChanged"
QT_MOC_LITERAL(8, 107, 18), // "propaddressChanged"
QT_MOC_LITERAL(9, 126, 17), // "onAddrListClicked"
QT_MOC_LITERAL(10, 144, 19), // "onGenAddressClicked"
QT_MOC_LITERAL(11, 164, 18), // "monthsEditDeselect"
QT_MOC_LITERAL(12, 183, 1) // "i"

    },
    "CreateProposalDialog\0onNextClicked\0\0"
    "onBackClicked\0propNameChanged\0newText\0"
    "propUrlChanged\0propAmountChanged\0"
    "propaddressChanged\0onAddrListClicked\0"
    "onGenAddressClicked\0monthsEditDeselect\0"
    "i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateProposalDialog[] = {

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
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    1,   61,    2, 0x0a /* Public */,
       6,    1,   64,    2, 0x0a /* Public */,
       7,    1,   67,    2, 0x0a /* Public */,
       8,    1,   70,    2, 0x0a /* Public */,
       9,    0,   73,    2, 0x0a /* Public */,
      10,    0,   74,    2, 0x0a /* Public */,
      11,    1,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void CreateProposalDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreateProposalDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onNextClicked(); break;
        case 1: _t->onBackClicked(); break;
        case 2: _t->propNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->propUrlChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->propAmountChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: { bool _r = _t->propaddressChanged((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->onAddrListClicked(); break;
        case 7: _t->onGenAddressClicked(); break;
        case 8: _t->monthsEditDeselect((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CreateProposalDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CreateProposalDialog.data,
    qt_meta_data_CreateProposalDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CreateProposalDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateProposalDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CreateProposalDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CreateProposalDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
