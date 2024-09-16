parse_cookie()
{
    if (non_null(cookie_reject_domains))
	Cookie_reject_domains = make_domain_list(cookie_reject_domains);
    if (non_null(cookie_accept_domains))
	Cookie_accept_domains = make_domain_list(cookie_accept_domains);
    if (non_null(cookie_avoid_wrong_number_of_dots))
	Cookie_avoid_wrong_number_of_dots_domains
	       	= make_domain_list(cookie_avoid_wrong_number_of_dots);
}
