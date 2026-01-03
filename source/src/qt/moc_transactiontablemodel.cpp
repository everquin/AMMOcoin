/****************************************************************************
** Meta object code from reading C++ file 'transactiontablemodel.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "qt/transactiontablemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transactiontablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.18. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TransactionTableModel_t {
    QByteArrayData data[18];
    char stringdata0[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TransactionTableModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TransactionTableModel_t qt_meta_stringdata_TransactionTableModel = {
    {
QT_MOC_LITERAL(0, 0, 21), // "TransactionTableModel"
QT_MOC_LITERAL(1, 22, 8), // "txLoaded"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 4), // "hash"
QT_MOC_LITERAL(4, 37, 6), // "txType"
QT_MOC_LITERAL(5, 44, 8), // "txStatus"
QT_MOC_LITERAL(6, 53, 9), // "txArrived"
QT_MOC_LITERAL(7, 63, 11), // "isCoinStake"
QT_MOC_LITERAL(8, 75, 10), // "isMNReward"
QT_MOC_LITERAL(9, 86, 11), // "isCSAnyType"
QT_MOC_LITERAL(10, 98, 17), // "updateTransaction"
QT_MOC_LITERAL(11, 116, 6), // "status"
QT_MOC_LITERAL(12, 123, 15), // "showTransaction"
QT_MOC_LITERAL(13, 139, 19), // "updateConfirmations"
QT_MOC_LITERAL(14, 159, 17), // "updateDisplayUnit"
QT_MOC_LITERAL(15, 177, 23), // "updateAmountColumnTitle"
QT_MOC_LITERAL(16, 201, 31), // "setProcessingQueuedTransactions"
QT_MOC_LITERAL(17, 233, 5) // "value"

    },
    "TransactionTableModel\0txLoaded\0\0hash\0"
    "txType\0txStatus\0txArrived\0isCoinStake\0"
    "isMNReward\0isCSAnyType\0updateTransaction\0"
    "status\0showTransaction\0updateConfirmations\0"
    "updateDisplayUnit\0updateAmountColumnTitle\0"
    "setProcessingQueuedTransactions\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransactionTableModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x06 /* Public */,
       6,    4,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    3,   65,    2, 0x0a /* Public */,
      13,    0,   72,    2, 0x0a /* Public */,
      14,    0,   73,    2, 0x0a /* Public */,
      15,    0,   74,    2, 0x0a /* Public */,
      16,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    3,    7,    8,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Bool,    3,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,

       0        // eod
};

void TransactionTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TransactionTableModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->txLoaded((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 1: _t->txArrived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3])),(*reinterpret_cast< const bool(*)>(_a[4]))); break;
        case 2: _t->updateTransaction((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: _t->updateConfirmations(); break;
        case 4: _t->updateDisplayUnit(); break;
        case 5: _t->updateAmountColumnTitle(); break;
        case 6: _t->setProcessingQueuedTransactions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TransactionTableModel::*)(const QString & , const int , const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TransactionTableModel::txLoaded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TransactionTableModel::*)(const QString & , const bool , const bool , const bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TransactionTableModel::txArrived)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TransactionTableModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractTableModel::staticMetaObject>(),
    qt_meta_stringdata_TransactionTableModel.data,
    qt_meta_data_TransactionTableModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TransactionTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransactionTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TransactionTableModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int TransactionTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TransactionTableModel::txLoaded(const QString & _t1, const int _t2, const int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TransactionTableModel::txArrived(const QString & _t1, const bool _t2, const bool _t3, const bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
