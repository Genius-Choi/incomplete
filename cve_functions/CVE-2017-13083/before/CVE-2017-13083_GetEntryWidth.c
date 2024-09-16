LONG GetEntryWidth(HWND hDropDown, const char *entry)
{
	HDC hDC;
	HFONT hFont, hDefFont = NULL;
	SIZE size;

	hDC = GetDC(hDropDown);
	hFont = (HFONT)SendMessage(hDropDown, WM_GETFONT, 0, 0);
	if (hFont != NULL)
		hDefFont = (HFONT)SelectObject(hDC, hFont);

	if (!GetTextExtentPointU(hDC, entry, &size))
		size.cx = 0;

	if (hFont != NULL)
		SelectObject(hDC, hDefFont);

	if (hDC != NULL)
		ReleaseDC(hDropDown, hDC);
	return size.cx;
}
