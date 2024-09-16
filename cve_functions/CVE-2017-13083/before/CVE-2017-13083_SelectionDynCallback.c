INT_PTR CALLBACK SelectionDynCallback(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int r = -1;
	switch (message) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			r = 0;
		case IDCANCEL:
			EndDialog(hwndDlg, r);
			return (INT_PTR)TRUE;
		}
	}
	return FALSE;
}
