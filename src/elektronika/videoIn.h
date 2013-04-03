/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	VIDEOIN.H					(c)	YoY'03						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_VIDEOIN_H_
#define							_VIDEOIN_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidVIDEOIN						(Avideoin::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							VIN_MAXPAD						10

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Avideoin : public Aeffect
{
	AOBJ

								Avideoin						(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
	virtual						~Avideoin						();

	virtual bool				save							(Afile *f);
	virtual bool				load							(Afile *f);

	virtual int					priority						()	{ return priorityIMPORT; }
	virtual void				settings						(bool emergency);
	
	virtual void				actionStart						(int time);
	virtual void				action							(double time, double dtime, double beat, double dbeat);
//	virtual void				actionStop						();

	class Avidcap				*vcap;
	Abitmap						*image;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AvideoinFront : public AeffectFront
{
	AOBJ

								AvideoinFront					(QIID qiid, char *name, Avideoin *e, int h);
	virtual						~AvideoinFront					();

	bool						save							(Afile *f);
	bool						load							(Afile *f);

	bool						notify							(Anode *o, int event, dword p);
	void						paint							(Abitmap *b);

	bool						system							(int event, dword d0, dword d1);
	void						pulse							();
	
	void						refresh							();
	
	
	Abitmap						*back;
	Alist						*device;
	Aitem						*idevice;
	Alist						*dialog;
	Aitem						*idialog;
	Alist						*standard;
	Aitem						*istandard;
	Alist						*source;
	Aitem						*isource;
	Abutton						*deinterlace;
	Apaddle						*pad[VIN_MAXPAD];
	HDEVNOTIFY					hDevNotify;
	char						olddev[256];
	char						curdev[256];
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AvideoinBack : public AeffectBack
{
	AOBJ

								AvideoinBack					(QIID qiid, char *name, Avideoin *e, int h);
	virtual						~AvideoinBack					();

	void						paint							(Abitmap *b);

	Abitmap						*back;
	Avideo						*video;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AvideoinInfo : public AeffectInfo
{
	AOBJ 

								AvideoinInfo					(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return INOUT; }
	virtual dword				version							() { return 0x00019902; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AvideoinInfo::AvideoinInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					videoinGetInfo					();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_VIDEOIN_H
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
