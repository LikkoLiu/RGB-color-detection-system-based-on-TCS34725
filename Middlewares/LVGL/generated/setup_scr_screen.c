/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


void setup_scr_screen(lv_ui *ui)
{
	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen, 240, 280);

	//Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_spangroup_1
	ui->screen_spangroup_1 = lv_spangroup_create(ui->screen);
	lv_spangroup_set_align(ui->screen_spangroup_1, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_spangroup_1, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_spangroup_1, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_spangroup_1_span;
	screen_spangroup_1_span = lv_spangroup_new_span(ui->screen_spangroup_1);
	lv_span_set_text(screen_spangroup_1_span, "RGB red value");
	lv_style_set_text_color(&screen_spangroup_1_span->style, lv_color_hex(0x909090));
	lv_style_set_text_decor(&screen_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_spangroup_1_span->style, &lv_font_montserratMedium_10);
	lv_obj_set_pos(ui->screen_spangroup_1, 141, 28);
	lv_obj_set_size(ui->screen_spangroup_1, 107, 8);

	//Write style state: LV_STATE_DEFAULT for &style_screen_spangroup_1_main_default
	static lv_style_t style_screen_spangroup_1_main_default;
	ui_init_style(&style_screen_spangroup_1_main_default);
	
	lv_style_set_bg_opa(&style_screen_spangroup_1_main_default, 0);
	lv_style_set_border_width(&style_screen_spangroup_1_main_default, 0);
	lv_style_set_radius(&style_screen_spangroup_1_main_default, 0);
	lv_style_set_pad_top(&style_screen_spangroup_1_main_default, 0);
	lv_style_set_pad_right(&style_screen_spangroup_1_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_spangroup_1_main_default, 0);
	lv_style_set_pad_left(&style_screen_spangroup_1_main_default, 0);
	lv_style_set_shadow_width(&style_screen_spangroup_1_main_default, 0);
	lv_obj_add_style(ui->screen_spangroup_1, &style_screen_spangroup_1_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_spangroup_1);

	//Write codes screen_line_1
	ui->screen_line_1 = lv_line_create(ui->screen);
	static lv_point_t screen_line_1[] ={{0, 0},{0, 30},};
	lv_line_set_points(ui->screen_line_1, screen_line_1, 2);
	lv_obj_set_pos(ui->screen_line_1, 131, 28);
	lv_obj_set_size(ui->screen_line_1, 13, 26);

	//Write style for screen_line_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->screen_line_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->screen_line_1, lv_color_hex(0xff0000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->screen_line_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->screen_line_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_spangroup_2
	ui->screen_spangroup_2 = lv_spangroup_create(ui->screen);
	lv_spangroup_set_align(ui->screen_spangroup_2, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_spangroup_2, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_spangroup_2, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_spangroup_2_span;
	screen_spangroup_2_span = lv_spangroup_new_span(ui->screen_spangroup_2);
	lv_span_set_text(screen_spangroup_2_span, "RGB green value");
	lv_style_set_text_color(&screen_spangroup_2_span->style, lv_color_hex(0x909090));
	lv_style_set_text_decor(&screen_spangroup_2_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_spangroup_2_span->style, &lv_font_montserratMedium_10);
	lv_obj_set_pos(ui->screen_spangroup_2, 141, 73);
	lv_obj_set_size(ui->screen_spangroup_2, 107, 8);

	//Write style state: LV_STATE_DEFAULT for &style_screen_spangroup_2_main_default
	static lv_style_t style_screen_spangroup_2_main_default;
	ui_init_style(&style_screen_spangroup_2_main_default);
	
	lv_style_set_bg_opa(&style_screen_spangroup_2_main_default, 0);
	lv_style_set_border_width(&style_screen_spangroup_2_main_default, 0);
	lv_style_set_radius(&style_screen_spangroup_2_main_default, 0);
	lv_style_set_pad_top(&style_screen_spangroup_2_main_default, 0);
	lv_style_set_pad_right(&style_screen_spangroup_2_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_spangroup_2_main_default, 0);
	lv_style_set_pad_left(&style_screen_spangroup_2_main_default, 0);
	lv_style_set_shadow_width(&style_screen_spangroup_2_main_default, 0);
	lv_obj_add_style(ui->screen_spangroup_2, &style_screen_spangroup_2_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_spangroup_2);

	//Write codes screen_line_2
	ui->screen_line_2 = lv_line_create(ui->screen);
	static lv_point_t screen_line_2[] ={{0, 0},{0, 30},};
	lv_line_set_points(ui->screen_line_2, screen_line_2, 2);
	lv_obj_set_pos(ui->screen_line_2, 131, 73);
	lv_obj_set_size(ui->screen_line_2, 13, 26);

	//Write style for screen_line_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->screen_line_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->screen_line_2, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->screen_line_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->screen_line_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bar_3
	ui->screen_bar_3 = lv_bar_create(ui->screen);
	lv_obj_set_style_anim_time(ui->screen_bar_3, 256, 0);
	lv_bar_set_mode(ui->screen_bar_3, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_bar_3, 100, LV_ANIM_ON);
	lv_obj_set_pos(ui->screen_bar_3, 16, 73);
	lv_obj_set_size(ui->screen_bar_3, 100, 30);

	//Write style for screen_bar_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_bar_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_bar_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_bar_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_bar_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_bar_3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_bar_3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_bar_3, lv_color_hex(0x898989), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_bar_3, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_line_3
	ui->screen_line_3 = lv_line_create(ui->screen);
	static lv_point_t screen_line_3[] ={{0, 0},{0, 30},};
	lv_line_set_points(ui->screen_line_3, screen_line_3, 2);
	lv_obj_set_pos(ui->screen_line_3, 131, 118);
	lv_obj_set_size(ui->screen_line_3, 19, 26);

	//Write style for screen_line_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->screen_line_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->screen_line_3, lv_color_hex(0x0000ff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->screen_line_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->screen_line_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_bar_4
	ui->screen_bar_4 = lv_bar_create(ui->screen);
	lv_obj_set_style_anim_time(ui->screen_bar_4, 256, 0);
	lv_bar_set_mode(ui->screen_bar_4, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_bar_4, 100, LV_ANIM_ON);
	lv_obj_set_pos(ui->screen_bar_4, 16, 118);
	lv_obj_set_size(ui->screen_bar_4, 100, 30);

	//Write style for screen_bar_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_bar_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_bar_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_bar_4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_bar_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_bar_4, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_bar_4, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_bar_4, lv_color_hex(0x898989), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_bar_4, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_spangroup_3
	ui->screen_spangroup_3 = lv_spangroup_create(ui->screen);
	lv_spangroup_set_align(ui->screen_spangroup_3, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_spangroup_3, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_spangroup_3, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_spangroup_3_span;
	screen_spangroup_3_span = lv_spangroup_new_span(ui->screen_spangroup_3);
	lv_span_set_text(screen_spangroup_3_span, "RGB blue value");
	lv_style_set_text_color(&screen_spangroup_3_span->style, lv_color_hex(0x909090));
	lv_style_set_text_decor(&screen_spangroup_3_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_spangroup_3_span->style, &lv_font_montserratMedium_10);
	lv_obj_set_pos(ui->screen_spangroup_3, 141, 118);
	lv_obj_set_size(ui->screen_spangroup_3, 107, 8);

	//Write style state: LV_STATE_DEFAULT for &style_screen_spangroup_3_main_default
	static lv_style_t style_screen_spangroup_3_main_default;
	ui_init_style(&style_screen_spangroup_3_main_default);
	
	lv_style_set_bg_opa(&style_screen_spangroup_3_main_default, 0);
	lv_style_set_border_width(&style_screen_spangroup_3_main_default, 0);
	lv_style_set_radius(&style_screen_spangroup_3_main_default, 0);
	lv_style_set_pad_top(&style_screen_spangroup_3_main_default, 0);
	lv_style_set_pad_right(&style_screen_spangroup_3_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_spangroup_3_main_default, 0);
	lv_style_set_pad_left(&style_screen_spangroup_3_main_default, 0);
	lv_style_set_shadow_width(&style_screen_spangroup_3_main_default, 0);
	lv_obj_add_style(ui->screen_spangroup_3, &style_screen_spangroup_3_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_spangroup_3);

	//Write codes screen_RGB_R_Value
	ui->screen_RGB_R_Value = lv_table_create(ui->screen);
	lv_table_set_col_cnt(ui->screen_RGB_R_Value,1);
	lv_table_set_row_cnt(ui->screen_RGB_R_Value,1);
	lv_table_set_cell_value(ui->screen_RGB_R_Value,0,0,"256");
	lv_obj_set_pos(ui->screen_RGB_R_Value, 141, 39);
	lv_obj_set_scrollbar_mode(ui->screen_RGB_R_Value, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_RGB_R_Value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_pad_top(ui->screen_RGB_R_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_RGB_R_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_RGB_R_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_RGB_R_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_RGB_R_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_RGB_R_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_RGB_R_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_RGB_R_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_RGB_R_Value, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_RGB_R_Value, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_RGB_R_Value, &lv_font_Acme_Regular_14, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_RGB_R_Value, LV_TEXT_ALIGN_LEFT, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_RGB_R_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_RGB_R_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_RGB_R_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_RGB_R_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_RGB_R_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_RGB_R_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes screen_RGB_G_Value
	ui->screen_RGB_G_Value = lv_table_create(ui->screen);
	lv_table_set_col_cnt(ui->screen_RGB_G_Value,1);
	lv_table_set_row_cnt(ui->screen_RGB_G_Value,1);
	lv_table_set_cell_value(ui->screen_RGB_G_Value,0,0,"256");
	lv_obj_set_pos(ui->screen_RGB_G_Value, 141, 84);
	lv_obj_set_scrollbar_mode(ui->screen_RGB_G_Value, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_RGB_G_Value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_pad_top(ui->screen_RGB_G_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_RGB_G_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_RGB_G_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_RGB_G_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_RGB_G_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_RGB_G_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_RGB_G_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_RGB_G_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_RGB_G_Value, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_RGB_G_Value, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_RGB_G_Value, &lv_font_Acme_Regular_14, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_RGB_G_Value, LV_TEXT_ALIGN_LEFT, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_RGB_G_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_RGB_G_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_RGB_G_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_RGB_G_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_RGB_G_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_RGB_G_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes screen_RGB_B_Value
	ui->screen_RGB_B_Value = lv_table_create(ui->screen);
	lv_table_set_col_cnt(ui->screen_RGB_B_Value,1);
	lv_table_set_row_cnt(ui->screen_RGB_B_Value,1);
	lv_table_set_cell_value(ui->screen_RGB_B_Value,0,0,"256");
	lv_obj_set_pos(ui->screen_RGB_B_Value, 141, 129);
	lv_obj_set_scrollbar_mode(ui->screen_RGB_B_Value, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_RGB_B_Value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_pad_top(ui->screen_RGB_B_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_RGB_B_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_RGB_B_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_RGB_B_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_RGB_B_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_RGB_B_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_RGB_B_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_RGB_B_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_RGB_B_Value, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_RGB_B_Value, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_RGB_B_Value, &lv_font_Acme_Regular_14, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_RGB_B_Value, LV_TEXT_ALIGN_LEFT, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_RGB_B_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_RGB_B_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_RGB_B_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_RGB_B_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_RGB_B_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_RGB_B_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes screen_bar_2
	ui->screen_bar_2 = lv_bar_create(ui->screen);
	lv_obj_set_style_anim_time(ui->screen_bar_2, 256, 0);
	lv_bar_set_mode(ui->screen_bar_2, LV_BAR_MODE_SYMMETRICAL);
	lv_bar_set_value(ui->screen_bar_2, 100, LV_ANIM_ON);
	lv_obj_set_pos(ui->screen_bar_2, 16, 28);
	lv_obj_set_size(ui->screen_bar_2, 100, 30);

	//Write style for screen_bar_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_bar_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_bar_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_bar_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_bar_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_bar_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_bar_2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_bar_2, lv_color_hex(0x898989), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_bar_2, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_Clear_Value
	ui->screen_Clear_Value = lv_table_create(ui->screen);
	lv_table_set_col_cnt(ui->screen_Clear_Value,1);
	lv_table_set_row_cnt(ui->screen_Clear_Value,1);
	lv_table_set_cell_value(ui->screen_Clear_Value,0,0,"256");
	lv_obj_set_pos(ui->screen_Clear_Value, 15, 175);
	lv_obj_set_scrollbar_mode(ui->screen_Clear_Value, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_Clear_Value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_pad_top(ui->screen_Clear_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_Clear_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_Clear_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_Clear_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_Clear_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_Clear_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_Clear_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_Clear_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_Clear_Value, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_Clear_Value, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_Clear_Value, &lv_font_Acme_Regular_14, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_Clear_Value, LV_TEXT_ALIGN_LEFT, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_Clear_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_Clear_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_Clear_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_Clear_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_Clear_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_Clear_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes screen_spangroup_4
	ui->screen_spangroup_4 = lv_spangroup_create(ui->screen);
	lv_spangroup_set_align(ui->screen_spangroup_4, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_spangroup_4, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_spangroup_4, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_spangroup_4_span;
	screen_spangroup_4_span = lv_spangroup_new_span(ui->screen_spangroup_4);
	lv_span_set_text(screen_spangroup_4_span, "Clear value");
	lv_style_set_text_color(&screen_spangroup_4_span->style, lv_color_hex(0x909090));
	lv_style_set_text_decor(&screen_spangroup_4_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_spangroup_4_span->style, &lv_font_montserratMedium_10);
	lv_obj_set_pos(ui->screen_spangroup_4, 15, 165);
	lv_obj_set_size(ui->screen_spangroup_4, 107, 8);

	//Write style state: LV_STATE_DEFAULT for &style_screen_spangroup_4_main_default
	static lv_style_t style_screen_spangroup_4_main_default;
	ui_init_style(&style_screen_spangroup_4_main_default);
	
	lv_style_set_bg_opa(&style_screen_spangroup_4_main_default, 0);
	lv_style_set_border_width(&style_screen_spangroup_4_main_default, 0);
	lv_style_set_radius(&style_screen_spangroup_4_main_default, 0);
	lv_style_set_pad_top(&style_screen_spangroup_4_main_default, 0);
	lv_style_set_pad_right(&style_screen_spangroup_4_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_spangroup_4_main_default, 0);
	lv_style_set_pad_left(&style_screen_spangroup_4_main_default, 0);
	lv_style_set_shadow_width(&style_screen_spangroup_4_main_default, 0);
	lv_obj_add_style(ui->screen_spangroup_4, &style_screen_spangroup_4_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_spangroup_4);

	//Write codes screen_spangroup_5
	ui->screen_spangroup_5 = lv_spangroup_create(ui->screen);
	lv_spangroup_set_align(ui->screen_spangroup_5, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_spangroup_5, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_spangroup_5, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_spangroup_5_span;
	screen_spangroup_5_span = lv_spangroup_new_span(ui->screen_spangroup_5);
	lv_span_set_text(screen_spangroup_5_span, "Current gain level");
	lv_style_set_text_color(&screen_spangroup_5_span->style, lv_color_hex(0x909090));
	lv_style_set_text_decor(&screen_spangroup_5_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_spangroup_5_span->style, &lv_font_montserratMedium_10);
	lv_obj_set_pos(ui->screen_spangroup_5, 15, 205);
	lv_obj_set_size(ui->screen_spangroup_5, 107, 8);

	//Write style state: LV_STATE_DEFAULT for &style_screen_spangroup_5_main_default
	static lv_style_t style_screen_spangroup_5_main_default;
	ui_init_style(&style_screen_spangroup_5_main_default);
	
	lv_style_set_bg_opa(&style_screen_spangroup_5_main_default, 0);
	lv_style_set_border_width(&style_screen_spangroup_5_main_default, 0);
	lv_style_set_radius(&style_screen_spangroup_5_main_default, 0);
	lv_style_set_pad_top(&style_screen_spangroup_5_main_default, 0);
	lv_style_set_pad_right(&style_screen_spangroup_5_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_spangroup_5_main_default, 0);
	lv_style_set_pad_left(&style_screen_spangroup_5_main_default, 0);
	lv_style_set_shadow_width(&style_screen_spangroup_5_main_default, 0);
	lv_obj_add_style(ui->screen_spangroup_5, &style_screen_spangroup_5_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_spangroup_5);

	//Write codes screen_Gain_Value
	ui->screen_Gain_Value = lv_table_create(ui->screen);
	lv_table_set_col_cnt(ui->screen_Gain_Value,1);
	lv_table_set_row_cnt(ui->screen_Gain_Value,1);
	lv_table_set_cell_value(ui->screen_Gain_Value,0,0,"256");
	lv_obj_set_pos(ui->screen_Gain_Value, 15, 215);
	lv_obj_set_scrollbar_mode(ui->screen_Gain_Value, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_Gain_Value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_pad_top(ui->screen_Gain_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_Gain_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_Gain_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_Gain_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_Gain_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_Gain_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_Gain_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_Gain_Value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_Gain_Value, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_Gain_Value, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_Gain_Value, &lv_font_Acme_Regular_14, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_Gain_Value, LV_TEXT_ALIGN_LEFT, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_Gain_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_Gain_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_Gain_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_Gain_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_Gain_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_Gain_Value, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen);

	
}
