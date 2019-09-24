/****************************************************************************
** Meta object code from reading C++ file 'QImageLabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QImageLabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QImageLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QImageLabel_t {
    QByteArrayData data[18];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QImageLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QImageLabel_t qt_meta_stringdata_QImageLabel = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QImageLabel"
QT_MOC_LITERAL(1, 12, 12), // "MouseRelease"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 39, 3), // "evt"
QT_MOC_LITERAL(5, 43, 10), // "KeyPressed"
QT_MOC_LITERAL(6, 54, 10), // "QKeyEvent*"
QT_MOC_LITERAL(7, 65, 10), // "MouseMoved"
QT_MOC_LITERAL(8, 76, 12), // "MousePressed"
QT_MOC_LITERAL(9, 89, 16), // "MouseDoubliClick"
QT_MOC_LITERAL(10, 106, 10), // "WheelEvent"
QT_MOC_LITERAL(11, 117, 12), // "QWheelEvent*"
QT_MOC_LITERAL(12, 130, 13), // "mouseMoveInfo"
QT_MOC_LITERAL(13, 144, 1), // "x"
QT_MOC_LITERAL(14, 146, 1), // "y"
QT_MOC_LITERAL(15, 148, 10), // "setMapping"
QT_MOC_LITERAL(16, 159, 3), // "min"
QT_MOC_LITERAL(17, 163, 3) // "max"

    },
    "QImageLabel\0MouseRelease\0\0QMouseEvent*\0"
    "evt\0KeyPressed\0QKeyEvent*\0MouseMoved\0"
    "MousePressed\0MouseDoubliClick\0WheelEvent\0"
    "QWheelEvent*\0mouseMoveInfo\0x\0y\0"
    "setMapping\0min\0max"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QImageLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       7,    1,   60,    2, 0x06 /* Public */,
       8,    1,   63,    2, 0x06 /* Public */,
       9,    1,   66,    2, 0x06 /* Public */,
      10,    1,   69,    2, 0x06 /* Public */,
      12,    2,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    2,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 11,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   16,   17,

       0        // eod
};

void QImageLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QImageLabel *_t = static_cast<QImageLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->MouseRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->KeyPressed((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: _t->MouseMoved((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->MousePressed((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->MouseDoubliClick((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->WheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 6: _t->mouseMoveInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->setMapping((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QImageLabel::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QImageLabel::MouseRelease)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QImageLabel::*_t)(QKeyEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QImageLabel::KeyPressed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QImageLabel::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QImageLabel::MouseMoved)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QImageLabel::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QImageLabel::MousePressed)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QImageLabel::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QImageLabel::MouseDoubliClick)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QImageLabel::*_t)(QWheelEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QImageLabel::WheelEvent)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QImageLabel::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QImageLabel::mouseMoveInfo)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject QImageLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_QImageLabel.data,
      qt_meta_data_QImageLabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QImageLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QImageLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QImageLabel.stringdata0))
        return static_cast<void*>(const_cast< QImageLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int QImageLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QImageLabel::MouseRelease(QMouseEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QImageLabel::KeyPressed(QKeyEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QImageLabel::MouseMoved(QMouseEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QImageLabel::MousePressed(QMouseEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QImageLabel::MouseDoubliClick(QMouseEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QImageLabel::WheelEvent(QWheelEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QImageLabel::mouseMoveInfo(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
