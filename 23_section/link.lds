SECTIONS
{
    . = ALIGN(16);
    _init_start = .;
    .usri_fn.0 : { *(.usri_fn.0) }
    .usri_fn.1 : { *(.usri_fn.1) }
    _init_end = .;
}
INSERT AFTER .rodata




