repBuffer(Buffer *oldbuf, Buffer *buf)
{
    Firstbuf = replaceBuffer(Firstbuf, oldbuf, buf);
    Currentbuf = buf;
}
