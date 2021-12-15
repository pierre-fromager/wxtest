
#include "frame.h"
#include "app.h"

#define APP_NAME "WxTest"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    SetAppDisplayName(APP_NAME);
    AppFrame *appFrame = new AppFrame(this);
    SetTopWindow(appFrame);
    appFrame->Show(true);
    return true;
}