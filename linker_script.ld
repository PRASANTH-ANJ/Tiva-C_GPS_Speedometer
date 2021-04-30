SECTIONS
{
	. = 0x0; /* Reseting location counter to 0 */
	.text : 
	{
		*(.vectors) /* Vector Table */
		*(.text) /* Program Code */
		KEEP (*(.eh_frame))
	}
	
	.rodata : 
	{
		*(.rodata) /* Read-only data */
	}
	
	.ARM :
    	{
       	 __exidx_start = .;
        	*(.ARM.exidx*)
        	__exidx_end = .;
    	}
	
	_DATA_ROM_START = .;
	
	. = 0x20000000;
	
	_DATA_RAM_START = .;
	
	.data : AT(_DATA_ROM_START)
	{
		*(.data) /* Data memory */
	}
	
	_DATA_RAM_END = .;
	
	_BSS_START = .;
	__bss_start__ = .;
	
	.bss :
	{
		*(.bss) /* Zero filled runtime allocated data memory */
	}
	
	_BSS_END = .;
	__bss_end__ = .;
}
