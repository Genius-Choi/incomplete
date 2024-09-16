void TCGetDosNameFromNumber (LPWSTR dosname,int cbDosName, int nDriveNo, DeviceNamespaceType namespaceType)
{
	WCHAR tmp[3] =
	{0, ':', 0};
	int j = nDriveNo + (WCHAR) 'A';

	tmp[0] = (short) j;

	if (DeviceNamespaceGlobal == namespaceType)
	{
		RtlStringCbCopyW (dosname, cbDosName, (LPWSTR) DOS_MOUNT_PREFIX_GLOBAL);
	}
	else
	{
		RtlStringCbCopyW (dosname, cbDosName, (LPWSTR) DOS_MOUNT_PREFIX_DEFAULT);
	}

	RtlStringCbCatW (dosname, cbDosName, tmp);
}
