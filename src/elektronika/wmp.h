/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	WMP.H						(c)	YoY'03						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_WMP_H_
#define							_WMP_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidWMP							(Awmp::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							MAXWMP							128

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Awmp : public Aeffect
{
	AOBJ

								Awmp							(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
	virtual						~Awmp							();

	virtual bool				save							(Afile *f);
	virtual bool				load							(Afile *f);

	virtual bool				savePreset						(Afile *f);
	virtual bool				loadPreset						(Afile *f);

	virtual int					priority						()	{ return priorityFILTER; }
	virtual void				settings						(bool emergency);
	
	virtual void				action							(double time, double dtime, double beat, double dbeat);

	class AdataWMP				*dt;
	byte						sample[2][1024];
	Asection					section;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AwmpFront : public AeffectFront
{
	AOBJ

								AwmpFront						(QIID qiid, char *name, Awmp *e, int h);
	virtual						~AwmpFront						();

	bool						save							(Afile *f);
	bool						load							(Afile *f);

	bool						notify							(Anode *o, int event, dword p);
	void						paint							(Abitmap *b);

	//void						pulse							();
	
	bool						setEffect						(int n);
	bool						setPreset						(int n);

	Abitmap						*back;
	Alist						*drivers;
	Aitem						*driverItems;
	Alist						*preset;
	Aitem						*ipreset;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AwmpBack : public AeffectBack
{
	AOBJ

								AwmpBack						(QIID qiid, char *name, Awmp *e, int h);
	virtual						~AwmpBack						();

	void						paint							(Abitmap *b);

	Abitmap						*back;

	Asample						*in;
	Avideo						*out;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AwmpInfo : public AeffectInfo
{
	AOBJ 

								AwmpInfo						(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return EFFECT2D; }
	virtual dword				version							() { return 0x00010500; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AwmpInfo::AwmpInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					wmpGetInfo					();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_WMP_H
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
