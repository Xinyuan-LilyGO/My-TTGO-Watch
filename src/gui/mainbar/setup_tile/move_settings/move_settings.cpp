#include "config.h"
#include "move_settings.h"

#include "gui/mainbar/mainbar.h"
#include "gui/statusbar.h"
#include "hardware/bma.h"

lv_obj_t *move_settings_tile1=NULL;
lv_obj_t *stepcounter_onoff=NULL;
lv_obj_t *doubleclick_onoff=NULL;
lv_style_t move_settings_style;

LV_IMG_DECLARE(exit_32px);
LV_IMG_DECLARE(move_32px);

static void exit_move_setup_event_cb( lv_obj_t * obj, lv_event_t event );
static void stepcounter_onoff_event_handler(lv_obj_t * obj, lv_event_t event);
static void doubleclick_onoff_event_handler(lv_obj_t * obj, lv_event_t event);

void move_settings_tile_setup( lv_obj_t *tile, lv_style_t *style, lv_coord_t hres, lv_coord_t vres ) {
    lv_style_init( &move_settings_style );
    lv_style_set_radius( &move_settings_style, LV_OBJ_PART_MAIN, 0);
    lv_style_set_bg_color( &move_settings_style, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
    lv_style_set_bg_opa( &move_settings_style, LV_OBJ_PART_MAIN, LV_OPA_100);
    lv_style_set_border_width( &move_settings_style, LV_OBJ_PART_MAIN, 0);
    lv_style_set_text_color( &move_settings_style, LV_OBJ_PART_MAIN, LV_COLOR_BLACK);
    lv_style_set_image_recolor( &move_settings_style, LV_OBJ_PART_MAIN, LV_COLOR_BLACK);

    move_settings_tile1 = lv_obj_create( tile, NULL);
    lv_obj_set_size(move_settings_tile1, hres , vres);
    lv_obj_align(move_settings_tile1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style( move_settings_tile1, LV_OBJ_PART_MAIN, &move_settings_style );

    lv_obj_t *exit_btn = lv_imgbtn_create( move_settings_tile1, NULL);
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_RELEASED, &exit_32px);
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_PRESSED, &exit_32px);
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_CHECKED_RELEASED, &exit_32px);
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_CHECKED_PRESSED, &exit_32px);
    lv_obj_add_style( exit_btn, LV_IMGBTN_PART_MAIN, style);
    lv_obj_align( exit_btn, move_settings_tile1, LV_ALIGN_IN_TOP_LEFT, 10, STATUSBAR_HEIGHT + 10 );
    lv_obj_set_event_cb( exit_btn, exit_move_setup_event_cb );
    
    lv_obj_t *exit_label = lv_label_create( move_settings_tile1, NULL);
    lv_obj_add_style( exit_label, LV_OBJ_PART_MAIN, style );
    lv_label_set_text( exit_label, "movement settings");
    lv_obj_align( exit_label, exit_btn, LV_ALIGN_OUT_RIGHT_MID, 5, 0 );

    lv_obj_t *stepcounter_cont = lv_obj_create( move_settings_tile1, NULL );
    lv_obj_set_size(stepcounter_cont, hres , 40);
    lv_obj_add_style( stepcounter_cont, LV_OBJ_PART_MAIN, style );
    lv_obj_align( stepcounter_cont, move_settings_tile1, LV_ALIGN_IN_TOP_RIGHT, 0, 75 );
    stepcounter_onoff = lv_switch_create( stepcounter_cont, NULL );
    lv_switch_off( stepcounter_onoff, LV_ANIM_ON );
    lv_obj_align( stepcounter_onoff, stepcounter_cont, LV_ALIGN_IN_RIGHT_MID, -5, 0 );
    lv_obj_set_event_cb( stepcounter_onoff, stepcounter_onoff_event_handler );
    lv_obj_t *stepcounter_label = lv_label_create( stepcounter_cont, NULL);
    lv_obj_add_style( stepcounter_label, LV_OBJ_PART_MAIN, style );
    lv_label_set_text( stepcounter_label, "step counter");
    lv_obj_align( stepcounter_label, stepcounter_cont, LV_ALIGN_IN_LEFT_MID, 5, 0 );

    lv_obj_t *doubleclick_cont = lv_obj_create( move_settings_tile1, NULL );
    lv_obj_set_size(doubleclick_cont, hres , 40);
    lv_obj_add_style( doubleclick_cont, LV_OBJ_PART_MAIN, style );
    lv_obj_align( doubleclick_cont, stepcounter_cont, LV_ALIGN_OUT_BOTTOM_MID, 0, 0 );
    doubleclick_onoff = lv_switch_create( doubleclick_cont, NULL );
    lv_switch_off( doubleclick_onoff, LV_ANIM_ON );
    lv_obj_align( doubleclick_onoff, doubleclick_cont, LV_ALIGN_IN_RIGHT_MID, -5, 0 );
    lv_obj_set_event_cb( doubleclick_onoff, doubleclick_onoff_event_handler );
    lv_obj_t *doubleclick_label = lv_label_create( doubleclick_cont, NULL);
    lv_obj_add_style( doubleclick_label, LV_OBJ_PART_MAIN, style );
    lv_label_set_text( doubleclick_label, "double click");
    lv_obj_align( doubleclick_label, doubleclick_cont, LV_ALIGN_IN_LEFT_MID, 5, 0 );

    if ( bma_get_config( BMA_DOUBLECLICK ) )
        lv_switch_on( doubleclick_onoff, LV_ANIM_OFF );
    else
        lv_switch_off( doubleclick_onoff, LV_ANIM_OFF );

    if ( bma_get_config( BMA_STEPCOUNTER ) )
        lv_switch_on( stepcounter_onoff, LV_ANIM_OFF );
    else
        lv_switch_off( stepcounter_onoff, LV_ANIM_OFF );
}


static void exit_move_setup_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       mainbar_jump_to_tilenumber( SETUP_TILE, LV_ANIM_OFF );
                                        break;
    }
}

static void stepcounter_onoff_event_handler(lv_obj_t * obj, lv_event_t event) {
    if(event == LV_EVENT_VALUE_CHANGED) {
        if( lv_switch_get_state( obj ) ) {
            bma_set_config( BMA_STEPCOUNTER, true );
        }
        else {
            bma_set_config( BMA_STEPCOUNTER, false );
        }
    }
}

static void doubleclick_onoff_event_handler(lv_obj_t * obj, lv_event_t event) {
    if(event == LV_EVENT_VALUE_CHANGED) {
        if( lv_switch_get_state( obj ) ) {
            bma_set_config( BMA_DOUBLECLICK, true );
        }
        else {
            bma_set_config( BMA_DOUBLECLICK, false );
        }
    }
}