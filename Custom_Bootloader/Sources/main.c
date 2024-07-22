/**
 * @file  : main.c
 * @author: Nguyen The Anh.
 * @brief : Definition of function using in file main.c
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include "../Includes/Driver/Driver_GPIO.h"
#include "../Includes/Driver/Driver_MCG.h"
#include "../Includes/Driver/Driver_SIM.h"
#include "../Includes/Driver/Driver_UART0.h"
#include "../Includes/Driver/Driver_core.h"
#include "../Includes/Srec/Srec.h"
#include "../Includes/HAL/FLASH.h"
#include <stdlib.h>

/*******************************************************************************
 * Macro
 ******************************************************************************/

/*Base address of application code*/
#define BASE_APP_ADDRESS (0xA000u)

/*Flash location that stores the start address of application code*/
#define APP_START_ADDRESS_LOCATION (0x9C00u)

/*Flash location that stores the size of application in sector*/
#define APP_SIZE_LOCATION (APP_START_ADDRESS_LOCATION + 4u)

/*Flash location stores the flag that indicates firmware updated successfully*/
#define APP_UPDATED_FLAG_LOCATION (APP_SIZE_LOCATION + 4u)

/*Flash location that stores header of the file*/
#define APP_HEADER_LOCATION (APP_UPDATED_FLAG_LOCATION + 4u)

/*\Indicating the app has been updated successfully*/
#define APP_UPDATE_SUCCESS (1u)

/*\Red LED port and pin macro*/
#define RED_LED_PORT (PORT_E)
#define RED_LED_PIN (29u)

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Static functions prototype
 ******************************************************************************/

/**
 * @brief Erase failed update application code in flash
 *
 * @param: This function has no parameter
 *
 * @return: This function return nothing
 */
static void Erase_failed_app(void);

/**
 * @brief Erase old application code in flash
 *
 * @param: This function has no parameter
 *
 * @return: This function return nothing
 */
static void Erase_Old_Application(void);

/**
 * @brief Get App size in sector
 *
 * @param App_size_byte: App size in byte
 *
 * @return App size in sector
 */
static uint32_t Get_App_size_sector(uint32_t App_size_byte);

/*******************************************************************************
 * Functions
 ******************************************************************************/

/**
 * @brief Erase failed update application code in flash
 */
static void Erase_failed_app(void)
{
    uint32_t i = 0;              /*i is used for traversaling the loop*/
    uint32_t written_sector = 0; /*This variable store the number of written sector in flash*/

    while (Read_FlashAddress(BASE_APP_ADDRESS + (i * 1024)) != FLASH_DELETED_VALUE)
    {
        written_sector++;
    }

    /*Erase failed application code*/
    Erase_Multi_Sector(APP_START_ADDRESS_LOCATION, written_sector + 1);

    return;
}

/**
 * @brief Erase old application code in flash
 */
static void Erase_Old_Application(void)
{
    uint32_t app_start_addr = 0;  /*This variable stores old application start address*/
    uint32_t app_size_sector = 0; /*This variable stores old application size in sector*/

    /*Get Application start address*/
    app_start_addr = Read_FlashAddress(APP_START_ADDRESS_LOCATION);

    /*Get Application size*/
    app_size_sector = Read_FlashAddress(APP_SIZE_LOCATION);

    /*Disable all current interrupts*/
    Driver_Disable_current_IRQs();

    /*Erase Application information sector*/
    Erase_Sector(APP_START_ADDRESS_LOCATION);

    /*Check if there is no App*/
    if ((app_start_addr == FLASH_DELETED_VALUE) && (app_size_sector == FLASH_DELETED_VALUE))
    {
        /*Do nothing*/
    }
    else
    {
        /*Erase old App*/
        Erase_Multi_Sector(app_start_addr, app_size_sector);
    }
    /*Enable all current interrupted interrupts*/
    Driver_Enable_current_IRQs();

    return;
}

/**
 * @brief Get App size in sector
 *
 * @param App_size_byte: App size in byte
 *
 * @return App size in sector
 */
static uint32_t Get_App_size_sector(uint32_t App_size_byte)
{
    if (App_size_byte % 1024 == 0)
    {
        App_size_byte = App_size_byte / 1024 + 1u;
    }
    else
    {
        App_size_byte = (App_size_byte / 1024) + 2u;
    }

    return App_size_byte;
}

/**
 * @brief Jump to application code in flash
 *
 * @param vector_start_addr: Start address of application code.
 *
 * @return: This function return nothing
 */
