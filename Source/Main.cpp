#include <iostream>

#include <Application.hpp>

int main()
{
    try
    {
        Editor::Application app;
        app.run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

