/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"export.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	REGISTRY.CPP				(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						"registry.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL ACI						Aregistry::CI=ACI("Aregistry", GUID(0xAE57E515,0x00000450), &Anode::CI, 0, NULL); // countof(properties), properties);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Aregistry::Aregistry(char *name, int base) : Anode(name)
{
	HKEY	wbase;
	switch(base)
	{
		case CLASSES_ROOT:
		wbase=HKEY_CLASSES_ROOT;
		break;
		case CURRENT_USER:
		wbase=HKEY_CURRENT_USER;
		break;
		case LOCAL_MACHINE:
		default:
		wbase=HKEY_LOCAL_MACHINE;
		break;
		case USERS:
		wbase=HKEY_USERS;
		break;
		case CURRENT_CONFIG:
		wbase=HKEY_CURRENT_CONFIG;
		break;
	}								
	if(RegOpenKey(wbase, name, &hk)!=ERROR_SUCCESS)
	{
		if(RegCreateKey(wbase, name, &hk)==ERROR_SUCCESS)
			hk=NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Aregistry::~Aregistry()
{
	if(hk)
		RegCloseKey(hk);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Aregistry::write(char *name, char *s)
{
	if(hk)
		return RegSetValueEx(hk, name, 0, REG_SZ, (byte *)s, strlen(s)+1)==ERROR_SUCCESS;
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Aregistry::read(char *name, char *s, int size)
{
	if(hk)
	{
		DWORD	t;
		DWORD	sz=size;
		return RegQueryValueEx(hk, name, 0, &t, (byte *)s, &sz)==ERROR_SUCCESS;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Aregistry::read(char *name, int *value)
{
	if(hk)
	{
		DWORD	t;
		DWORD	size=sizeof(int);
		return RegQueryValueEx(hk, name, 0, &t, (byte *)value, &size)==ERROR_SUCCESS;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Aregistry::write(char *name, int value)
{
	if(hk)
		return RegSetValueEx(hk, name, 0, REG_DWORD, (byte *)&value, sizeof(value))==ERROR_SUCCESS;
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Aregistry::read(char *name, bool *value)
{
	if(hk)
	{
		DWORD	t;
		DWORD	size=sizeof(bool);
		return RegQueryValueEx(hk, name, 0, &t, (byte *)value, &size)==ERROR_SUCCESS;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Aregistry::write(char *name, bool value)
{
	if(hk)
		return RegSetValueEx(hk, name, 0, REG_DWORD, (byte *)&value, sizeof(value))==ERROR_SUCCESS;
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Aregistry::subEnum(int index, char *name, int size)
{
	if(hk)
		return RegEnumKey(hk, index, name, size)==ERROR_SUCCESS;
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
