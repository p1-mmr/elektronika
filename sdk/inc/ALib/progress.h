/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	PROGRESS.H					(c)	YoY'05						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_PROGRESS_H_
#define							_PROGRESS_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"types.h"
#include						"surface.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	If you use directly the variables in the class API, it's at your own risks. Prefer the methods...   

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidPROGRESS					(Aprogress::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// a GUI progress bar
class Aprogress : public Aobject
{
public:
	ALIBOBJ

	enum
	{
								typeNORMAL=0
	};

	ADLL						Aprogress						(char *name, Aobject *L, int x, int y, Aresobj *o);
	ADLL						Aprogress						(char *name, Aobject *L, int x, int y, int type=typeNORMAL);
	ADLL virtual				~Aprogress						();

	virtual void				set								(float v)	{ val=mini(maxi(0.f, v), 1.f); repaint(); }

	ADLL virtual void			paint							(Abitmap *b);

private:

	Abitmap						*bmp;
	int							ow,oh;
	float						val;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_PROGRESS_H_
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
