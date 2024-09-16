void FreeContextBuffer_QuerySecurityPackageInfo(void* contextBuffer)
{
	SecPkgInfo* pPackageInfo = (SecPkgInfo*) contextBuffer;

	if (pPackageInfo->Name)
		free(pPackageInfo->Name);

	if (pPackageInfo->Comment)
		free(pPackageInfo->Comment);

	free(pPackageInfo);
}
