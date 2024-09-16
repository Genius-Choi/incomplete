vlvIndex_new()
{
    struct vlvIndex* p = (struct vlvIndex*)slapi_ch_calloc(1,sizeof(struct vlvIndex));
    if(p!=NULL)
    {
        p->vlv_sortspec= NULL;
        p->vlv_attrinfo= attrinfo_new();
        p->vlv_sortkey= NULL;
        p->vlv_filename= NULL;
	    p->vlv_mrpb= NULL;
        p->vlv_indexlength_lock= PR_NewLock();
        p->vlv_indexlength_cached= 0;
        p->vlv_indexlength= 0;
        p->vlv_online = 1;
        p->vlv_enabled = 0;
        p->vlv_lastchecked= 0;
        p->vlv_uses= 0;
        p->vlv_search= NULL;
        p->vlv_next= NULL;
    }
    return p;
}
