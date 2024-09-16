CSoundFile::ProbeResult CSoundFile::ProbeFileHeaderSTP(MemoryFileReader file, const uint64 *pfilesize)
{
	STPFileHeader fileHeader;
	if(!file.ReadStruct(fileHeader))
	{
		return ProbeWantMoreData;
	}
	if(!ValidateHeader(fileHeader))
	{
		return ProbeFailure;
	}
	MPT_UNREFERENCED_PARAMETER(pfilesize);
	return ProbeSuccess;
}
