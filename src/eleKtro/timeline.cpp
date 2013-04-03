/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"elektroexp.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	TIMELINE.CPP				(c)	YoY'05						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						<assert.h>
#include						"timeline.h"
#include						"interface.h"
#include						"resource.h"
#include						"effect.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL ACI						Atimeline::CI		= ACI("Atimeline",	GUID(0xE4EC7600,0x00010140), &AcontrolObj::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Atimehand : public Aobject
{
public:
	ELIBOBJ

	enum
	{
								typeCUR,
								typeSTA,
								typeEND
	};


	dword						color;
	int							type;
	bool						test;
	int							xx;

		 						Atimehand						(char *name, Aobject *L, int x, int y, int w, int h, dword color, int type);
	virtual						~Atimehand						();

	virtual void				paint							(Abitmap *b);
	virtual bool				mouse							(int x, int y, int state, int event);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL ACI						Atimehand::CI		= ACI("Atimehand",	GUID(0xE4EC7600,0x00010141), &Acontrol::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Atimehand::Atimehand(char *name, Aobject *L, int x, int y, int w, int h, dword color, int type) : Aobject(name, L, x, y, w, h)
{
	this->color=color;
	this->type=type;
	test=false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Atimehand::~Atimehand()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Atimehand::paint(Abitmap *b)
{
	int x=(pos.w-1)/2;
	int y=(pos.h-1)/2;
	int	h=pos.h/2;
	int i;

	b->linea(x, 0, x, pos.h, color);
	b->linea(x+1, 0, x+1, pos.h, color);

	switch(type)
	{
		case typeCUR:
		for(i=0; i<h; i++)
		{
			int xi=h-i;
			b->linea(x-xi, i, x+1+xi, i, color);
		}
		break;

		case typeSTA:
		case typeEND:
		for(i=0; i<h; i++)
		{
			int xi=h-i;;
			b->linea(x-xi, pos.h-1-i, x+1+xi, pos.h-1-i, color);
		}
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Atimehand::mouse(int x, int y, int state, int event)
{
	switch(event)
	{
		case mouseLDOWN:
		if((type==typeEND)&&(((Atimeline *)father)->getSelBegin()==1.f))	// start & len at the end position
			return ((Atimeline *)father)->osta->mouse(x, y, state, event);
		cursor(cursorHANDSEL);
		mouseCapture(true);
		test=true;
		xx=x;
		focus(this);
		father->notify(this, nyPRESS, type);
		return true;

		case mouseMOVE:
		cursor(cursorHANDSEL);
		if(test)
		{
			int nx=pos.x+x-xx;
			((Atimeline *)father)->moveX(type, nx);
		}
		return true;

		case mouseLUP:
		case mouseLEAVE:
		mouseCapture(false);
		test=false;
		father->notify(this, nyRELEASE, type);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Atimeline::Atimeline(QIID qiid, char *name, Aobject *L, int x, int y, int w, int h, dword colorBACK, dword colorSEL, dword colorCUR) : AcontrolObj(name, L, x, y, w, h)
{
	control=new Acontrol(qiid, name, Aeffect::getEffect(L), this, Acontrol::CONTROLER_03);
	control->setInfo(Acontrol::CONTROLER_01, "current", 0xff808000);
	control->setInfo(Acontrol::CONTROLER_02, "sel begin", 0xff808000);
	control->setInfo(Acontrol::CONTROLER_03, "sel length", 0xff008000);
	begin=current=0.f;
	length=1.f;
	this->colorBACK=colorBACK;
	this->colorSEL=colorSEL;
	this->colorCUR=colorCUR;
	int hh=pos.h/3;
	osta=new Atimehand("begin", this, pos.h/2, hh, pos.h, pos.h-hh, colorCUR, Atimehand::typeSTA);
	osta->show(true);
	olen=new Atimehand("lenght", this, pos.w-(pos.h*3)/2, hh, pos.h, pos.h-hh, colorCUR, Atimehand::typeEND);
	olen->show(true);
	ocur=new Atimehand("current", this, pos.w/2, 0, pos.h, pos.h-hh, colorCUR, Atimehand::typeCUR);
	ocur->show(true);
	ctrlPaint=false;
	timer(CTRLTIMEREPAINT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Atimeline::~Atimeline()
{
	delete(control);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void Atimeline::pulse()
{
	if(ctrlPaint)
	{
		repaint();
		ctrlPaint=false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void Atimeline::paint(Abitmap *b)
{
	int	h=pos.h/3;
	//controlPaint(b, pos.w, pos.h);
	//b->boxfa(0, 0, pos.w, pos.h, colorBACK);
	b->boxfa(pos.h, h, pos.w-pos.h, pos.h-1-h, colorBACK);
	{
		float	e=mini(begin+length, 1.f);
		b->boxfa(pos.h+(int)(begin*(float)(pos.w-pos.h*2)), h, pos.h+(int)(e*(float)(pos.w-pos.h*2)), pos.h-1-h, colorSEL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Atimeline::mouse(int x, int y, int state, int event)
{
	switch(event)
	{
		case mouseLDOWN:
		moveX(Atimehand::typeCUR, x-ocur->pos.w/2);
		ocur->mouse(ocur->pos.w/2, 0, state, event);
		return true;

		case mouseMOVE:
		return true;

		case mouseLUP:
		case mouseLEAVE:
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Atimeline::moveX(int type, int x)
{
	x=mini(maxi(x, pos.h/2), pos.w-pos.h*3/2);
	float	v=(float)(x-pos.h/2)/(float)(pos.w-2*pos.h);
	switch(type)
	{
		case Atimehand::typeCUR:
		setCurrent(v);
		father->notify(this, nyCHANGE, changeCUR);
		break;
		case Atimehand::typeSTA:
		{
			float vlen=getSelLength();
			setSelBegin(v);
			if(vlen!=getSelLength())
				father->notify(this, nyCHANGE, changeLEN);
			father->notify(this, nyCHANGE, changeSTA);
		}
		break;
		case Atimehand::typeEND:
		setSelLength(v-getSelBegin());
		father->notify(this, nyCHANGE, changeLEN);
		break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool Atimeline::notify(Anode *o, int event, dword p)
{
	switch(event)
	{
		case nyPRESS:
		case nyRELEASE:
		control->select();
		father->notify(this, event, p);
		break;

		case nyCHANGE:
		return true;
	}
	return AcontrolObj::notify(o, event, p);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool Atimeline::sequence(int nctrl, float value)
{
	switch(nctrl)
	{
		case Acontrol::CONTROLER_01:	
		setCurrent(value, false);
		father->notify(this, nyCHANGE, changeCUR);
		break;
		case Acontrol::CONTROLER_02:
		setSelBegin(value, false);
		father->notify(this, nyCHANGE, changeSTA);
		break;
		case Acontrol::CONTROLER_03:
		setSelLength(value);
		father->notify(this, nyCHANGE, changeLEN);
		break;
	}
	ctrlPaint=true;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL float Atimeline::getCurrent()
{
	return current;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void Atimeline::setCurrent(float current, bool sendControl)
{
	float	l=this->current;
	this->current=maxi(mini(current, 1.f), 0.f);
	if(l!=this->current)
	{
		int	x=(int)((float)(pos.w-pos.h*2)*this->current)+pos.h/2;
		ocur->move(x,ocur->pos.y);
		if(sendControl)
			control->set(Acontrol::CONTROLER_01, current);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL float Atimeline::getSelBegin()
{
	return begin;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void Atimeline::setSelBegin(float begin, bool sendControl)
{
	float	l=this->begin;
	this->begin=maxi(mini(begin, 1.f), 0.f);
	if(l!=this->begin)
	{
		int		x=(int)((float)(pos.w-pos.h*2)*this->begin)+pos.h/2;
		osta->move(x,osta->pos.y);
		if(sendControl)
			control->set(Acontrol::CONTROLER_02, begin);
		setSelLength(getSelLength());
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL float Atimeline::getSelLength()
{
	return length;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void Atimeline::setSelLength(float length, bool sendControl)
{
	float	l=this->length;
	this->length=mini(maxi(length, 0.f), 1.f-begin);
	{
		int	x=(int)((float)(pos.w-pos.h*2)*(begin+this->length))+pos.h/2;
		if(x!=olen->pos.x)
			olen->move(x,olen->pos.y);
	}
	if(l!=this->length)
	{
		if(sendControl)
			control->set(Acontrol::CONTROLER_03, length);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
