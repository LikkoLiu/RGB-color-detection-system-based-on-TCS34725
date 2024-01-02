/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"


static void screen_table_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		lv_obj_add_state(guider_ui.screen_table_1, LV_STATE_EDITED);
		break;
	}
	default:
		break;
	}
}
static void screen_table_2_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		lv_obj_add_state(guider_ui.screen_table_2, LV_STATE_EDITED);
		break;
	}
	default:
		break;
	}
}
static void screen_table_3_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		lv_obj_add_state(guider_ui.screen_table_3, LV_STATE_EDITED);
		break;
	}
	default:
		break;
	}
}
static void screen_bar_2_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		lv_obj_add_state(guider_ui.screen_bar_2, LV_STATE_EDITED);
		break;
	}
	default:
		break;
	}
}
void events_init_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_table_1, screen_table_1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_table_2, screen_table_2_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_table_3, screen_table_3_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_bar_2, screen_bar_2_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
