checksignature(void)
{
    char buf[6];

    fread(buf,1,6,infile);
    if (strncmp(buf,"GIF",3)) {
        fprintf(stderr, "file is not a GIF file\n");
        return 0;
    }
    if (strncmp(&buf[3],"87a",3)) {
        fprintf(stderr, "unknown GIF version number\n");
        return 0;
    }
    return 1;
}
