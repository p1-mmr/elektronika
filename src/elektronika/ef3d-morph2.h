/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ef3d-morph2.H				(c)	YoY'03						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_EF3DMORPH2_H_
#define							_EF3DMORPH2_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidEF3DMORPH2					(Aef3dmorph2::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aef3dmorph2 : public Aeffect3d
{
	AOBJ

								Aef3dmorph2						(QIID qiid, char *name, Aobject *father, int x, int y);
	virtual						~Aef3dmorph2					();

	virtual bool				notify							(Anode *o, int event, dword p);
	virtual void				paint							(Abitmap *b);

	virtual bool				load							(class Afile *f);
	virtual bool				save							(class Afile *f);

	virtual int					getTEXtype						()								{ return ef3dTEXfull; }

	virtual bool				init3D							(class Aef3dInfo *info);
	virtual bool				release3D						(class Aef3dInfo *info);

	virtual bool				action							(class Aef3dInfo *info);

	virtual void				settings						(bool emergency);

	virtual bool				fillSurface						();							
	
	class Adatamorph2			*dt;
	class Apaddle				*zoom;
	class Apaddle				*mastef;
	class Apaddle				*ef[8];
	class Apaddle				*efa[3];
	class Abitmap				*back;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aef3dmorph2Info : public Aeffect3dInfo
{
	AOBJ 

								Aef3dmorph2Info					(char *name, ACI *eci, char *ename, char *ehelp);

	virtual Aeffect3d *			create							(QIID qiid, char *name, Aobject *father, int x, int y);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline Aef3dmorph2Info::Aef3dmorph2Info(char *name, ACI *eci, char *ename, char *ehelp) : Aeffect3dInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					ef3dmorph2GetInfo					();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_EF3DMORPH2_H
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
