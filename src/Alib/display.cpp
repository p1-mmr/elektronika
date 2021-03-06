/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"export.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	DISPLAY.CPP					(c)	YoY'00						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						"display.h"
#include						"interface.h"
#include						"resource.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL ACI						Adisplay::CI=ACI("Adisplay", GUID(0xAE57E515,0x00001060), &Asurface::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Adisplay::Adisplay(char *name, Aobject *L, int x, int y, int w, int h, Aresobj *o, int ow, int oh, int mode) : Asurface(name, L, x, y, w, h)
{
	bitmap->flags=bitmapALPHA;
	bmp=new Abitmap(o);
	this->ow=ow;
	this->oh=oh;
	val=0.f;
	NCdisplay();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Adisplay::Adisplay(char *name, Aobject *L, int x, int y, int type) : Asurface(name, L, x, y, 8, 8)
{
	bitmap->flags|=bitmapALPHA;
	switch(type)
	{
		case displayVM0001:
		{
			Aresobj	o=alibres.get(MAKEINTRESOURCE(PNG_DISPLAY0001), "PNG");
			bmp=new Abitmap(&o);
			ow=32;
			oh=32;
			size(32, 32);
		}
		break;

		case displayVM0002:
		{
			Aresobj	o=alibres.get(MAKEINTRESOURCE(PNG_DISPLAY0002), "PNG");
			bmp=new Abitmap(&o);
			ow=32;
			oh=32;
			size(32, 32);
		}
		break;

		default:
		bitmap->flags&=~bitmapALPHA;
		bmp=NULL;
		break;
	}
	val=0.f;
	NCdisplay();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Adisplay::~Adisplay()
{
	if(bmp)
		delete(bmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void Adisplay::NCdisplay()
{
	if(bmp)
	{
		int	nx=bmp->w/ow;
		int	ny=bmp->h/oh;
		int	nb=nx*ny;
		int	n=mini((int)(val*(float)nb), nb-1);
		bitmap->set(0, 0, (n%nx)*ow, (n/nx)*oh, ow, oh, bmp, bitmapNORMAL, bitmapNORMAL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
