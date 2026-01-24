idf_component_register(
    SRCS
        "main.c"
        "Os/Os_Alarm.c"
        "Os/Os.c"
        "Bsp/Bsp_Lcd/Bsp_Lcd.c"
    INCLUDE_DIRS
        "."
        "Os"
        "Bsp/Bsp_Lcd"
        "App"
    REQUIRES
        lvgl
)

add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
