/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	trans-luma.H				(c)	YoY'04						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_TRANSLUMA_H_
#define							_TRANSLUMA_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<elektro.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidTRANSLUMA					(Atransluma::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Atransluma : public Atransition
{
	AOBJ

								Atransluma						(QIID qiid, char *name, Aobject *father, int x, int y);
	virtual						~Atransluma						();

	virtual bool				notify							(Anode *o, int event, dword p);
	virtual void				paint							(Abitmap *b);

	virtual bool				load							(class Afile *f);
	virtual bool				save							(class Afile *f);

	virtual bool				action							(Abitmap *out, Abitmap *in0, Abitmap *in1, float cross, int src, float power, Abitmap *in[8]);
	virtual void				settings						(bool emergency);

	void						luma							(Abitmap *out, Abitmap *in, float v, float fade);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AtranslumaInfo : public AtransitionInfo
{
	AOBJ 

								AtranslumaInfo					(char *name, ACI *eci, char *ename, char *ehelp);

	virtual Atransition *		create							(QIID qiid, char *name, Aobject *father, int x, int y);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AtranslumaInfo::AtranslumaInfo(char *name, ACI *eci, char *ename, char *ehelp) : AtransitionInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					translumaGetInfo				();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_TRANSLUMA_H
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
