/****************************************************************************
** Meta object code from reading C++ file 'votedialog.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "qt/ammocoin/votedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'votedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.18. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VoteDialog_t {
    QByteArrayData data[10];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VoteDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VoteDialog_t qt_meta_stringdata_VoteDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "VoteDialog"
QT_MOC_LITERAL(1, 11, 15), // "onAcceptClicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "onCheckBoxClicked"
QT_MOC_LITERAL(4, 46, 10), // "QCheckBox*"
QT_MOC_LITERAL(5, 57, 8), // "checkBox"
QT_MOC_LITERAL(6, 66, 13), // "QProgressBar*"
QT_MOC_LITERAL(7, 80, 11), // "progressBar"
QT_MOC_LITERAL(8, 92, 9), // "isVoteYes"
QT_MOC_LITERAL(9, 102, 20) // "onMnSelectionClicked"

    },
    "VoteDialog\0onAcceptClicked\0\0"
    "onCheckBoxClicked\0QCheckBox*\0checkBox\0"
    "QProgressBar*\0progressBar\0isVoteYes\0"
    "onMnSelectionClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VoteDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    3,   30,    2, 0x0a /* Public */,
       9,    0,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6, QMetaType::Bool,    5,    7,    8,
    QMetaType::Void,

       0        // eod
};

void VoteDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VoteDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onAcceptClicked(); break;
        case 1: _t->onCheckBoxClicked((*reinterpret_cast< QCheckBox*(*)>(_a[1])),(*reinterpret_cast< QProgressBar*(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->onMnSelectionClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCheckBox* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QProgressBar* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VoteDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_VoteDialog.data,
    qt_meta_data_VoteDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VoteDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VoteDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VoteDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int VoteDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
