#include "lv_port_disp_template.h"
#include "lvgl.h"
#include "lcd.h"
#include "spi.h"

#define LCD_WIDTH   LCD_W
#define LCD_HEIGHT  LCD_H
#define PICE_HEIGHT 240

static lv_disp_drv_t disp_drv;

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

void lv_port_disp_init(void)
{
	SPI_Init();
    LCD_Init();

    static lv_disp_draw_buf_t draw_buf_dsc_1;
    lv_color_t * buf_1 = heap_caps_malloc(LCD_WIDTH*PICE_HEIGHT*sizeof(lv_color_t),MALLOC_CAP_DMA);
    //lv_color_t * buf_2 = heap_caps_malloc(LCD_WIDTH*PICE_HEIGHT*sizeof(lv_color_t),MALLOC_CAP_DMA);
    //static lv_color_t buf_1[LCD_WIDTH*PICE_HEIGHT];
    
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, LCD_WIDTH * PICE_HEIGHT);   /*Initialize the display buffer*/


    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;

    disp_drv.flush_cb = disp_flush;

    disp_drv.draw_buf = &draw_buf_dsc_1;

    lv_disp_drv_register(&disp_drv);
}

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    LCD_Fill(area->x1,area->y1,area->x2,area->y2,(uint16_t*)color_p);
    //lv_disp_flush_ready(disp_drv);
}

void spi_disp_flush_ready(void)
{
    lv_disp_flush_ready(&disp_drv);
}


