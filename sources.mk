# Source files
SOURCES =  ./main.c \
           ./startup.c \
           ./timer/timer.c \
           ./uart/uart.c \
           ./gps_module/gps.c
	   
# Include paths
INCLUDES = -I ./inc/ \
           -I ./timer/ \
           -I ./uart/ \
           -I ./gps_module/
           
