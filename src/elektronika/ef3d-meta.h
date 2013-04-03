/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ef3d-meta.H				(c)	YoY'03						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_EF3DMETA_H_
#define							_EF3DMETA_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidEF3Dmeta					(Aef3dmeta::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							META_DECAL						5
#define							META_GRIDSIZE					(1<<META_DECAL)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	byte					status;
	struct
	{
		float				x;
		float				y;
		float				z;
	}						pos;
	struct
	{
		float				x;
		float				y;
		float				z;
	}						normal;
} TmetaInfo;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aef3dmeta : public Aeffect3d
{
	AOBJ

								Aef3dmeta						(QIID qiid, char *name, Aobject *father, int x, int y);
	virtual						~Aef3dmeta						();

	virtual bool				notify							(Anode *o, int event, dword p);
	virtual void				paint							(Abitmap *b);

	virtual bool				load							(class Afile *f);
	virtual bool				save							(class Afile *f);

	virtual int					getTEXtype						()								{ return ef3dTEXpart; }

	virtual bool				init3D							(class Aef3dInfo *info);
	virtual bool				release3D						(class Aef3dInfo *info);

	virtual bool				action							(class Aef3dInfo *info);

	virtual void				settings						(bool emergency);
	
	virtual bool				fillSurface						();							

	
	TmetaInfo					info[META_GRIDSIZE][META_GRIDSIZE][META_GRIDSIZE][3];
	float						grid[META_GRIDSIZE][META_GRIDSIZE][META_GRIDSIZE];
	byte						test[META_GRIDSIZE][META_GRIDSIZE][META_GRIDSIZE];
	class Adatameta				*dt;
	class Apaddle				*zoom;
	class Apaddle				*mastef;
	class Apaddle				*efa[4];
	Abitmap						*back;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aef3dmetaInfo : public Aeffect3dInfo
{
	AOBJ 

								Aef3dmetaInfo					(char *name, ACI *eci, char *ename, char *ehelp);

	virtual Aeffect3d *			create							(QIID qiid, char *name, Aobject *father, int x, int y);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline Aef3dmetaInfo::Aef3dmetaInfo(char *name, ACI *eci, char *ename, char *ehelp) : Aeffect3dInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					ef3dmetaGetInfo					();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_EF3DMETA_H
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
