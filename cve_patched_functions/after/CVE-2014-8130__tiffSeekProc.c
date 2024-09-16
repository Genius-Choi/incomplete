_tiffSeekProc(thandle_t fd, uint64 off, int whence)
{
	LARGE_INTEGER offli;
	DWORD dwMoveMethod;
	offli.QuadPart = off;
	switch(whence)
	{
		case SEEK_SET:
			dwMoveMethod = FILE_BEGIN;
			break;
		case SEEK_CUR:
			dwMoveMethod = FILE_CURRENT;
			break;
		case SEEK_END:
			dwMoveMethod = FILE_END;
			break;
		default:
			dwMoveMethod = FILE_BEGIN;
			break;
	}
	offli.LowPart=SetFilePointer(fd,offli.LowPart,&offli.HighPart,dwMoveMethod);
	if ((offli.LowPart==INVALID_SET_FILE_POINTER)&&(GetLastError()!=NO_ERROR))
		offli.QuadPart=0;
	return(offli.QuadPart);
}
