SIZE GetBorderSize(HWND hDlg)
{
	RECT rect = {0, 0, 0, 0};
	SIZE size = {0, 0};
	WINDOWINFO wi;
	wi.cbSize = sizeof(WINDOWINFO);

	GetWindowInfo(hDlg, &wi);

	AdjustWindowRectEx(&rect, wi.dwStyle, FALSE, wi.dwExStyle);
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	return size;
}
