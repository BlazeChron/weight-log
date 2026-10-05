# Compilation
```cd src/```

```gcc main.c weight_calculator.c regression.c datetonumber.c -o weight_logger```

# Usage

Put your weights in some file `logfile` in the format specified in `notes`

```weight_logger weight_log [number of previous entries considered]```
