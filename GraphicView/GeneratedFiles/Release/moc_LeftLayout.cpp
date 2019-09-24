/****************************************************************************
** Meta object code from reading C++ file 'LeftLayout.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LeftLayout.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LeftLayout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LeftLayout_t {
    QByteArrayData data[14];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LeftLayout_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LeftLayout_t qt_meta_stringdata_LeftLayout = {
    {
QT_MOC_LITERAL(0, 0, 10), // "LeftLayout"
QT_MOC_LITERAL(1, 11, 14), // "lineNumChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 1), // "n"
QT_MOC_LITERAL(4, 29, 18), // "tiffMappingChanged"
QT_MOC_LITERAL(5, 48, 3), // "min"
QT_MOC_LITERAL(6, 52, 3), // "max"
QT_MOC_LITERAL(7, 56, 18), // "progressBarChanged"
QT_MOC_LITERAL(8, 75, 5), // "value"
QT_MOC_LITERAL(9, 81, 18), // "slotLineNumChanged"
QT_MOC_LITERAL(10, 100, 21), // "minTiffMappingChanged"
QT_MOC_LITERAL(11, 122, 21), // "maxTiffMappingChanged"
QT_MOC_LITERAL(12, 144, 15), // "slotShowMiniMap"
QT_MOC_LITERAL(13, 160, 6) // "isShow"

    },
    "LeftLayout\0lineNumChanged\0\0n\0"
    "tiffMappingChanged\0min\0max\0"
    "progressBarChanged\0value\0slotLineNumChanged\0"
    "minTiffMappingChanged\0maxTiffMappingChanged\0"
    "slotShowMiniMap\0isShow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LeftLayout[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    2,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   57,    2, 0x0a /* Public */,
       9,    0,   60,    2, 0x0a /* Public */,
      10,    1,   61,    2, 0x0a /* Public */,
      11,    1,   64,    2, 0x0a /* Public */,
      12,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void LeftLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LeftLayout *_t = static_cast<LeftLayout *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lineNumChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->tiffMappingChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->progressBarChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotLineNumChanged(); break;
        case 4: _t->minTiffMappingChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->maxTiffMappingChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotShowMiniMap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LeftLayout::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LeftLayout::lineNumChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LeftLayout::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LeftLayout::tiffMappingChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject LeftLayout::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LeftLayout.data,
      qt_meta_data_LeftLayout,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LeftLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LeftLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LeftLayout.stringdata0))
        return static_cast<void*>(const_cast< LeftLayout*>(this));
    return QWidget::qt_metacast(_clname);
}

int LeftLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void LeftLayout::lineNumChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LeftLayout::tiffMappingChanged(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
