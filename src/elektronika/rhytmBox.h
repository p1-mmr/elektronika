
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	RHYTMBOX.H					(c)	YoY'01						WEB: www.vout.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_RHYTMBOX_H_
#define							_RHYTMBOX_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						"../elektro/elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidRHYTMBOX					(Arhytmbox::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							NBBANKS							6

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aseg7 : public Aobject
{
	AOBJ

								Aseg7							(char *name, Aobject *e, int x, int y, int w, int h, bool bstart=false);
	virtual						~Aseg7							();

	void						paint							(Abitmap *b);
	bool						notify							(Anode *o, int event, dword p);
	void						pulse							();

	void						set								(int v);

	Abutton						*up;
	Abutton						*down;
	Asegment					*seg;

	bool						bstart;

	int							wait;
	int							value;
	int							sens;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Arhytmbox : public Aeffect, public Athread
{
	AOBJ

								Arhytmbox						(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
	virtual						~Arhytmbox						();

	virtual void				settings						(bool emergency);

	virtual void				actionStop						();
	virtual void				action							(double time, double dtime, double beat, double dbeat);
	virtual void				run								();

	virtual bool				save							(Afile *f);
	virtual bool				load							(Afile *f);

	virtual bool				savePreset						(Afile *f);
	virtual bool				loadPreset						(Afile *f);

	virtual int					priority						()	{ return priorityIMPORT; }

	// private

	Abitmap						*image;
	//Asection					sectionImage;
	class RBvideo				*video[7];
	int							order[7];
	Asection					sectionVideo;
	bool						patternActive;
	bool						mPatternActive;
	int							patternStep;
	double						currentStep;
	bool						bCycle;
	bool						bCut;

	bool						bRun;
	bool						bStop;

	char						filename[7][ALIB_PATH];
	char						memoname[NBBANKS][7][ALIB_PATH];
	int							nbank;
	int							current;
	int							percent;
	char						loadedname[7][ALIB_PATH];

	bool						loadFile						(int nbox, char *filename);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ArhytmboxFront : public AeffectFront
{
	AOBJ

								ArhytmboxFront					(QIID qiid, char *name, Arhytmbox *e, int h);
	virtual						~ArhytmboxFront					();

	bool						notify							(Anode *o, int event, dword p);
	void						paint							(Abitmap *b);

	void						pulse							();
	
	void						moveBox							(int from, int to);

	Abitmap						*back;

	class ArhytmB				*box[7];
	class Asequence				*sequence;
	class AselButton			*eventType;
	class Atrigger				*steps;
	class ActrlButton			*buttonPattern;
	class Aseg7					*nsteps;
	class Aselect				*pattern;
	class Aselect				*patternABCD;
	class ActrlButton			*buttonCycle;
	class ActrlButton			*buttonCut;
	class Apaddle				*fadetime;
	
	class AseqPulse				*seqpulse;

	class Apaddle				*inLevel;
	class Apaddle				*fadeLevel;
	class Aselcolor				*fadeColor;
	class Apaddle				*zoomLevel;
	class Apaddle				*zoomSize;
	class Apaddle				*blurLevel;
	class Apaddle				*blurSize;

	class Apaddle				*master;

	class Arnbreso				*reso;
	Apaddle						*gpitch;

	Aselect						*bank;
	ActrlButton					*buttonSend;

	int							selected;
	
	sbyte						seqcopy[7][64];
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ArhytmboxBack : public AeffectBack
{
	AOBJ

								ArhytmboxBack					(QIID qiid, char *name, Arhytmbox *e, int h);
	virtual						~ArhytmboxBack					();

	void						paint							(Abitmap *b);

	Abitmap						*back;

	Avideo						*in;
	Avideo						*out;
	Avideo						*outa;
	Avideo						*outb;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ArhytmboxInfo : public AeffectInfo
{
	AOBJ 

								ArhytmboxInfo					(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return PLAYER; }
	virtual dword				version							() { return 0x00019900; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline ArhytmboxInfo::ArhytmboxInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz *					rhytmboxGetInfo						();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_RHYTMBOX_H
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
