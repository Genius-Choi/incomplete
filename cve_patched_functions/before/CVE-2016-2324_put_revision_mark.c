void put_revision_mark(const struct rev_info *revs, const struct commit *commit)
{
	char *mark = get_revision_mark(revs, commit);
	if (!strlen(mark))
		return;
	fputs(mark, stdout);
	putchar(' ');
}
