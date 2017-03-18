#pragma once

#if !defined(EFLCPP_TIZEN) || (TIZEN_SDK_VERSION >= 240)

struct _Eo_Opaque;
typedef _Eo_Opaque Eo;
typedef Eo Evas_Object;
typedef Eo Evas;
typedef Eo Ecore_Timer;
typedef Eo Elm_Widget_Item;
typedef Eo Elm_Object_Item;

#else

struct _Evas_Object;
typedef struct _Evas_Object Evas_Object;

struct _Evas;
typedef struct _Evas Evas;

struct _Ecore_Timer;
typedef struct _Ecore_Timer Ecore_Timer;

struct _Elm_Object_Item;
typedef struct _Elm_Object_Item Elm_Object_Item;

struct _Elm_Widget_Item;
typedef struct _Elm_Widget_Item Elm_Widget_Item;

#endif

struct _Evas_Map;
typedef _Evas_Map Evas_Map;

struct _Ecore_IMF_Context;
typedef _Ecore_IMF_Context Ecore_IMF_Context;

struct _Elm_Gen_Item_Class;
typedef struct _Elm_Gen_Item_Class Elm_Gen_Item_Class;
typedef Elm_Gen_Item_Class Elm_Gengrid_Item_Class;

struct _Eina_List;
typedef struct _Eina_List Eina_List;

struct _Ecore_Evas;
typedef struct _Ecore_Evas Ecore_Evas;

typedef unsigned char Eina_Bool;
typedef int Evas_Coord;

typedef struct app_control_s* app_control_h;
