static void add_missing(struct chfn_control *ctl)
{
	ctl->newf.full_name = find_field(ctl->newf.full_name, ctl->oldf.full_name);
	ctl->newf.office = find_field(ctl->newf.office, ctl->oldf.office);
	ctl->newf.office_phone = find_field(ctl->newf.office_phone, ctl->oldf.office_phone);
	ctl->newf.home_phone = find_field(ctl->newf.home_phone, ctl->oldf.home_phone);
	ctl->newf.other = find_field(ctl->newf.other, ctl->oldf.other);
	printf("\n");
}
