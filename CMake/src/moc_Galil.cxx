/****************************************************************************
** Meta object code from reading C++ file 'Galil.h'
**
** Created: Fri Aug 3 14:57:09 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Galil.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Galil.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Galil[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      23,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Galil[] = {
    "Galil\0\0ReceivingData()\0ReadReply()\0"
};

const QMetaObject Galil::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Galil,
      qt_meta_data_Galil, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Galil::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Galil::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Galil::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Galil))
        return static_cast<void*>(const_cast< Galil*>(this));
    return QDialog::qt_metacast(_clname);
}

int Galil::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ReceivingData(); break;
        case 1: ReadReply(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
