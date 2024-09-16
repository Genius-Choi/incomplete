HWND MyCreateDialog(HINSTANCE hInstance, int Dialog_ID, HWND hWndParent, DLGPROC lpDialogFunc)
{
	LPCDLGTEMPLATE rcTemplate = GetDialogTemplate(Dialog_ID);
	HWND hDlg = CreateDialogIndirect(hInstance, rcTemplate, hWndParent, lpDialogFunc);
	safe_free(rcTemplate);
	return hDlg;
}
