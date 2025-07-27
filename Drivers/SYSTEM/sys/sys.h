/**
 ****************************************************************************************************
 * @file        sys.h
 * @version     V1.0
 * @brief       ϵͳ��ʼ������(����ʱ������/�жϹ���/GPIO���õ�)
 ****************************************************************************************************
 *
 * V1.0
 * ��ͷ�ļ�����·���ĳ����·��,�����ظ����ð���·�����鷳
 *
 ****************************************************************************************************
 */

#ifndef __SYS_H
#define __SYS_H

/***************************** ��׼��ͷ�ļ����� *****************************/
#include "gd32h7xx.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

/***************************** MiddleWare�ļ����� *****************************/
#include "elog.h"
#include "easyflash.h"
#include "multi_button.h"

/***************************** BSP�ļ����� *****************************/
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/Button/Button.h"

/**
 * SYS_SUPPORT_OS���ڶ���ϵͳ�ļ����Ƿ�֧��OS
 * 0,��֧��OS
 * 1,֧��OS
 */
#define SYS_SUPPORT_OS 0

/******************************************************************************************/

/* ��ͨ���� */
void sys_soft_reset(void);   /* ϵͳ��λ */
void sys_cache_enable(void); /* ʹ�� Cache */

/* ����Ϊ��ຯ�� */
void sys_wfi_set(void);          /* ִ��WFIָ�� */
void sys_intx_disable(void);     /* �ر������ж� */
void sys_intx_enable(void);      /* ���������ж� */
void sys_msr_msp(uint32_t addr); /* ����ջ����ַ */

#endif
