#include <qapplication.h>
#include "editpreference.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    EditPreference w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
