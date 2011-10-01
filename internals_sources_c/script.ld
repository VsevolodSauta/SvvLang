ENTRY(_initAll)

MEMORY
{
	ram (rwx) : org = 0x400000, l = 4M
}

SECTIONS
{
	.text :
	{
		*(.text)
	}
	.data :
	{
		*(.data)
	}
	.rodata :
	{
		*(.rodata)
	}
	.initClasses :
	{
		initClassesStart = .;
		*(.initClasses)
		QUAD(0);
	}
}
