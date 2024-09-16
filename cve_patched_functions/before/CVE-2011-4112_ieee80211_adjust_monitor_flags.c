void ieee80211_adjust_monitor_flags(struct ieee80211_sub_if_data *sdata,
				    const int offset)
{
	struct ieee80211_local *local = sdata->local;
	u32 flags = sdata->u.mntr_flags;

#define ADJUST(_f, _s)	do {					\
	if (flags & MONITOR_FLAG_##_f)				\
		local->fif_##_s += offset;			\
	} while (0)

	ADJUST(FCSFAIL, fcsfail);
	ADJUST(PLCPFAIL, plcpfail);
	ADJUST(CONTROL, control);
	ADJUST(CONTROL, pspoll);
	ADJUST(OTHER_BSS, other_bss);

#undef ADJUST
}
