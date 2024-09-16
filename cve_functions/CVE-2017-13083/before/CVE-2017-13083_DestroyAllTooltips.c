void DestroyAllTooltips(void)
{
	int i, j;

	for (i=0, j=0; i<MAX_TOOLTIPS; i++) {
		if (ttlist[i].hTip == NULL) continue;
		j++;
		DestroyWindow(ttlist[i].hTip);
		safe_free(ttlist[i].wstring);
		ttlist[i].original_proc = NULL;
		ttlist[i].hTip = NULL;
		ttlist[i].hCtrl = NULL;
	}
}
