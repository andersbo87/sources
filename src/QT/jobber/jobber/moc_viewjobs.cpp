/****************************************************************************
** Meta object code from reading C++ file 'viewjobs.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "viewjobs.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewjobs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ViewJobs_t {
    QByteArrayData data[14];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewJobs_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewJobs_t qt_meta_stringdata_ViewJobs = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ViewJobs"
QT_MOC_LITERAL(1, 9, 28), // "comboboxApplicationIDChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 20), // "lineEditTitleChanged"
QT_MOC_LITERAL(4, 60, 22), // "lineEditCompanyChanged"
QT_MOC_LITERAL(5, 83, 22), // "lineEditDealineChanged"
QT_MOC_LITERAL(6, 106, 21), // "comboBoxCityIDChanged"
QT_MOC_LITERAL(7, 128, 23), // "comboBoxStatusIDChanged"
QT_MOC_LITERAL(8, 152, 18), // "buttonFirstClicked"
QT_MOC_LITERAL(9, 171, 21), // "buttonPreviousClicked"
QT_MOC_LITERAL(10, 193, 17), // "buttonNextClicked"
QT_MOC_LITERAL(11, 211, 17), // "buttonLastClicked"
QT_MOC_LITERAL(12, 229, 17), // "buttonSaveClicked"
QT_MOC_LITERAL(13, 247, 19) // "buttonDeleteClicked"

    },
    "ViewJobs\0comboboxApplicationIDChanged\0"
    "\0lineEditTitleChanged\0lineEditCompanyChanged\0"
    "lineEditDealineChanged\0comboBoxCityIDChanged\0"
    "comboBoxStatusIDChanged\0buttonFirstClicked\0"
    "buttonPreviousClicked\0buttonNextClicked\0"
    "buttonLastClicked\0buttonSaveClicked\0"
    "buttonDeleteClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewJobs[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ViewJobs::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ViewJobs *_t = static_cast<ViewJobs *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->comboboxApplicationIDChanged(); break;
        case 1: _t->lineEditTitleChanged(); break;
        case 2: _t->lineEditCompanyChanged(); break;
        case 3: _t->lineEditDealineChanged(); break;
        case 4: _t->comboBoxCityIDChanged(); break;
        case 5: _t->comboBoxStatusIDChanged(); break;
        case 6: _t->buttonFirstClicked(); break;
        case 7: _t->buttonPreviousClicked(); break;
        case 8: _t->buttonNextClicked(); break;
        case 9: _t->buttonLastClicked(); break;
        case 10: _t->buttonSaveClicked(); break;
        case 11: _t->buttonDeleteClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ViewJobs::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ViewJobs.data,
      qt_meta_data_ViewJobs,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ViewJobs::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewJobs::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ViewJobs.stringdata0))
        return static_cast<void*>(const_cast< ViewJobs*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ViewJobs::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
