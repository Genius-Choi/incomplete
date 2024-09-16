void FreeContextBuffer_EnumerateSecurityPackages(void* contextBuffer)
{
	int index;
	UINT32 cPackages;
	SecPkgInfoA* pPackageInfo = (SecPkgInfoA*) contextBuffer;

	cPackages = sizeof(SecPkgInfoA_LIST) / sizeof(*(SecPkgInfoA_LIST));

	for (index = 0; index < (int) cPackages; index++)
	{
		if (pPackageInfo[index].Name)
			free(pPackageInfo[index].Name);

		if (pPackageInfo[index].Comment)
			free(pPackageInfo[index].Comment);
	}

	free(pPackageInfo);
}
