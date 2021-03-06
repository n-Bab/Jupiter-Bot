/**
 * Copyright (C) 2016 Jessica James.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Written by Jessica James <jessica.aj@outlook.com>
 */

#if !defined _RENX_SERVERLIST_H_HEADER
#define _RENX_SERVERLIST_H_HEADER

#include "Jupiter/Plugin.h"
#include "Jupiter/Reference_String.h"
#include "RenX_Plugin.h"

class RenX_ServerListPlugin : public RenX::Plugin
{
public: // RenX_ServerListPlugin
	Jupiter::ReadableString *getServerListJSON();
	Jupiter::ReadableString *getServerListGame();

	void addServerToServerList(RenX::Server *server);
	void updateServerList();

	virtual bool initialize() override;
	~RenX_ServerListPlugin();

public: // RenX::Plugin
	void RenX_OnServerFullyConnected(RenX::Server *server) override;
	void RenX_OnServerDisconnect(RenX::Server *server, RenX::DisconnectReason reason) override;
	void RenX_OnJoin(RenX::Server *server, const RenX::PlayerInfo *player) override;
	void RenX_OnPart(RenX::Server *server, const RenX::PlayerInfo *player) override;
	void RenX_OnMapLoad(RenX::Server *server, const Jupiter::ReadableString &map) override;

private:
	Jupiter::StringS server_list_json, server_list_game;
	Jupiter::StringS web_hostname, web_path, server_list_page_name, server_list_long_page_name, server_page_name, game_server_list_page_name;
};

Jupiter::ReadableString *handle_server_list_page(const Jupiter::ReadableString &);
Jupiter::ReadableString *handle_server_list_long_page(const Jupiter::ReadableString &);
Jupiter::ReadableString *handle_server_page(const Jupiter::ReadableString &query_string);
Jupiter::ReadableString *handle_game_server_list_page(const Jupiter::ReadableString &);

#endif // _RENX_SERVERLIST_H_HEADER
