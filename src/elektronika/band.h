/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	BAND.H						(c)	YoY'04						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_BAND_H_
#define							_BAND_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidBAND						(Aband::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aband : public Aeffect
{
	AOBJ

								Aband							(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
	virtual						~Aband							();

	virtual void				actionStop						();
	virtual void				action							(double time, double dtime, double beat, double dbeat);

	virtual int					priority						()	{ return priorityFILTER; }

	float						vleft;
	float						vright;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AbandFront : public AeffectFront
{
	AOBJ

								AbandFront						(QIID qiid, char *name, Aband *e, int h);
	virtual						~AbandFront						();

	void						paint							(Abitmap *b);
	void						pulse							();

	Abitmap						*back;

	Apaddle						*bass;
	Apaddle						*medium;
	Apaddle						*treble;
	Apaddle						*volume;
	Adisplay					*left;
	Adisplay					*right;

	float						m_vleft;
	float						m_vright;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AbandBack : public AeffectBack
{
	AOBJ

								AbandBack						(QIID qiid, char *name, Aband *e, int h);
	virtual						~AbandBack						();

	void						paint							(Abitmap *b);

	Abitmap						*back;

	Asample						*in;
	Asample						*out;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AbandInfo : public AeffectInfo
{
	AOBJ 

								AbandInfo						(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return EFFECTAUDIO; }
	virtual dword				version							() { return 0x00019900; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AbandInfo::AbandInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					bandGetInfo				();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_BAND_H
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
