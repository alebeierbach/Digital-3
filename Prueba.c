


int main(int argc, char const *argv[])
{
	SystemInit();
	uint32_t verClk;
	verClk = SystemCoreClock;
	LPC_GPIO0->FIODIR |= ((1<<22)&(~(1<<19)));//output port0 pin 22
	LPC_GPIO0->FIOMASK = ~();//
	LPC_GPIO0->FIOMASK &= ~(1<<19);//

    return 0;
}
