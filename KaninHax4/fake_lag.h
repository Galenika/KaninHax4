#pragma once
#include "sdk.h"
#include "settings.h"

void fake_lag()
{
	if (!current_settings.misc_fake_lag_enabled)
	{
		send_packet(true);
		return;
	}

	static int choked_packets = 0;
	if (choked_packets < current_settings.misc_fake_lag_amount)
	{
		send_packet(false);
		choked_packets++;
	}
	else
	{
		send_packet(true);
		choked_packets = 0;
	}
}