/* $Id: commands_token_gui.h $ */

#ifndef COMMANDS_TOKEN_GUI_H
#define COMMANDS_TOKEN_GUI_H

#include "window_gui.h"
#include "company_base.h"

void ShowTokenLogin();
NWidgetBase *MakeServerButtons_User(int *biggest_index);
bool GetServerInfo(int number, bool findonly);

#endif
