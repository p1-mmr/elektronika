/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"export.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	TOOLBAR.CPP					(c)	YoY'04						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						"resources.h"
#include						"toolbar.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL ACI						AtoolBar::CI=ACI("AtoolBar", GUID(0xAE57E515,0x00001130), &Aobject::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Atool : public Aobject
{
public:
	ALIBOBJ
	
	enum
	{
								T_NORMAL=0,
								T_OVER=1,
								T_SELECT=2
	};

	ADLL						Atool							(char *name, Aobject *father, int x, int y, Aresobj *res, int data);
	ADLL virtual				~Atool							();
	
	ADLL virtual void			paint							(Abitmap *b);
	ADLL virtual bool			mouse							(int x, int y, int state, int event);

	Abitmap						*image;
	int							select;
	int							data;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL ACI						Atool::CI=ACI("Atool", GUID(0xAE57E515,0x00001131), &Aobject::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Atool::Atool(char *name, Aobject *father, int x, int y, Aresobj *res, int data) : Aobject(name, father, x, y, 4, 4)
{
	select=T_NORMAL;
	this->data=data;
	image=new Abitmap(res);
	size(image->w/3, image->h);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Atool::~Atool()
{
	delete(image);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void Atool::paint(Abitmap *b)
{
	int	w=image->w/3;
	int	x=w*mini(select, T_SELECT);
	b->set(0, 0, x, 0, w, image->h, image);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool Atool::mouse(int x, int y, int state, int event)
{
	switch(event)
	{
		case mouseENTER:
		cursor(cursorHANDSEL);
		select|=T_OVER;
		repaint();
		return true;

		case mouseLEAVE:
		select&=~T_OVER;
		repaint();
		return true;
		
		case mouseLUP:
		case mouseMOVE:
		cursor(cursorHANDSEL);
		return true;
		
		case mouseLDOWN:
		cursor(cursorHANDSEL);
		if(!(select&T_SELECT))
		{
			select|=T_SELECT;
			father->notify(this, nyCLICK, data);
			repaint();
		}
		return true;
		
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL AtoolBar::AtoolBar(char *name, Aobject *L, int x, int y, int w, int h, int type) : Aobject(name, L, x, y, w, h)
{
	colorSEPARATOR=0xff404040;
	nbsep=0;
	this->type=type;
	icurrent=-1;
	ipos=0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL AtoolBar::~AtoolBar()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void AtoolBar::paint(Abitmap *b)
{
	int	i;
	for(i=0; i<nbsep; i++)
	{
		int	x=sep[i];
		b->line(x-1, 0, x-1, pos.h-1, colorSEPARATOR);
		b->line(x, 0, x, pos.h-1, colorSEPARATOR);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL bool AtoolBar::notify(Anode *o, int event, dword p)
{
	switch(event)
	{
		case nyCLICK:
		{
			Anode	*o=fchild;
			int		icurrent=p;
			while(o)
			{
				if(o->isCI(&Atool::CI))
				{
					Atool	*t=(Atool *)o;
					
					if((t->data!=icurrent)&&(t->select&Atool::T_SELECT))
					{
						t->select=Atool::T_NORMAL;
						t->repaint();
						break;
					}
				}
				o=(Anode *)o->next;
			}
			father->notify(this, nyCHANGE, icurrent);
		}
		return true;
	}
	return Aobject::notify(o, event, p);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void AtoolBar::set(int idata)
{
	icurrent=idata;
	{
		Anode	*o=fchild;
		while(o)
		{
			if(o->isCI(&Atool::CI))
			{
				Atool	*t=(Atool *)o;
				t->select=(t->data==idata)?Atool::T_SELECT:Atool::T_NORMAL;
			}
			o=(Anode *)o->next;
		}
	}
	repaint();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void AtoolBar::enable(int idata, bool b)
{
	Anode	*o=fchild;
	while(o)
	{
		if(o->isCI(&Atool::CI))
		{
			Atool	*t=(Atool *)o;
			if(t->data==idata)
			{
				if(b)
					t->state|=stateENABLE;
				else
				{
					t->state&=~stateENABLE;
					t->select=Atool::T_NORMAL;
					if(icurrent==idata)
						icurrent=NONE;
				}
				break;
			}
		}
		o=(Anode *)o->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void AtoolBar::enableAll(bool b)
{
	Anode	*o=fchild;
	while(o)
	{
		if(o->isCI(&Atool::CI))
		{
			Atool	*t=(Atool *)o;
			if(b)
				t->state|=stateENABLE;
			else
			{
				t->state&=~stateENABLE;
				t->select=Atool::T_NORMAL;
				if(icurrent==t->data)
					icurrent=NONE;
			}
		}
		o=(Anode *)o->next;
	}
	repaint();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void AtoolBar::addSeparator()
{
	if(ipos)
	{
		if(nbsep<MAXSEPARATOR)
			sep[nbsep++]=ipos+8;
		ipos+=16;
	}
	else
	{
		if(nbsep<MAXSEPARATOR)
			sep[nbsep++]=ipos+1;
		ipos+=9;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void AtoolBar::add(char *name, char *help, Aresobj *res, int data)
{
	switch(type)
	{
		case HORIZONTAL:
		{
			Atool *t=new Atool(name, this, ipos, 0, res, data);
			t->setTooltips(help);
			t->show(true);
			ipos+=4+t->image->w/3;
		}
		break;
		
		case VERTICAL:
		{
			Atool *t=new Atool(name, this, 0, ipos, res, data);
			t->setTooltips(help);
			t->show(true);
			ipos+=4+t->image->h;
		}
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
