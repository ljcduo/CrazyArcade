#pragma once

#include "Util.h"
#include "LGCenter.h"

#define SetCurrentScene(SceneName) g_pLGCenter->SetCurrentScene(SceneName::Instance());
#define SetWindowsTitle(TitleName) g_pLGCenter->WindowsTitle(TitleName);