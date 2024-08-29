#include "Vtop.h"
#include "verilated.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "verilated_vcd_c.h"  // 用于波形文件
#include <nvboard.h>
int main(int argc, char** argv) {

	nvboard_bind_all_pins(&d);
	nvboard_init();
	VerilatedContext* contextp = new VerilatedContext;
	contextp->traceEverOn(true);
	contextp->commandArgs(argc, argv);
	VerilatedVcdC* tfp = new VerilatedVcdC;
	Vtop* top = new Vtop{contextp};
	top->trace(tfp, 99);  // 99是波形记
	tfp->open("waveform.vcd");
	while (!contextp->gotFinish()) {
		int a = rand() & 1;
		int b = rand() & 1;
		top->a = a;
		top->b = b;
		top->eval();
		printf("a = %d, b = %d, f = %d\n", a, b, top->f);

		assert(top->f == (a ^ b));
		contextp->timeInc(1);  // 增加仿真时
		tfp->dump(contextp->time());  // 记录波形数据
		nvboard_update();
	}
	nvboard_quit();
	tfp->close();
	delete top;
	delete contextp;
	delete tfp;
	return 0;

}
