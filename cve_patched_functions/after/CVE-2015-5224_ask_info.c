static void ask_info(struct chfn_control *ctl)
{
	if (ctl->allow_fullname)
		ctl->newf.full_name = ask_new_field(ctl, _("Name"), ctl->oldf.full_name);
	if (ctl->allow_room)
		ctl->newf.office = ask_new_field(ctl, _("Office"), ctl->oldf.office);
	if (ctl->allow_work)
		ctl->newf.office_phone = ask_new_field(ctl, _("Office Phone"), ctl->oldf.office_phone);
	if (ctl->allow_home)
		ctl->newf.home_phone = ask_new_field(ctl, _("Home Phone"), ctl->oldf.home_phone);
	putchar('\n');
}
