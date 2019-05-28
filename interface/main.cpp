#include <application.h>

int main(int argc, char *argv[])
{

    try
    {
        TApplication a(argc, argv);
        return a.exec();
    }
    catch(int)
    {
        getchar();
        return EXIT_FAILURE;
    }


}
