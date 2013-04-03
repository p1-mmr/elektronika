/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	BAND.CPP					(c)	YoY'04						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<dsound.h>
#include						<assert.h>

#include						"band.h"
#include						"resource.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ACI								AbandInfo::CI	= ACI("AbandInfo",	GUID(0x11111112,0x00000880), &AeffectInfo::CI, 0, NULL);
ACI								Aband::CI		= ACI("Aband",		GUID(0x11111112,0x00000881), &Aeffect::CI, 0, NULL);
ACI								AbandFront::CI	= ACI("AbandFront",	GUID(0x11111112,0x00000882), &AeffectFront::CI, 0, NULL);
ACI								AbandBack::CI	= ACI("AbandBack",	GUID(0x11111112,0x00000883), &AeffectBack::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Aband::Aband(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule) : Aeffect(qiid, name, info, capsule)
{
	vleft=0.f;
	vright=0.f;
	front=new AbandFront(qiid, "band front", this, 50);
	front->setTooltips("3 bands filter");
	back=new AbandBack(qiid, "band back", this, 50);
	back->setTooltips("3 bands filter");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Aband::~Aband()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Aband::action(double time, double dtime, double beat, double dbeat)
{
	AbandFront	*front=(AbandFront *)this->front;
	Asample		*in=(Asample *)((AbandBack *)back)->in;
	Asample		*out=(Asample *)((AbandBack *)back)->out;
	float		bass=front->bass->get()*2.f;
	float		medium=front->medium->get()*2.f;
	float		treble=front->treble->get()*2.f;
	float		master=front->volume->get()*2.f;
	
	in->enter(__FILE__,__LINE__);
	out->enter(__FILE__,__LINE__);
	if(in->isConnected())
	{
		short	buf[8192][2];
		int		avaible=in->avaible();
		
		out->vmaster=master;
		out->vbass=bass;
		out->vmedium=medium;
		out->vtreeble=treble;
		
		while(avaible)
		{
			int	r=in->getBuffer((sword *)buf, null, null, null, 8192);
			out->addBuffer((short *)buf, r);
			avaible-=r;
		}
		
		vleft=mini(1.f, out->maxL);
		vright=mini(1.f, out->maxR);
	}
	out->leave();
	in->leave();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Aband::actionStop()
{
	vleft=0.f;
	vright=0.f;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AbandFront::AbandFront(QIID qiid, char *name, Aband *e, int h) : AeffectFront(qiid, name, e, h)
{
	Aresobj	o=resource.get(MAKEINTRESOURCE(PNG_BAND_FRONT), "PNG");
	back=new Abitmap(&o);

	int	hb=(h-32)>>1;
	
	volume=new Apaddle(MKQIID(qiid, 0x04acba5125ff01b0), "master", this, 399, 12, paddleYOLI24);
	volume->setTooltips("master level");
	volume->set(0.5f);
	volume->show(TRUE);

	bass=new Apaddle(MKQIID(qiid, 0xa5e5187313ca82c0), "eq/bass", this, 255, 10, paddleBUTTON02);
	bass->setTooltips("bass level");
	bass->set(0.5f);
	bass->show(TRUE);

	medium=new Apaddle(MKQIID(qiid, 0x00f0c3df956e1a64), "eq/medium", this, 297, 10, paddleBUTTON02);
	medium->setTooltips("medium level");
	medium->set(0.5f);
	medium->show(TRUE);

	treble=new Apaddle(MKQIID(qiid, 0x7fb2e64a4195fc40), "eq/treble", this, 339, 10, paddleBUTTON02);
	treble->setTooltips("treble level");
	treble->set(0.5f);
	treble->show(TRUE);

	left=new Adisplay("left vue meter", this, 450, hb, displayVM0001);
	left->setTooltips("left vue meter");
	left->show(TRUE);

	right=new Adisplay("right vue meter", this, 470, hb, displayVM0001);
	right->setTooltips("right vue meter");
	right->show(TRUE);

	m_vleft=0.f;
	m_vright=0.f;

	timer(40);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AbandFront::~AbandFront()
{
	delete(volume);
	delete(bass);
	delete(medium);
	delete(treble);
	delete(back);
	delete(left);
	delete(right);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AbandFront::paint(Abitmap *b)
{
	b->set(0, 0, back, bitmapDEFAULT, bitmapDEFAULT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AbandFront::pulse()
{
	Aband	*si=(Aband *)effect;
	m_vleft=(m_vleft+si->vleft)*0.5f;
	m_vright=(m_vright+si->vright)*0.5f;
	left->set(m_vleft);
	right->set(m_vright);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AbandBack::AbandBack(QIID qiid, char *name, Aband *e, int h) : AeffectBack(qiid, name, e, h)
{
	Aresobj	o=resource.get(MAKEINTRESOURCE(PNG_BAND_BACK), "PNG");
	back=new Abitmap(&o);

	in=new Asample(MKQIID(qiid, 0x0255616dcd216c00), "audio in", this, pinIN, 10, 10);
	in->setTooltips("audio input");
	in->show(TRUE);

	out=new Asample(MKQIID(qiid, 0x02351658cd216c00), "audio out", this, pinOUT, pos.w-18, 10);
	out->setTooltips("audio output");
	out->show(TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AbandBack::~AbandBack()
{
	delete(back);
	delete(in);
	delete(out);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AbandBack::paint(Abitmap *b)
{
	b->set(0, 0, back, bitmapDEFAULT, bitmapDEFAULT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Aeffect * AbandInfo::create(QIID qiid, char *name, Acapsule *capsule)
{
	return new Aband(qiid, name, this, capsule);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz * bandGetInfo()
{
	return new AbandInfo("bandInfo", &Aband::CI, "3 bands", "3 bands filter");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
