/****************************************************************************
** Meta object code from reading C++ file 'seralanalysis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../seralanalysis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'seralanalysis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_seralAnalysis_t {
    QByteArrayData data[13];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_seralAnalysis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_seralAnalysis_t qt_meta_stringdata_seralAnalysis = {
    {
QT_MOC_LITERAL(0, 0, 13), // "seralAnalysis"
QT_MOC_LITERAL(1, 14, 6), // "sigGro"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "type"
QT_MOC_LITERAL(4, 27, 6), // "float*"
QT_MOC_LITERAL(5, 34, 3), // "gro"
QT_MOC_LITERAL(6, 38, 13), // "slotSeralRead"
QT_MOC_LITERAL(7, 52, 20), // "slot_Receive_CanData"
QT_MOC_LITERAL(8, 73, 5), // "CanCH"
QT_MOC_LITERAL(9, 79, 2), // "id"
QT_MOC_LITERAL(10, 82, 6), // "datAry"
QT_MOC_LITERAL(11, 89, 16), // "slotGyroRangeSet"
QT_MOC_LITERAL(12, 106, 5) // "range"

    },
    "seralAnalysis\0sigGro\0\0type\0float*\0gro\0"
    "slotSeralRead\0slot_Receive_CanData\0"
    "CanCH\0id\0datAry\0slotGyroRangeSet\0range"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_seralAnalysis[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   39,    2, 0x0a /* Public */,
       7,    3,   40,    2, 0x0a /* Public */,
      11,    1,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QByteArray,    8,    9,   10,
    QMetaType::Void, QMetaType::Float,   12,

       0        // eod
};

void seralAnalysis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        seralAnalysis *_t = static_cast<seralAnalysis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigGro((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float*(*)>(_a[2]))); break;
        case 1: _t->slotSeralRead(); break;
        case 2: _t->slot_Receive_CanData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 3: _t->slotGyroRangeSet((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (seralAnalysis::*_t)(QString , float * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&seralAnalysis::sigGro)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject seralAnalysis::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_seralAnalysis.data,
      qt_meta_data_seralAnalysis,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *seralAnalysis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *seralAnalysis::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_seralAnalysis.stringdata0))
        return static_cast<void*>(const_cast< seralAnalysis*>(this));
    return QObject::qt_metacast(_clname);
}

int seralAnalysis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void seralAnalysis::sigGro(QString _t1, float * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
