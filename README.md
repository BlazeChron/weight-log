# Compilation
```cd src/```

```gcc main.c regression.c datetonumber.c -o weight_logger```

# Usage

Put your weights in some file `logfile` in the format specified in `notes`

```cat logfile | weight_logger```

# Notes
Yes I'm using `cat`, no I haven't figured out file I/O
