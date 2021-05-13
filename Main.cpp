#include <iostream>
#include "Tester.h"
#include "Tasks.h"


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path>\n";
        return 1;
    }
    std::string path(argv[1]);
    StringsTask strings;
    TicketsTask tickets;
    Tester::run_tests(strings, (path + "/0.String").c_str());
    Tester::run_tests(tickets, (path +"/1.Tickets").c_str());
    return 0;
}
