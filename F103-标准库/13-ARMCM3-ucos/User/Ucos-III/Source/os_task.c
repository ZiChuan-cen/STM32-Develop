#include "os.h"

void OSTaskCreate (OS_TCB        *p_tcb,			//任务控制块
                   OS_TASK_PTR   p_task, 			//任务函数指针
                   void          *p_arg,			//任务中的参数
                   CPU_STK       *p_stk_base,		//任务栈的基地址
                   CPU_STK_SIZE  stk_size,			//任务栈的大小
                   OS_ERR        *p_err)			//任务反馈参数
{
	CPU_STK       *p_sp;

	p_sp = OSTaskStkInit (p_task,		//任务的入口地址
	p_arg,								//任务形参
	p_stk_base,
	stk_size);
	p_tcb->StkPtr = p_sp;
	p_tcb->StkSize = stk_size;

	*p_err = OS_ERR_NONE;
}

