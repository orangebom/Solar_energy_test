
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "key.h"
#include "led.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

FATFS fs;													/* FatFs�ļ�ϵͳ���� */
FIL file;													/* �ļ����� */
FRESULT f_res;                    /* �ļ�������� */
UINT fnum;            					  /* �ļ��ɹ���д���� */
BYTE ReadBuffer[1024]={0};        /* �������� */
BYTE WriteBuffer[]= "��ӭʹ��ӲʯSTM32������ �����Ǹ������ӣ��½��ļ�ϵͳ�����ļ�\n";/* д������*/  

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
  
  printf("****** �������в���... ******\r\n");	
	if(retSD == 0)
  {
	//��SD�������ļ�ϵͳ���ļ�ϵͳ����ʱ���SD����ʼ��
	f_res = f_mount(&fs,(TCHAR const*)SDPath,1);
	printf_fatfs_error(f_res);
    /*----------------------- ��ʽ������ ---------------------------*/  
    /* ���û���ļ�ϵͳ�͸�ʽ�����������ļ�ϵͳ */
    if(f_res == FR_NO_FILESYSTEM)
    {
      printf("��SD����û���ļ�ϵͳ���������и�ʽ��...\r\n");
      /* ��ʽ�� */
      f_res=f_mkfs((TCHAR const*)SDPath,0,0);							
      
      if(f_res == FR_OK)
      {
        printf("��SD���ѳɹ���ʽ���ļ�ϵͳ��\r\n");
        /* ��ʽ������ȡ������ */
        f_res = f_mount(NULL,(TCHAR const*)SDPath,1);			
        /* ���¹���	*/			
        f_res = f_mount(&fs,(TCHAR const*)SDPath,1);
      }
      else
      {
        printf("������ʽ��ʧ�ܡ�����\r\n");
        while(1);
      }
    }
    else if(f_res!=FR_OK)
    {
      printf("����SD�������ļ�ϵͳʧ�ܡ�(%d)\r\n",f_res);
      printf_fatfs_error(f_res);
      while(1);
    }
    else
    {
      printf("���ļ�ϵͳ���سɹ������Խ��ж�д����\r\n");
    }
    
    /*----------------------- �ļ�ϵͳ���ԣ�д���� -----------------------------*/
    /* ���ļ�������ļ��������򴴽��� */
    printf("****** ���������ļ�д�����... ******\r\n");	
    f_res = f_open(&file, "FatFs��д�����ļ�.txt",FA_CREATE_ALWAYS | FA_WRITE );
    if ( f_res == FR_OK )
    {
      printf("����/����FatFs��д�����ļ�.txt�ļ��ɹ������ļ�д�����ݡ�\r\n");
      /* ��ָ���洢������д�뵽�ļ��� */
      f_res=f_write(&file,WriteBuffer,sizeof(WriteBuffer),&fnum);
      if(f_res==FR_OK)
      {
        printf("���ļ�д��ɹ���д���ֽ����ݣ�%d\r\n",fnum);
        printf("�����ļ�д�������Ϊ��\r\n%s\r\n",WriteBuffer);
      }
      else
      {
        printf("�����ļ�д��ʧ�ܣ�(%d)\r\n",f_res);
      }    
      /* ���ٶ�д���ر��ļ� */
      f_close(&file);
    }
    else
    {	
      printf("������/�����ļ�ʧ�ܡ�\r\n");
    }
    
    /*------------------- �ļ�ϵͳ���ԣ������� ------------------------------------*/
    printf("****** ���������ļ���ȡ����... ******\r\n");
    f_res = f_open(&file, "FatFs��д�����ļ�.txt", FA_OPEN_EXISTING | FA_READ); 	 
    if(f_res == FR_OK)
    {
      printf("�����ļ��ɹ���\r\n");
      f_res = f_read(&file, ReadBuffer, sizeof(ReadBuffer), &fnum); 
      if(f_res==FR_OK)
      {
        printf("���ļ���ȡ�ɹ�,�����ֽ����ݣ�%d\r\n",fnum);
        printf("����ȡ�õ��ļ�����Ϊ��\r\n%s \r\n", ReadBuffer);	
      }
      else
      {
        printf("�����ļ���ȡʧ�ܣ�(%d)\r\n",f_res);
      }		
    }
    else
    {
      printf("�������ļ�ʧ�ܡ�\r\n");
    }
    /* ���ٶ�д���ر��ļ� */
    f_close(&file);
    
    /* ����ʹ�ã�ȡ������ */
    f_res = f_mount(NULL,(TCHAR const*)SDPath,1);	
  
  /* ע��һ��FatFS�豸��SD�� */
    FATFS_UnLinkDriver(SDPath);
	}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
