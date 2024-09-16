vlvSearch_addtolist(struct vlvSearch* p, struct vlvSearch** pplist)
{
    if(pplist!=NULL && p!=NULL)
    {
        p->vlv_next= NULL;
        if(*pplist==NULL)
        {
            *pplist= p;
        }
        else
        {
            struct vlvSearch* last= *pplist;
            for(;last->vlv_next!=NULL;last=last->vlv_next);
            last->vlv_next= p;
        }
    }
}
