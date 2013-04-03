/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"elektroexp.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	CONNECT.CPP					(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<assert.h>

#include						"table.h"
#include						"pin.h"
#include						"connect.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL ACI						Aconnect::CI=ACI("Aconnect", GUID(0xE4EC7600,0x00010030), &Anode::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aconnect::Aconnect(char *name, Atable *table, Apin *in, Apin *out) : Anode(name)
{
	assert((!in)||(in&&(in->type&pinDIR)==pinIN));
	assert((!out)||(out&&(out->type&pinDIR)==pinOUT));
	this->table=table;
	this->in=in;
	this->out=out;
	if(in&&out)
	{
		in->addConnect(out);
		out->addConnect(in);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aconnect::~Aconnect()
{
	if(in&&out)
	{
		in->removeConnect(out);
		out->removeConnect(in);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
