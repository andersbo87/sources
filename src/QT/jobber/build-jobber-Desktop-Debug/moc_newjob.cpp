/****************************************************************************
** Meta object code from reading C++ file 'newjob.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../jobber/newjob.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newjob.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NewJob_t {
    QByteArrayData data[10];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NewJob_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NewJob_t qt_meta_stringdata_NewJob = {
    {
QT_MOC_LITERAL(0, 0, 6), // "NewJob"
QT_MOC_LITERAL(1, 7, 16), // "titleTextChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 18), // "companyTextChanged"
QT_MOC_LITERAL(4, 44, 13), // "cityIDchanged"
QT_MOC_LITERAL(5, 58, 15), // "statusIDchanged"
QT_MOC_LITERAL(6, 74, 11), // "dateChanged"
QT_MOC_LITERAL(7, 86, 21), // "motivationTextChanged"
QT_MOC_LITERAL(8, 108, 15), // "OKButtonClicked"
QT_MOC_LITERAL(9, 124, 19) // "CancelButtonClicked"

    },
    "NewJob\0titleTextChanged\0\0companyTextChanged\0"
    "cityIDchanged\0statusIDchanged\0dateChanged\0"
    "motivationTextChanged\0OKButtonClicked\0"
    "CancelButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewJob[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NewJob::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NewJob *_t = static_cast<NewJob *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->titleTextChanged(); break;
        case 1: _t->companyTextChanged(); break;
        case 2: _t->cityIDchanged(); break;
        case 3: _t->statusIDchanged(); break;
        case 4: _t->dateChanged(); break;
        case 5: _t->motivationTextChanged(); break;
        case 6: _t->OKButtonClicked(); break;
        case 7: _t->CancelButtonClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NewJob::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_NewJob.data,
      qt_meta_data_NewJob,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NewJob::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewJob::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NewJob.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int NewJob::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
