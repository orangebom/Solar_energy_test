/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "fatfs.h"

uint8_t retSD;    /* Return value for SD */
char SDPath[4];   /* SD logical drive path */
FATFS SDFatFS;    /* File system object for SD logical drive */
FIL SDFile;       /* File object for SD */

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */    

void MX_FATFS_Init(void) 
{
  /*## FatFS: Link the SD driver ###########################*/
  retSD = FATFS_LinkDriver(&SD_Driver, SDPath);

  /* USER CODE BEGIN Init */
  /* additional user code for init */     
  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC 
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */  
}

/* USER CODE BEGIN Application */
 /**
  * ��������: FatFS�ļ�ϵͳ���������Ϣ����.
  * �������: FatFS�ļ�ϵͳ���������FRESULT
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void printf_fatfs_error(FRESULT fresult)
{
  switch(fresult)
  {
    case FR_OK:                   //(0)
      printf("�������ɹ���\r\n");
    break;
    case FR_DISK_ERR:             //(1)
      printf("����Ӳ�����������������\r\n");
    break;
    case FR_INT_ERR:              //(2)
      printf("�������Դ���\r\n");
    break;
    case FR_NOT_READY:            //(3)
      printf("���������豸�޷�������\r\n");
    break;
    case FR_NO_FILE:              //(4)
      printf("�����޷��ҵ��ļ���\r\n");
    break;
    case FR_NO_PATH:              //(5)
      printf("�����޷��ҵ�·����\r\n");
    break;
    case FR_INVALID_NAME:         //(6)
      printf("������Ч��·������\r\n");
    break;
    case FR_DENIED:               //(7)
    case FR_EXIST:                //(8)
      printf("�����ܾ����ʡ�\r\n");
    break;
    case FR_INVALID_OBJECT:       //(9)
      printf("������Ч���ļ���·����\r\n");
    break;
    case FR_WRITE_PROTECTED:      //(10)
      printf("�����߼��豸д������\r\n");
    break;
    case FR_INVALID_DRIVE:        //(11)
      printf("������Ч���߼��豸��\r\n");
    break;
    case FR_NOT_ENABLED:          //(12)
      printf("������Ч�Ĺ�������\r\n");
    break;
    case FR_NO_FILESYSTEM:        //(13)
      printf("������Ч���ļ�ϵͳ��\r\n");
    break;
    case FR_MKFS_ABORTED:         //(14)
      printf("���������������⵼��f_mkfs��������ʧ�ܡ�\r\n");
    break;
    case FR_TIMEOUT:              //(15)
      printf("����������ʱ��\r\n");
    break;
    case FR_LOCKED:               //(16)
      printf("�����ļ���������\r\n");
    break;
    case FR_NOT_ENOUGH_CORE:      //(17)
      printf("�������ļ���֧�ֻ�ȡ�ѿռ�ʧ�ܡ�\r\n");
    break;
    case FR_TOO_MANY_OPEN_FILES:  //(18)
      printf("������̫���ļ���\r\n");
    break;
    case FR_INVALID_PARAMETER:    // (19)
      printf("����������Ч��\r\n");
    break;
  }
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
