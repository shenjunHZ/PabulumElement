#ifndef __DS_GUI_GLOBAL_H
#define __DS_GUI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef DS_GUI_LIB
# define DS_GUI_EXPORT Q_DECL_EXPORT
#else
# define DS_GUI_EXPORT Q_DECL_IMPORT
#endif

#endif // __DS_GUI_GLOBAL_H
