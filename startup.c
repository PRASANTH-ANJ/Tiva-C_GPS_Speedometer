#include <stdint.h>

extern uint32_t _DATA_ROM_START;
extern uint32_t _DATA_RAM_START;
extern uint32_t _DATA_RAM_END;
extern uint32_t _BSS_START;
extern uint32_t _BSS_END;

#define STACK_TOP 0x20040000

extern int main(void);

void startup();

uint32_t * myvectors[2] __attribute__((section (".vectors"))) = {
	(uint32_t *) STACK_TOP,
	(uint32_t *) startup
};



void startup()
{
	/*Copy data belonging to '.data' section from its
	 * load time location in ROM (Flash) to its run-time
	 * location in SRAM.
	 */
	 
	 uint32_t * data_rom_start_p = &_DATA_ROM_START;
	 uint32_t * data_ram_start_p = &_DATA_RAM_START;
	 uint32_t * data_ram_end_p = &_DATA_RAM_END;
	 
	 while(data_ram_start_p != data_ram_end_p)
	{
		*data_ram_start_p = *data_rom_start_p;
		data_ram_start_p++;
		data_rom_start_p++;
	}
	
	
	/*Initialize data in the ".bss" section to zeros.
	*/
	
	uint32_t * bss_start_p = &_BSS_START;
	uint32_t * bss_end_p = &_BSS_END;
	
	while(bss_start_p != bss_end_p)
	{
		*bss_start_p = 0;
		bss_start_p++;
	}
	
	/*Call the main() function.
	*/
	
	main();

}
