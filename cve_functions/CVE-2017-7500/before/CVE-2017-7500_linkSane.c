static int linkSane(FD_t wfd, const char *dest)
{
    struct stat sb, lsb;

    return (fstat(Fileno(wfd), &sb) == 0 && sb.st_size == 0 &&
	    (sb.st_mode & ~S_IFMT) == S_IWUSR &&
	    lstat(dest, &lsb) == 0 && S_ISREG(lsb.st_mode) &&
	    sb.st_dev == lsb.st_dev && sb.st_ino == lsb.st_ino);
}
