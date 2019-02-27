#include "klib/kio.h"
#include "klib/kstring.h"

unsigned short *videomem = (unsigned short *)0xB8000;
int attrib = 0x0F;
int px = 0, py = 0;

void kprintch(unsigned char x)
{
	unsigned att = attrib << 8;
	unsigned short *where = videomem + (py * 80 + px);
	*where = x | att;
	px++;
	if(px >= 80)
	{
		px = 0;
		py++;
	}
}

void kprintf(char *x)
{
	int n = kstrlen((unsigned char *)x);
	for(int i = 0; i < n; i++) kprintch(x[i]);
}