void jump_to_application(uint32_t vector_start_addr)
{
    static uint32_t s_new_Entry = 0;        /*This variable stores start address of new application*/
    static uint32_t s_new_StackPointer = 0; /*This varialle stores stack pointer initial value of new application*/
    static void (*s_entry)(void) = 0;       /*This variable store the entry of new application*/

    /*Get start address of application*/
    s_new_Entry = *(uint32_t *)(vector_start_addr + 4);

    /*Get initial value of stack pointer*/
    s_new_StackPointer = *(uint32_t *)vector_start_addr;

    /*Disable all current interrupts*/
    Driver_Disable_current_IRQs();

    /*Off set vector table*/
    Driver_Set_VectorTable_offset(BASE_APP_ADDRESS);

    /*Set initial stack pointer value*/
    Driver_Set_MSP(s_new_StackPointer);
    Driver_Set_PSP(s_new_StackPointer);

    /*Get new application entry*/
    s_entry = (void (*)(void))s_new_Entry;

    /*Jump to new application*/
    s_entry();

    return;
}

/**
 * @brief Boot main
 *
 * @param: This function has no param
 *
 * @return 1 if success, 0 if fail
 */
uint32_t Boot_main(void)
{
    uint32_t ret_val = 0;              /*This variable stores the function return value*/
    uint32_t i = 0;                    /*i is used for traversaling loop*/
    uint8_t queue_flag = 0;            /*This flag indicates if a queue element has received a full srec line*/
    uint8_t stop_flag = 0;             /*This flag indicates if the function need to stop*/
    uint8_t received_line[515] = {0};  /*Buffer for srec line*/
    srec_line record = {0};            /*This struct stores information of a parsed srec line*/
    uint32_t newApp_start_address = 0; /*This variable stores start address of new Application*/
    uint32_t newApp_sector_size = 0;   /*This variable stores size of new Application in byte*/
    uint32_t newApp_byte_size = 0;     /*This variable stores size of new Application in sector*/

    /*Erase old application*/
    Erase_Old_Application();

    /*Turn on the Red LED*/
    Driver_GPIO_set_pin_State(RED_LED_PORT, RED_LED_PIN, LOW_STATE);

    while (1)
    {
        /*Get queue flag*/
        queue_flag = Driver_UART0_check_first_buffer();

        /*If a queue element is ready and no stop sign*/
        if (1 == queue_flag && stop_flag == 0)
        {
            /*Get srec line from queue*/
            Driver_UART0_receive_string(received_line);
            /*Parse the srec line*/
            record = parse_Srecord_line(received_line);
            /*Check srec line*/
            stop_flag = check_srec_line(&record, received_line);

            /*If srec record is good*/
            if (0 == stop_flag)
            {
                /*If record is header*/
                if (S0 == record.type)
                {
                    /*Write header data to the App header location in flash*/
                    for (i = 0; i < record.data_word; i++)
                    {
                        Driver_Disable_current_IRQs();
                        Program_LongWord_8B(APP_HEADER_LOCATION + i * 4, &record.data[i * 4]);
                        Driver_Enable_current_IRQs();
                    }
                }
                /*If record is a termination record*/
                else if (S9 == record.type || S8 == record.type || S7 == record.type)
                {
                    newApp_sector_size = Get_App_size_sector(newApp_byte_size);

                    /*Program App start address and size to App information region*/
                    Driver_Disable_current_IRQs();
                    Program_LongWord(APP_SIZE_LOCATION, newApp_sector_size);
                    Program_LongWord(APP_UPDATED_FLAG_LOCATION, 1u);
                    Driver_Enable_current_IRQs();

                    ret_val = 1;
                    break;
                }
                /*If record is data record and has address greater or equal to base app address*/
                else if (record.address >= BASE_APP_ADDRESS)
                {
                    /*Get new App start address*/
                    if (0 == newApp_start_address)
                    {
                        newApp_start_address = record.address;
                        Driver_Disable_current_IRQs();
                        Program_LongWord(APP_START_ADDRESS_LOCATION, newApp_start_address);
                        Driver_Enable_current_IRQs();
                    }
                    else
                    {
                        /*Do nothing*/
                    }

                    /*Program data record to flash*/
                    for (i = 0; i < record.data_word; i++)
                    {
                        Driver_Disable_current_IRQs();
                        Program_LongWord_8B(record.address + i * 4, &record.data[i * 4]);
                        Driver_Enable_current_IRQs();
                    }

                    newApp_byte_size += record.data_word * 4;
                }
                /*If record address is smaller than base App address*/
                else
                {
                    /*Return error value*/
                    ret_val = 0;
                    break;
                }
            }
            /*If the received srec line is error*/
            else
            {
                /*Get current size of new Application*/
                newApp_sector_size = Get_App_size_sector(newApp_byte_size);

                /*Erase all written memory of new App*/
                Driver_Disable_current_IRQs();
                Erase_Multi_Sector(BASE_APP_ADDRESS, 50);
                Driver_Enable_current_IRQs();

                ret_val = 0;
                break;
            }
            /*Dequeue the queue*/
            Driver_UART0_dequeue();
        }
        else
        {
            /*Do nothing*/
        }
    }

    return ret_val;
}

