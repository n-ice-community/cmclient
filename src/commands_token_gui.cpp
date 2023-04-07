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

using namespace std;
std::string _server_list_text_names1;

enum TokenLoginWidgets {
	CC_TOKEN_USER,
	CC_TOKEN_LOGIN,
	CC_TOKEN_COMMUNITY,
	CC_TOKEN_WEBSITE,
	CC_TOKEN_WIKI,
	CC_OTHER_WIKI_RULES,
	CC_OTHER_IRC_CHAT,
	CC_OTHER_IRC_SERVERS,
	CC_SERVERS,
	CC_SERVERS1,
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

	virtual void DrawWidget(const Rect &r, int widget) const
	{
		char* _cc_name; //server name - for the button
		char name[16];
		char sn[64];
		switch (widget) {
			case CC_SERVERS:
				// do nothing
				break;
			default:
				if(widget >= CC_SERVERS1){
					if(widget - CC_SERVERS1 + 1 < 10){
						seprintf(name, lastof(name), "NAME0%i", widget - CC_SERVERS1 + 1);
					}
					else {
						seprintf(name, lastof(name), "NAME%i", widget - CC_SERVERS1 + 1);
					}
					size_t posname = _server_list_text_names1.find(name);
					std::string sname = _server_list_text_names1.substr(posname + 8, _server_list_text_names1.find(";", posname + 8) - posname - 8);
					strecpy(sn, sname.c_str(), lastof(sn));
					_cc_name = sn;

					SetDParamStr(0, _cc_name);
					DrawString(r.left, r.right, r.top + 3, STR_NETWORK_DIRECT_JOIN_GAME, TC_FROMSTRING, SA_CENTER);
				}
				break;
		}
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
				} else { // do nothing
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
			default:
				if(widget >= CC_SERVERS1){
					/*get info of server from network.cpp and join*/
					if (GetCommunityServer(widget - CC_SERVERS1 + 1)) {
						if (_ctrl_pressed) {
							NetworkClientConnectGame(fmt::format("{}:{}", _cc_address, _cc_porti), COMPANY_NEW_COMPANY);
						} else {
							NetworkClientConnectGame(fmt::format("{}:{}", _cc_address, _cc_porti), COMPANY_SPECTATOR);
						}
					}
				} else { ShowErrorMessage(STR_CC_SERVER_DISABLED, INVALID_STRING_ID, WL_ERROR); }
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
			/* Welcome user */
			NWidget(NWID_HORIZONTAL),
				NWidget(NWID_SPACER), SetMinimalSize(3,0), SetFill(0, 1),
				NWidget(WWT_TEXT, COLOUR_BROWN, CC_TOKEN_USER), SetDataTip(STR_CC_TOKEN_WELCOME, STR_NULL), SetMinimalSize(200, 20),
			EndContainer(),
			/* Login button */
			NWidget(NWID_HORIZONTAL), SetPIP(2, 2, 2), SetPadding(10, 100, 10, 100),
				NWidget(WWT_PUSHTXTBTN, COLOUR_GREY, CC_TOKEN_LOGIN), SetMinimalSize(60, 40),SetFill(1, 0), SetDataTip(STR_CC_TOKEN_LOGIN, STR_CC_TOKEN_LOGIN_TOOLTIP),
			EndContainer(),
			NWidget(NWID_SPACER), SetMinimalSize(0, 5), SetFill(1, 1),
			/* several buttons */
			NWidget(NWID_HORIZONTAL ), SetPadding(0, 15, 0, 15),
				NWidget(WWT_PUSHTXTBTN, COLOUR_GREY, CC_TOKEN_WEBSITE), SetMinimalSize(55, 30),SetFill(1, 0), SetDataTip(STR_NETWORK_SERVER_LIST_JOIN_GAME_CC_WEBSITE, STR_NETWORK_SERVER_LIST_JOIN_GAME_CC_WEBSITE_TOOLTIP),
				NWidget(NWID_SPACER), SetMinimalSize(5,0), SetFill(0, 1),
				NWidget( WWT_PUSHTXTBTN, COLOUR_GREY, CC_OTHER_IRC_CHAT ), SetMinimalSize(55, 30),SetFill(1, 0), SetDataTip( STR_CC_IRC_LINK_CHAT, STR_CC_IRC_LINK_CHAT_TOOLTIP ),
				NWidget(NWID_SPACER), SetMinimalSize(5,0), SetFill(0, 1),
				NWidget(WWT_PUSHTXTBTN, COLOUR_GREY, CC_OTHER_IRC_SERVERS ), SetMinimalSize(50, 30),SetFill(1, 0), SetDataTip( STR_CC_IRC_LINK_SERVERS, STR_CC_IRC_LINK_SERVERS_TOOLTIP ),
				NWidget(NWID_SPACER), SetMinimalSize(5,0), SetFill(0, 1),
				NWidget(WWT_PUSHTXTBTN, COLOUR_GREY, CC_OTHER_WIKI_RULES ), SetMinimalSize(50, 30),SetFill(1, 0), SetDataTip( STR_CC_WIKI_RULES_PAGE, STR_CC_WIKI_RULES_PAGE_TOOLTIP ),
			EndContainer(),
			/* Visit community text */
			NWidget(NWID_HORIZONTAL ), SetPadding(10, 2, 3, 2),
				NWidget(WWT_CAPTION, COLOUR_BROWN, CC_TOKEN_COMMUNITY), SetDataTip(STR_NETWORK_SERVER_LIST_CC_HEADER, STR_CC_SERVERS_TOOLTIP),
			EndContainer(),
		EndContainer(),
		/* Server buttons */
        NWidget( NWID_HORIZONTAL, NC_EQUALSIZE ), SetFill(1, 0), SetPIP(4, 1, 4),
           NWidgetFunction(MakeServerButtons_User),
        EndContainer( ),
		NWidget(NWID_SPACER), SetMinimalSize(2, 2), SetFill(0, 1),
	EndContainer(),
};

NWidgetBase *MakeServerButtons_User(int *biggest_index)
{
	NWidgetVertical *ver = new NWidgetVertical;
	_server_list_text_names1 = _server_list_text;

	if(_settings_client.gui.community == 0 || _server_list_text_names1.empty()){
		NWidgetBackground *leaf = new NWidgetBackground(WWT_PANEL, COLOUR_GREY, CC_SERVERS, NULL);
		ver->Add(leaf);
		return ver;
	}

    /* check for disabled server from serverlist file */
	int active = 0, aactive[50], s_max = 0;
	if (_settings_client.gui.community == 1) s_max = 50; //for n-ice
	if (_settings_client.gui.community == 2) s_max = 30; //for btpro
	for (int i = 0; i < s_max; i++) {
        aactive[i] = GetCommunityServer(i + 1, true) ? (i + 1) : 0; //server disabled?
        active++;
    }

	NWidgetHorizontal *hor = new NWidgetHorizontal;
	int i1 = 0, i2 = 0;
	for (int i = 0; i < s_max; i++) {
		if ((aactive[i] == 0) && (_settings_client.gui.community == 1)) continue; //hide button if disabled - for n-ice only
		i2++;
		if ((i1 == 5) || (i1 == 10) || (i1 == 15) || (i1 == 20) || (i1 == 25) || (i1 == 30) || (i1 == 35) || (i1 == 40) || (i1 == 45) || (i1 == 50)) {
			i2=0;
			NWidgetSpacer *spce = new NWidgetSpacer(3, 0);
			spce->SetFill(1, 0);
			hor->Add(spce);
			ver->Add(hor);
			NWidgetSpacer *spc = new NWidgetSpacer(0, 4);
			spc->SetFill(1, 0);
			ver->Add(spc);
			hor = new NWidgetHorizontal();
		}
		NWidgetSpacer *spce = new NWidgetSpacer(3, 0);
		spce->SetFill(1, 0);
		hor->Add(spce);
		NWidgetBackground *leaf = new NWidgetBackground(WWT_PANEL, COLOUR_ORANGE, CC_SERVERS1 + i, NULL);
		if(aactive[i] == 0) leaf->SetDisabled(true);
		leaf->SetDataTip(0, STR_NETWORK_DIRECT_JOIN_GAME_TOOLTIP);
		leaf->SetMinimalSize(90, 15);
		hor->Add(leaf);
		i1++;
	}

	/* arrange buttons @ last line */
	if (i2==0) i2=375;
	if (i2==1) i2=282;
	if (i2==2) i2=189;
	if (i2==3) i2=96;
	if (i2==4) i2=3;
	NWidgetSpacer *spce = new NWidgetSpacer(i2, 0);
	spce->SetFill(1, 0);
	hor->Add(spce);
	ver->Add(hor);
	*biggest_index = CC_SERVERS1 - 1 + active;
	return ver;
}



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
