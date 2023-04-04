/* $Id: commands_token_gui.cpp	23663 2011-12-23 18:01:50	me $ */

#include "stdafx.h"
#include "widget_type.h"
#include "window_func.h"
#include "strings_func.h"
#include "commands_token_gui.h"
#include "network/network.h"
#include "network/network_func.h"
#include "network/network_base.h"
#include "network/network_type.h"
#include "table/strings.h"
#include "console_func.h"
#include "error.h"
#include "citymania/cm_base64.hpp"
#include <iostream>

#include "safeguards.h"

enum TokenLoginWidgets {
	CC_TOKEN_USER,
	CC_TOKEN_LOGIN,
	CC_TOKEN_COMMUNITY,
	CC_TOKEN_WEBSITE,
	CC_TOKEN_WIKI,
	CC_OTHER_WIKI_RULES,
	CC_OTHER_IRC_CHAT,
	CC_OTHER_IRC_SERVERS,
};

class TokenLoginGui : public Window
{
	public:
		TokenLoginGui(WindowDesc *desc, int window_number) : Window(desc)
		{
			this->InitNested(window_number);
		}

	virtual void OnPaint()
	{
		this->DrawWidgets();
	}

	virtual void SetStringParameters(int widget) const
	{
		if(widget == CC_TOKEN_USER) SetDParamStr(0, _settings_client.network.community_user[_settings_client.gui.community-1]);
		else if(widget == CC_TOKEN_COMMUNITY) SetDParam(0, (STR_CC_SEPARATOR_DEFAULT + (uint16)_settings_client.gui.community));
	}

	virtual void OnClick(Point pt, int widget, int click_count)
	{
		extern void OpenBrowser(const char *url);
		switch (widget) {
			case CC_TOKEN_LOGIN:
        if ((_networking) && (_settings_client.gui.community != 0)) {
          //LoginToken();
          //loginmgr.initiateLoginSequence();
          CommunityLoginManagerSend();
        } else {
          // do nothing
        }
				break;
			case CC_TOKEN_WEBSITE:
          if(_settings_client.gui.community == 1) OpenBrowser("http://www.n-ice.org/openttd");
          else if(_settings_client.gui.community == 2) OpenBrowser("https://openttd.btpro.nl");
				break;
			case CC_TOKEN_WIKI:
          if(_settings_client.gui.community == 1) OpenBrowser("http://www.n-ice.org/openttd");
          else if(_settings_client.gui.community == 2) OpenBrowser("https://openttd.btpro.nl/contact-us/vip-membership");
				break;
			case CC_OTHER_WIKI_RULES:
				if(_settings_client.gui.community == 1) OpenBrowser("https://wiki.x-base.info/OpenTTD/Rules");
				else if(_settings_client.gui.community == 2) OpenBrowser("https://openttd.btpro.nl/wiki/index.php/Server_Rules");
				break;
			case CC_OTHER_IRC_CHAT:
				if(_settings_client.gui.community == 1) OpenBrowser("https://chat.mibbit.com/?url=irc%3A%2F%2Firc.boxor.net:6668%2FOpenTTD.Chat");
				else if(_settings_client.gui.community == 2) OpenBrowser("https://chat.mibbit.com/?url=irc%3A%2F%2Firc.boxor.net:6668%2Fbtpro-chat");
				break;
			case CC_OTHER_IRC_SERVERS:
				if(_settings_client.gui.community == 1) OpenBrowser("https://chat.mibbit.com/?url=irc%3A%2F%2Firc.boxor.net:6668%2FOpenTTD");
				else if(_settings_client.gui.community == 2) OpenBrowser("https://chat.mibbit.com/?url=irc%3A%2F%2Firc.boxor.net:6668%2Fbtpro-openttd");
				break;
		}
	}
};

