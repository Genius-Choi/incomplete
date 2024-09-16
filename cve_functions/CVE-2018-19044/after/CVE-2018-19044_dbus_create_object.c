dbus_create_object(vrrp_t *vrrp)
{
	dbus_create_object_params(vrrp->iname, IF_NAME(IF_BASE_IFP(vrrp->ifp)), vrrp->vrid, vrrp->family, false);
}
