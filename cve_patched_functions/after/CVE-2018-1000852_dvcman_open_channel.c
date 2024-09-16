static UINT dvcman_open_channel(drdynvcPlugin* drdynvc,
                                IWTSVirtualChannelManager* pChannelMgr,
                                UINT32 ChannelId)
{
	DVCMAN_CHANNEL* channel;
	IWTSVirtualChannelCallback* pCallback;
	UINT error;
	channel = (DVCMAN_CHANNEL*) dvcman_find_channel_by_id(pChannelMgr, ChannelId);

	if (!channel)
	{
		WLog_Print(drdynvc->log, WLOG_ERROR, "ChannelId %"PRIu32" not found!", ChannelId);
		return ERROR_INTERNAL_ERROR;
	}

	if (channel->status == CHANNEL_RC_OK)
	{
		pCallback = channel->channel_callback;

		if ((pCallback->OnOpen) && (error = pCallback->OnOpen(pCallback)))
		{
			WLog_Print(drdynvc->log, WLOG_ERROR, "OnOpen failed with error %"PRIu32"!", error);
			return error;
		}

		WLog_Print(drdynvc->log, WLOG_DEBUG, "open_channel: ChannelId %"PRIu32"", ChannelId);
	}

	return CHANNEL_RC_OK;
}
