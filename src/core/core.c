#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "key_buffers_manager.h"
#include "key_layout_provider.h"
#include "key_manager.h"
#include "key_scancodes.h"

#include "ll_adapter.h"

uint8_t pressed_keys[16] = {0};
keyboard_desc_st_t key_desc = {0};
usb_report_st_t usb_report = {0};
consumer_report_st_t consumer_report = {0};

static
void usb_report_init(void)
{
        usb_report.id = 1;
}

void key_descriptor_init(void)
{
        key_desc.keys_layout = get_keys_layout(OS_MAC);
        key_desc.consumer_layout = get_consumer_layout();

        key_desc.keys_row_cnt = get_keys_row_cnt();
        key_desc.keys_col_cnt = get_keys_col_cnt();
        key_desc.pressed_keys = pressed_keys;
}

void JumpToBootloader(void) {
    void (*SysMemBootJump)(void);
    //USBdeInit();
    
    /**
     * Step: Set system memory address. 
     *       
     *       For STM32F429, system memory is on 0x1FFF 0000
     *       For other families, check AN2606 document table 110 with descriptions of memory addresses 
     */
    volatile uint32_t addr = 0x1FFF0000;
    
    /**
     * Step: Disable RCC, set it to default (after reset) settings
     *       Internal clock, no PLL, etc.
     */
#if defined(USE_HAL_DRIVER)
    HAL_RCC_DeInit();
#endif /* defined(USE_HAL_DRIVER) */
#if defined(USE_STDPERIPH_DRIVER)
    RCC_DeInit();
#endif /* defined(USE_STDPERIPH_DRIVER) */
    
    /**
     * Step: Disable systick timer and reset it to default values
     */
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;
 
    /**
     * Step: Disable all interrupts
     */
    //__disable_irq();
    
    /**
     * Step: Remap system memory to address 0x0000 0000 in address space
     *       For each family registers may be different. 
     *       Check reference manual for each family.
     *
     *       For STM32F4xx, MEMRMP register in SYSCFG is used (bits[1:0])
     *       For STM32F0xx, CFGR1 register in SYSCFG is used (bits[1:0])
     *       For others, check family reference manual
     */
//    //Remap by hand... {
//#if defined(STM32F4)
//    SYSCFG->MEMRMP = 0x01;
//#endif
//#if defined(STM32F0)
//    SYSCFG->CFGR1 = 0x01;
//#endif
    //} ...or if you use HAL drivers
    __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();    //Call HAL macro to do this for you
    
    /**
     * Step: Set jump memory location for system memory
     *       Use address with 4 bytes offset which specifies jump location where program starts
     */
    SysMemBootJump = (void (*)(void)) (*((uint32_t *)(addr + 4)));
    
    /**
     * Step: Set main stack pointer.
     *       This step must be done last otherwise local variables in this function
     *       don't have proper value since stack pointer is located on different position
     *
     *       Set direct address location which specifies stack pointer in SRAM location
     */
    __set_MSP(*(uint32_t *)addr);
    
    /**
     * Step: Actually call our function to jump to set location
     *       This will start system memory execution
     */
    SysMemBootJump();
}

int user_main(void)
{
        usb_report_init();
        key_descriptor_init();

        timer_init();

        delay_ms(4000);

        while (true) {
                //JumpToBootloader();

                // 16k SRAM in address 0x2000 0000 - 0x2000 3FFF
                // Our STM32 F401 has:
                // 64kA 0x2000 0000 - 0x2000 FFFF
                //*((unsigned long *)0x20003FF0) = 0xDEADBEEF;
                //
                //// Reset the processor
                //NVIC_SystemReset();

                
                key_desc.pressed_consumer = 0;
                consumer_report.keys = 0;
                consumer_report.id = 2;

                get_pressed_keys(&key_desc);

                consumer_report.keys = key_desc.pressed_consumer;

                prepare_send_buffer(&key_desc, &usb_report);

                /* TODO: Without delay see some second report send lags.
                 * Maybe it is data structure corrupt */
                usb_send_report(&usb_report, sizeof(usb_report_st_t));
                delay_ms(5);
                usb_send_report(&consumer_report, sizeof(consumer_report_st_t));
                delay_ms(5);
        };

        return 0;
}
