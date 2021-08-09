SECTIONS
{
    . = ALIGN(16);
    _init_start = .;
    .usri_fn. : { *(.usri_fn.) }
    _init_end = .;
}
INSERT AFTER .rodata




