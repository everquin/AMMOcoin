/****************************************************************************
** Meta object code from reading C++ file 'askpassphrasedialog.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "qt/askpassphrasedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'askpassphrasedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.18. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AskPassphraseDialog_t {
    QByteArrayData data[11];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AskPassphraseDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AskPassphraseDialog_t qt_meta_stringdata_AskPassphraseDialog = {
    {
QT_MOC_LITERAL(0, 0, 19), // "AskPassphraseDialog"
QT_MOC_LITERAL(1, 20, 14), // "onWatchClicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "textChanged"
QT_MOC_LITERAL(4, 48, 14), // "warningMessage"
QT_MOC_LITERAL(5, 63, 21), // "errorEncryptingWallet"
QT_MOC_LITERAL(6, 85, 18), // "openStandardDialog"
QT_MOC_LITERAL(7, 104, 5), // "title"
QT_MOC_LITERAL(8, 110, 4), // "body"
QT_MOC_LITERAL(9, 115, 5), // "okBtn"
QT_MOC_LITERAL(10, 121, 9) // "cancelBtn"

    },
    "AskPassphraseDialog\0onWatchClicked\0\0"
    "textChanged\0warningMessage\0"
    "errorEncryptingWallet\0openStandardDialog\0"
    "title\0body\0okBtn\0cancelBtn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AskPassphraseDialog[] = {

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
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    4,   63,    2, 0x08 /* Private */,
       6,    3,   72,    2, 0x28 /* Private | MethodCloned */,
       6,    2,   79,    2, 0x28 /* Private | MethodCloned */,
       6,    1,   84,    2, 0x28 /* Private | MethodCloned */,
       6,    0,   87,    2, 0x28 /* Private | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,   10,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    7,    8,
    QMetaType::Bool, QMetaType::QString,    7,
    QMetaType::Bool,

       0        // eod
};

void AskPassphraseDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AskPassphraseDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onWatchClicked(); break;
        case 1: _t->textChanged(); break;
        case 2: _t->warningMessage(); break;
        case 3: _t->errorEncryptingWallet(); break;
        case 4: { bool _r = _t->openStandardDialog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->openStandardDialog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->openStandardDialog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->openStandardDialog((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->openStandardDialog();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AskPassphraseDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_AskPassphraseDialog.data,
    qt_meta_data_AskPassphraseDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AskPassphraseDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AskPassphraseDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AskPassphraseDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Runnable"))
        return static_cast< Runnable*>(this);
    return QDialog::qt_metacast(_clname);
}

int AskPassphraseDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
