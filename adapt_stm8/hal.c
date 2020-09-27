void enableInterrupt(void)
{
	__asm__("rim"); // enable interrupt
}

void waitForInterrupt(void)
{
	__asm__("wfi");
}
