// dllmain.h: объ€вление класса модул€.

class CComponentModule : public ATL::CAtlDllModuleT< CComponentModule >
{
public :
	DECLARE_LIBID(LIBID_ComponentLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COMPONENT, "{08D41450-F8EE-4774-959A-B8423729D0C9}")
};

extern class CComponentModule _AtlModule;
