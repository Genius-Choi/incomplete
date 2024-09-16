static char *format_duration(u64 dur, u32 timescale, char *szDur)
{
	u32 h, m, s, ms;
	dur = (u32) (( ((Double) (s64) dur)/timescale)*1000);
	h = (u32) (dur / 3600000);
	dur -= h*3600000;
	m = (u32) (dur / 60000);
	dur -= m*60000;
	s = (u32) (dur/1000);
	dur -= s*1000;
	ms = (u32) (dur);
	sprintf(szDur, "%02d:%02d:%02d.%03d", h, m, s, ms);
	return szDur;
}
