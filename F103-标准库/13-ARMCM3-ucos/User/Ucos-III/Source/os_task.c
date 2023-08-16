#include "os.h"

void OSTaskCreate (OS_TCB        *p_tcb,			//������ƿ�
                   OS_TASK_PTR   p_task, 			//������ָ��
                   void          *p_arg,			//�����еĲ���
                   CPU_STK       *p_stk_base,		//����ջ�Ļ���ַ
                   CPU_STK_SIZE  stk_size,			//����ջ�Ĵ�С
                   OS_ERR        *p_err)			//����������
{
	CPU_STK       *p_sp;

	p_sp = OSTaskStkInit (p_task,		//�������ڵ�ַ
	p_arg,								//�����β�
	p_stk_base,
	stk_size);
	p_tcb->StkPtr = p_sp;
	p_tcb->StkSize = stk_size;

	*p_err = OS_ERR_NONE;
}

