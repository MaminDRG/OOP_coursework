#include "application.h"
int main(int argc, char *argv[])

{
        void printInfoTerm();
        printInfoTerm();

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

void printInfoTerm()
{

    std::cout << "\033[31;1m###############################################################################\033[0m" << std::endl;
    std::cout << "\033[31;1m########################\033[0m  <>  \033[34mServer\033[0m              <>    \033[31;1m#######################\033[0m" << std::endl;
    std::cout << "\033[31;1m########################\033[0m   <>       \033[34mstarted\033[0m        <>   \033[31;1m#######################\033[0m" << std::endl;
    std::cout << "\033[31;1m########################\033[0m    <>           \033[34mworking\033[0m    <>  \033[31;1m#######################\033[0m" << std::endl;
    std::cout << "\033[31;1m###############################################################################\033[0m" << std::endl << std::endl;

}
