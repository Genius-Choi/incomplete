void DestroyTooltip(HWND hControl)
{
	int i;

	if (hControl == NULL) return;
	for (i=0; i<MAX_TOOLTIPS; i++) {
		if (ttlist[i].hCtrl == hControl) break;
	}
	if (i >= MAX_TOOLTIPS) return;
	DestroyWindow(ttlist[i].hTip);
	safe_free(ttlist[i].wstring);
	ttlist[i].original_proc = NULL;
	ttlist[i].hTip = NULL;
	ttlist[i].hCtrl = NULL;
}
