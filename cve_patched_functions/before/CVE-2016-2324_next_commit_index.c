static inline unsigned int next_commit_index(unsigned int idx)
{
	static const unsigned int MIN_COMMITS = 100;
	static const unsigned int MAX_COMMITS = 5000;

	static const unsigned int MUST_REGION = 100;
	static const unsigned int MIN_REGION = 20000;

	unsigned int offset, next;

	if (idx <= MUST_REGION)
		return 0;

	if (idx <= MIN_REGION) {
		offset = idx - MUST_REGION;
		return (offset < MIN_COMMITS) ? offset : MIN_COMMITS;
	}

	offset = idx - MIN_REGION;
	next = (offset < MAX_COMMITS) ? offset : MAX_COMMITS;

	return (next > MIN_COMMITS) ? next : MIN_COMMITS;
}
