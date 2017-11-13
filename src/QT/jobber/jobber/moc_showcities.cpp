/****************************************************************************
** Meta object code from reading C++ file 'showcities.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "showcities.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showcities.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShowCities_t {
    QByteArrayData data[11];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShowCities_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShowCities_t qt_meta_stringdata_ShowCities = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ShowCities"
QT_MOC_LITERAL(1, 11, 21), // "comboboxCityIDChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 24), // "comboboxCountryIDChanged"
QT_MOC_LITERAL(4, 59, 23), // "lineEditCityNameChanged"
QT_MOC_LITERAL(5, 83, 18), // "buttonFirstClicked"
QT_MOC_LITERAL(6, 102, 21), // "buttonPreviousClicked"
QT_MOC_LITERAL(7, 124, 17), // "buttonNextClicked"
QT_MOC_LITERAL(8, 142, 17), // "buttonLastClicked"
QT_MOC_LITERAL(9, 160, 17), // "buttonSaveClicked"
QT_MOC_LITERAL(10, 178, 19) // "buttonDeleteClicked"

    },
    "ShowCities\0comboboxCityIDChanged\0\0"
    "comboboxCountryIDChanged\0"
    "lineEditCityNameChanged\0buttonFirstClicked\0"
    "buttonPreviousClicked\0buttonNextClicked\0"
    "buttonLastClicked\0buttonSaveClicked\0"
    "buttonDeleteClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShowCities[] = {

 // content:
       7,       // revision
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
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
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

void ShowCities::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShowCities *_t = static_cast<ShowCities *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->comboboxCityIDChanged(); break;
        case 1: _t->comboboxCountryIDChanged(); break;
        case 2: _t->lineEditCityNameChanged(); break;
        case 3: _t->buttonFirstClicked(); break;
        case 4: _t->buttonPreviousClicked(); break;
        case 5: _t->buttonNextClicked(); break;
        case 6: _t->buttonLastClicked(); break;
        case 7: _t->buttonSaveClicked(); break;
        case 8: _t->buttonDeleteClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ShowCities::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ShowCities.data,
      qt_meta_data_ShowCities,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ShowCities::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShowCities::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ShowCities.stringdata0))
        return static_cast<void*>(const_cast< ShowCities*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ShowCities::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
