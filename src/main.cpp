#include "Application.h"

int main(void) {
    Application application;
    application.Initialize();
    application.Run();
    application.Destroy();
}