///////////////////////////////////////////////////////////////////////////////
// (c) aestesis 2003 - code by renan jegouzo [aka YoY] - renan@aestesis.org
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// common input from elektronika

texture texture0;	// texture

float4	color;		// rendering color
float	beat;		// beat value [0..infinite] - 120bpm - ex: beat=120 after 1 mn elektronika running
float	rbeat;		// relative beat value 	[0..1]  0..1..0..1..0.. etc..
float	bass;		// bass audio level 	[0..1]
float	medium;		// medium audio level 	[0..1]
float	treble;		// treble audio level	[0..1]

///////////////////////////////////////////////////////////////////////////////
// effect special input (only float) elektronika assign a knob for each value (8 knobs max)

float	power;
float	speed;

///////////////////////////////////////////////////////////////////////////////
// effect global var

float	hz[2]={0.9845, 1.015151};

///////////////////////////////////////////////////////////////////////////////

struct PS_INPUT
{
	float2 vTexCoord: TEXCOORD;
};

///////////////////////////////////////////////////////////////////////////////

sampler SceneColorSampler = sampler_state
{
	texture = (texture0);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

float4 ps_filter( PS_INPUT v ) : COLOR
{
	float2	zyg,p;
	float	b=beat*speed;
	
	zyg.x=cos(v.vTexCoord.x*0.0145111f+b)+0.5;
	zyg.y=sin(v.vTexCoord.y*0.01216584f+b)+0.5;
	zyg-=v.vTexCoord;

	float d=zyg.x*zyg.x+zyg.y*zyg.y;

	p.x=cos(d)*power;
	p.y=sin(d)*power;

	p+=v.vTexCoord;

	p.x=(p.x+10.f)%1.f;
	p.y=(p.y+10.f)%1.f;
	
    return 	tex2D(SceneColorSampler, p)*color;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

technique elektronika
{
	pass P0
	{
		PixelShader = compile ps_2_0 ps_filter();
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
