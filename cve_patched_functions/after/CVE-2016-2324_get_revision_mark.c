char *get_revision_mark(const struct rev_info *revs, const struct commit *commit)
{
	if (commit->object.flags & BOUNDARY)
		return "-";
	else if (commit->object.flags & UNINTERESTING)
		return "^";
	else if (commit->object.flags & PATCHSAME)
		return "=";
	else if (!revs || revs->left_right) {
		if (commit->object.flags & SYMMETRIC_LEFT)
			return "<";
		else
			return ">";
	} else if (revs->graph)
		return "*";
	else if (revs->cherry_mark)
		return "+";
	return "";
}
