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

#include <ctime>
#include "Jupiter/INIFile.h"
#include "Jupiter/IRC_Client.h"
#include "RenX_Ladder_Daily.h"

using namespace Jupiter::literals;

bool RenX_Ladder_Daily_TimePlugin::initialize()
{
	// Load database
	this->database.process_file(this->config.get(Jupiter::ReferenceString::empty, "LadderDatabase"_jrs, "Ladder.Daily.db"_jrs));
	this->database.setName(this->config.get(Jupiter::ReferenceString::empty, "DatabaseName"_jrs, "Daily"_jrs));
	this->database.setOutputTimes(this->config.getBool(Jupiter::ReferenceString::empty, "OutputTimes"_jrs, false));

	this->last_sorted_day = gmtime(std::addressof<const time_t>(time(0)))->tm_wday;
	this->database.OnPreUpdateLadder = OnPreUpdateLadder;

	// Force database to default, if desired
	if (this->config.getBool(Jupiter::ReferenceString::empty, "ForceDefault"_jrs, false))
		RenX::default_ladder_database = &this->database;

	return true;
}

// Plugin instantiation and entry point.
RenX_Ladder_Daily_TimePlugin pluginInstance;

void OnPreUpdateLadder(RenX::LadderDatabase &database, RenX::Server *server, const RenX::TeamType &team)
{
	tm *tm_ptr = gmtime(std::addressof<const time_t>(time(0)));
	if (pluginInstance.last_sorted_day != tm_ptr->tm_wday)
		database.erase();
	pluginInstance.last_sorted_day = tm_ptr->tm_wday;
}

extern "C" __declspec(dllexport) Jupiter::Plugin *getPlugin()
{
	return &pluginInstance;
}