static const NWidgetPart _nested_token_login_widgets[] = {
	/* Title Bar with close box, title, shade and stick boxes */
	NWidget(NWID_HORIZONTAL),
		NWidget(WWT_CLOSEBOX, COLOUR_GREY),
		NWidget(WWT_CAPTION, COLOUR_GREY), SetDataTip(STR_CC_GLOBAL_COMMANDS_TITLE, STR_TOOLTIP_WINDOW_TITLE_DRAG_THIS),
		NWidget(WWT_SHADEBOX, COLOUR_GREY),
		NWidget(WWT_STICKYBOX, COLOUR_GREY),
	EndContainer(),
	NWidget(WWT_PANEL, COLOUR_GREY), SetFill(0, 1), SetPIP(2, 2, 2),
		NWidget(NWID_VERTICAL), SetPadding(0, 5, 0, 5),
			NWidget(WWT_TEXT, COLOUR_BROWN, CC_TOKEN_USER), SetDataTip(STR_CC_TOKEN_WELCOME, STR_NULL), SetMinimalSize(110, 16),
			NWidget(WWT_TEXT, COLOUR_BROWN), SetDataTip(STR_CC_TOKEN_CLICKME, STR_NULL), SetMinimalSize(110, 16),
			NWidget(NWID_HORIZONTAL), SetPIP(2, 2, 2),
				NWidget(WWT_PUSHTXTBTN, COLOUR_GREY, CC_TOKEN_LOGIN), SetMinimalSize(105, 40),SetFill(1, 0), SetDataTip(STR_CC_TOKEN_LOGIN, STR_CC_TOKEN_LOGIN_TOOLTIP),
			EndContainer(),
			NWidget(WWT_TEXT, COLOUR_BROWN), SetDataTip(STR_CC_TOKEN_ENJOY, STR_NULL), SetMinimalSize(110, 16),
			NWidget(WWT_TEXT, COLOUR_BROWN, CC_TOKEN_COMMUNITY), SetDataTip(STR_CC_SEPARATOR, STR_NULL), SetMinimalSize(110, 16),
			NWidget(WWT_PUSHTXTBTN, COLOUR_GREY, CC_TOKEN_WEBSITE), SetMinimalSize(120, 14),SetFill(1, 0), SetDataTip(STR_NETWORK_SERVER_LIST_JOIN_GAME_CC_WEBSITE, STR_NETWORK_SERVER_LIST_JOIN_GAME_CC_WEBSITE_TOOLTIP),
			NWidget(NWID_HORIZONTAL ), SetPadding(5, 0, 5, 0),
				NWidget( WWT_PUSHTXTBTN, COLOUR_GREY, CC_OTHER_IRC_CHAT ), SetMinimalSize(57, 14),SetFill(1, 0), SetDataTip( STR_CC_IRC_LINK_CHAT, STR_CC_IRC_LINK_CHAT_TOOLTIP ),
				NWidget(WWT_TEXT, COLOUR_BROWN), SetDataTip(STR_CC_IRC_LINK_SERVERS_SPACER, STR_NULL), SetMinimalSize(6, 14),
				NWidget(WWT_PUSHTXTBTN, COLOUR_GREY, CC_OTHER_IRC_SERVERS ), SetMinimalSize(57, 14),SetFill(1, 0), SetDataTip( STR_CC_IRC_LINK_SERVERS, STR_CC_IRC_LINK_SERVERS_TOOLTIP ),
			EndContainer(),
			NWidget(WWT_PUSHTXTBTN, COLOUR_GREY, CC_OTHER_WIKI_RULES ), SetMinimalSize(120, 14),SetFill(1, 0), SetDataTip( STR_CC_WIKI_RULES_PAGE, STR_CC_WIKI_RULES_PAGE_TOOLTIP ),
		EndContainer(),
		NWidget(NWID_SPACER), SetMinimalSize(2, 2), SetFill(0, 1),
	EndContainer(),
};

static WindowDesc _token_login_desc(
	WDP_CENTER, "commands_token_gui", 0, 0,
	WC_CC_TOKENLOGIN, WC_NONE,
	0,
	_nested_token_login_widgets, lengthof(_nested_token_login_widgets)
);

void ShowTokenLogin()
{
	AllocateWindowDescFront<TokenLoginGui>(&_token_login_desc, 0);
}
