iterate_md5_digest(MD5& md5, MD5::Digest& digest, int iterations)
{
    md5.digest(digest);

    for (int i = 0; i < iterations; ++i)
    {
	MD5 m;
	m.encodeDataIncrementally(reinterpret_cast<char*>(digest),
                                  sizeof(digest));
	m.digest(digest);
    }
}
