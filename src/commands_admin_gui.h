/* $Id: commands_admin_gui.h $ */

/** @file commands_admin_gui.h GUI related to community server commands. */

#ifndef COMMANDS_ADMIN_GUI_H
#define COMMANDS_ADMIN_GUI_H

#include "window_gui.h"
#include "company_base.h"

void ShowAdminCommands();
NWidgetBase *MakeServerButtons_admin(int *biggest_index);
bool GetServerInfo(int number, bool findonly);

#endif // commands_admin_gui_h
