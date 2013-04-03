/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"elektroexp.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	TRIGGER.CPP					(c)	YoY'02						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						"trigger.h"
#include						"interface.h"
#include						"resource.h"
#include						"effect.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL ACI						Atrigger::CI		= ACI("Atrigger",		GUID(0xE4EC7600,0x00010100), &Aobject::CI, 0, NULL);
EDLL ACI						ActrlTrigger::CI	= ACI("ActrlTrigger",	GUID(0xE4EC7600,0x00010105), &Atrigger::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Atrigger::Atrigger(char *name, Aobject *e, int x, int y, int w, int h, int nbpos) : Aobject(name, e, x, y, w, h)
{
	this->nbpos=nbpos;
	ipos=0;
	trig=new Abitmap(&resdll.get(MAKEINTRESOURCE(PNG_TRIGGER), "PNG"));
	test=false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Atrigger::~Atrigger()
{
	delete(trig);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void Atrigger::paint(Abitmap *b)
{
	b->set(0, ipos*(pos.h-trig->h)/(nbpos-1), trig, bitmapDEFAULT, bitmapDEFAULT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool Atrigger::mouse(int x, int y, int state, int event)
{
	switch(event)
	{
		case mouseLDOWN:
		father->notify(this, nyPRESS, ipos);
		mouseCapture(true);
		test=true;

		case mouseNORMAL:
		cursor(cursorHANDSEL);
		focus(this);
		if(test)
		{
			int n=(nbpos*y)/Aobject::pos.h;
			if(n<0)
				n=0;
			else if(n>=nbpos)
				n=nbpos-1;
			if(n!=ipos)
			{
				ipos=n;
				father->notify(this, nyCHANGE, ipos);
				repaint();
			}
		}
		return true;

		case mouseLUP:
		case mouseLOSTCAPTURE:
		if(test)
		{
			int n=(nbpos*y)/pos.h;
			if(n<0)
				n=0;
			else if(n>=nbpos)
				n=nbpos-1;
			if(n!=ipos)
			{
				ipos=n;
				father->notify(this, nyCHANGE, ipos);
				repaint();
			}
			mouseCapture(false);
		}
		test=false;
		return true;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL ActrlTrigger::ActrlTrigger(QIID qiid, char *name, Aobject *L, int x, int y, int w, int h, int nbpos) : AcontrolObj(name, L, x, y, w, h)
{
	control=new Acontrol(qiid, name, Aeffect::getEffect(L), this, Acontrol::KEY_01+nbpos-1);
	trigger=new Atrigger(name, this, 0, 0, w, h, nbpos);
	trigger->show(true);
	trigger->ipos=-1;
	set(0);
	defpos=-1;
	ctrlPaint=false;
	timer(CTRLTIMEREPAINT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL ActrlTrigger::~ActrlTrigger()
{
	delete(control);
	delete(trigger);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void ActrlTrigger::paint(Abitmap *b)
{
	AcontrolObj::paint(b);
	controlPaint(b, pos.w, pos.h);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void ActrlTrigger::pulse()
{
	if(ctrlPaint)
	{
		repaint();
		ctrlPaint=false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool ActrlTrigger::sequence(int nctrl, float value)
{
	trigger->ipos=(int)value;
	father->notify(this, nyCHANGE, (int)value);
	ctrlPaint=true;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool ActrlTrigger::keyboard(int event, int ascii, int scan, int state)
{
	switch(event)
	{
		case keyboardDOWN:
		if(state&keyboardALT)
		{
			if(defpos!=-1)
				set(defpos);
			else
				set(0);
			father->notify(this, nyCHANGE);
			return true;
		}
		break;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool ActrlTrigger::mouse(int x, int y, int state, int event)
{
	if(getKeyboardState()&keyboardLALT)
	{
		if(defpos!=-1)
			set(defpos);
		else
			set(0);
		father->notify(this, nyCHANGE);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool ActrlTrigger::notify(Anode *o, int event, dword p)
{
	switch(event)
	{
		case nyPRESS:
		if(o==trigger)
		{
			control->select();
			return true;
		}
		break;
		
		case nyCHANGE:
		if(o==trigger)
		{
			control->select();
			control->set(Acontrol::KEY, (float)trigger->ipos);
			father->notify(this, nyCHANGE);
			return true;
		}
		break;
	}
	return AcontrolObj::notify(o, event, p);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL int ActrlTrigger::get()
{
	return trigger->ipos;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void ActrlTrigger::set(int p)
{
	if(trigger->ipos!=p)
	{
		trigger->ipos=p;
		if(defpos==-1)
			defpos=p;
		control->set(Acontrol::KEY, (float)trigger->ipos);
		repaint();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