/*Functions*********************************************************************
*
* Function name: main
* Description: main function of the program
*
END***************************************************************************/
int main(void)
{
    uint32_t MCGFLLCLK_frequency = 0; /*This variable stores the MCGFLLCLK freuquency*/
    uint32_t i = 0;                   /*i is used for traversaling loop*/
    uint32_t boot_state = 0;          /*This variable store status of boot*/
    uint8_t header_byte = 0;
    uint8_t header[50] = {0}; /*This array store header of Application*/

    /*SIM_SCGC4 configuration info*/
    SCGC4_config_info SCGC4_config = {
        .UART0_clock_gate = ENABLED,
    };

    /*SIM_SOPT2 configuration info*/
    SOPT2_config_info SOPT2_config = {
        .uart0_clock_source = MCGFLLCLK_HALF_MCGPLLCLK_CLOCK,
        .MCGPLLCLK_MCGFLLCLK_option = MCGFLLCLK_CLOCK_SELECTED};

    /*MCG_C4 configuration info*/
    MCG_C4_config_info MCG_C4_config = {
        .DCO_max_frequency = DCO_FIX_TUNED_MAX_FREQUENCY,
        .DCO_range = DCO_MID_RANGE,
    };

    /*UART0 configuration info*/
    uart0_config_info UART0_config = {
        .baud_rate = 115200,
        .OSR = 16,
        .Tx_Rx_port = PORT_A,
        .Tx_pin = 2,
        .Rx_pin = 1,
        .data_mode = DATA_8BITS,
        .parity_state = PARITY_DISABLED,
        .parity_type = 0,
        .stop_bit_count = ONE_STOP_BIT,
        .transmitter_state = TRANSMITTER_ENABLED,
        .receiver_state = RECEIVER_ENABLED,
        .transmiter_IRQ = TRANSMIT_IRQ_DISABLED,
        .receiver_IRQ = RECEIVE_IRQ_ENABLED,
    };

    /*Green LED configuration info*/
    GPIO_config_info_t green_LED = {
        .port_type = PORT_D,
        .pin = 5,
        .direction = GPIO_OUTPUT,
        .pull_type = PULL_DOWN,
        .initial_state = HIGH_STATE,
    };

    /*Red LED configuration info*/
    GPIO_config_info_t red_LED = {
        .port_type = PORT_E,
        .pin = 29,
        .direction = GPIO_OUTPUT,
        .initial_state = HIGH_STATE,
        .pull_type = PULL_DOWN,
    };

    /*Switch 1 configuration*/
    GPIO_config_info_t switch2 =
        {
            .port_type = PORT_C,
            .pin = 12,
            .direction = GPIO_INPUT,
            .pull_type = PULL_UP,
            .initial_state = HIGH_STATE,
        };

    /*SIM_SCGC5 configuration info*/
    SCGC5_config_info port_gate_config = {
        .PORTA_clock = ENABLED,
        .PORTB_clock = DISABLED,
        .PORTC_clock = ENABLED,
        .PORTD_clock = ENABLED,
        .PORTE_clock = ENABLED,
    };

    /*Init SIM_SCGC5*/
    Driver_SIM_SCGC5_init_clock(&port_gate_config);
    /*Init SIM_SCGC4*/
    Driver_SIM_SCGC4_init_clock(&SCGC4_config);
    /*Init SOPT2*/
    Driver_SIM_SOPT2_init(&SOPT2_config);
    /*Init the MCGFLLCLK clock*/
    Driver_MCG_Init_MCGFLLCLK(&MCG_C4_config);

    /*Get the MCGFLLCLK frequency*/
    MCGFLLCLK_frequency = Driver_MCG_get_MCGFLLCLK_frequency(&MCG_C4_config);

    /*Init UART0*/
    Driver_UART0_init(&UART0_config, MCGFLLCLK_frequency);
    /*Init green LED*/
    Driver_GPIO_init_pin(&green_LED);
    /*Init red LED*/
    Driver_GPIO_init_pin(&red_LED);
    /*Init Switch 1*/
    Driver_GPIO_init_pin(&switch2);
    /*Enable UART0 interrupt handler*/
    Driver_UART0_enable_interrupt_handler();

    Driver_UART0_send_string("\n---------------------------------------------------------------");
    Driver_UART0_send_string("\nProject: MCU MOCK - Custom Bootloader");
    Driver_UART0_send_string("\nAuthor : Nguyen The Anh");
    Driver_UART0_send_string("\nNote   :");
    Driver_UART0_send_string("\n   + App mode will run in default.");
    Driver_UART0_send_string("\n   + To enter boot mode, hold switch 2 then press reset");
    Driver_UART0_send_string("\n   + Red led will turn on during boot mode");
    Driver_UART0_send_string("\n---------------------------------------------------------------\n");

    /*If the Boot button is not pressed*/
    if (Driver_GPIO_read_pin_state(switch2.port_type, switch2.pin) == 1)
    {
        Driver_UART0_send_string("\n---------------------------------------------------------------");
        Driver_UART0_send_string("\nMode   : App mode");

        /*If there is no available App*/
        if (FLASH_DELETED_VALUE == Read_FlashAddress(APP_START_ADDRESS_LOCATION))
        {
            Driver_UART0_send_string("\nStatus : No Application");
            Driver_UART0_send_string("\nMessage: + Enter boot mode then send Srec file to update firmware");
            Driver_UART0_send_string("\n         + To enter boot mode, hold switch 2 then press reset");
            Driver_UART0_send_string("\n---------------------------------------------------------------\n");
        }
        else
        {
            if (APP_UPDATE_SUCCESS == Read_FlashAddress(APP_UPDATED_FLAG_LOCATION))
            {
                /*Get the header in header region*/
                header_byte = Read_Flash_byte(APP_HEADER_LOCATION);
                while (0xFFu != header_byte && '.' != header_byte)
                {
                    header[i] = header_byte;
                    i++;
                    header_byte = Read_Flash_byte(APP_HEADER_LOCATION + i);
                }

                Driver_UART0_send_string("\nApp    : ");
                Driver_UART0_send_string(header);
                Driver_UART0_send_string("\nStatus : Running");
                Driver_UART0_send_string("\nMessage: To enter boot mode, hold switch 2 then press reset");
                Driver_UART0_send_string("\n---------------------------------------------------------------\n");

                /*Jump to application to excute*/
                jump_to_application(Read_FlashAddress(APP_START_ADDRESS_LOCATION));
            }
            else
            {
                Driver_UART0_send_string("\nStatus : Lastest updated failed");
                Driver_UART0_send_string("\nMessage: + Enter boot mode then send Srec file to update firmware");
                Driver_UART0_send_string("\n         + To enter boot mode, hold switch 2 then press reset");
                Driver_UART0_send_string("\n---------------------------------------------------------------\n");
                /*Erase failed App code*/
                Erase_failed_app();
            }
        }
    }
    else
    {
        Driver_UART0_send_string("\n---------------------------------------------------------------");
        Driver_UART0_send_string("\nMode  : Boot mode");
        Driver_UART0_send_string("\nStatus: Waiting for receiving Srec file");

        boot_state = Boot_main();

        Driver_UART0_send_string("\n\nStatus: Receiving and Writing to flash\n");
        Driver_UART0_send_string("\nProcessing:");

        for (i = 0; i < 500000; i++)
        {
            if (i % 100000 == 0)
            {
                Driver_UART0_send_string(".");
            }
            else
            {
                /*Do nothing*/
            }
        }

        if (1 == boot_state)
        {
            Driver_UART0_send_string("\nUpdate has been finised, restart to lanch new Application");
            Driver_UART0_send_string("\n---------------------------------------------------------------\n");
        }
        else
        {
            Driver_UART0_send_string("\nStatus: Failed to update firmware");
            Driver_UART0_send_string("\nThe Boot process will be terminated.");
            Driver_UART0_send_string("\n---------------------------------------------------------------\n");
        }
    }

    return 0;
}
/*EOF*/
