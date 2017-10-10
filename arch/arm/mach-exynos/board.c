#include <common.h>
#include <config.h>
#include <asm/io.h>
void s_init(void)
{
	writel(readl(0x1002330c) | 0x300, 0x1002330c);
	writel(0, 0x11000c08);
}

void led1_test(int on)
{
	writel(0x10, 0x11000060);
	
	if(on == 1)
		writel(0x2, 0x11000064);
	else
		writel(0x0, 0x11000064);
}

void led2_test(int on)
{
	writel(0x1, 0x11000100);

	if(on == 1)
		writel(0x1, 0x11000104);
	else 
		writel(0x0, 0x11000104);
}
