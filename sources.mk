# Source files
SOURCES =  ./main.c \
           ./startup.c \
           ./timer/timer.c \
           ./uart/uart.c \
           ./gps_module/gps.c \
           ./nmea_indexing/nmea.c \
           ./oled/ssd1306.c \
           ./gui/ugui.c
           
	   
# Include paths
INCLUDES = -I ./inc/ \
           -I ./timer/ \
           -I ./uart/ \
           -I ./gps_module/ \
           -I ./nmea_indexing/ \
           -I ./oled/ \
           -I ./gui/
           
