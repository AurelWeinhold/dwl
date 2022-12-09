/* appearance */
static const int sloppyfocus        = 0;  /* focus follows mouse */
static const int lockfullscreen     = 1;  /* 1 will force focus on the fullscreen window */
static const unsigned int borderpx  = 2;  /* border pixel of windows */
static const unsigned int gappih    = 4;  /* horiz inner gap between windows */
static const unsigned int gappiv    = 4;  /* vert inner gap between windows */
static const unsigned int gappoh    = 4;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 4;  /* vert outer gap between windows and screen edge */
static const float rootcolor[]      = {0.8431, 0.6000, 0.1294, 1.0};
static const float bordercolor[]    = {0.1137, 0.1255, 0.1294, 1.0};
static const float focuscolor[]     = {0.8000, 0.1412, 0.1137, 1.0};
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]  = {0.1, 0.1, 0.1, 1.0};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

// base definitions
#define DESKTOP_DIM_X 1920
#define DESKTOP_DIM_Y 1080
#define BAR_HEIGHT 33
#define RIGHTBOUND_X_SIZE 1008

// sizes
#define WINDOW_HEIGHT DESKTOP_DIM_Y - (BAR_HEIGHT + 3 * gappoh)
#define RIGHTBOUND_X_OFFSET DESKTOP_DIM_X - (RIGHTBOUND_X_SIZE + 2 * gappov)

// Floating window "layouts": x,y,w,h
#define LEFTBOUND_FLOAT gappov, gappoh, DESKTOP_DIM_X/2, WINDOW_HEIGHT
#define RIGHTBOUND_FLOAT RIGHTBOUND_X_OFFSET, gappoh, RIGHTBOUND_X_SIZE, WINDOW_HEIGHT
#define NO_FLOAT_RULE 0,0,0,0
/*
 * x, y, width, heigh are floating only
 * When x or y == 0 the client is placed at the center of the screen,
 * when width or height == 0 the default size of the client is used
 */
static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   monitor scratchkey float x,y,width,height */
	{ "Rofi",     "rofi",     0,            1,           -1,      0 ,       0,0,0,0 },
	{ NULL,     "scratchpad", 0,            1,           -1,     's',       200,100,0,0   },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors
 * The order in which monitors are defined determines their position.
 * Non-configured monitors are always added to the left. */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect x y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL},
	*/
	{ NULL,       0.5,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL},
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.layout = "de",
	.options = "caps:swapescape",
};

static const int repeat_rate = 50;
static const int repeat_delay = 300;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* Autostart */
static const char *const autostart[] = {
	"sh", "-c", "swaybg -c '#d79921'", NULL,
	"dunst", NULL,
	"nextcloud", "--background", NULL,
	"sh", "-c", "waybar > $HOME/.cache/waybar 2> $HOME/.cache/waybar_err", NULL,
	NULL /* terminate */
};

#define MODKEY WLR_MODIFIER_LOGO
#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
#define XDG_CONFIG_PATH(relpath) "/home/aurel/.config/"relpath

static const char *termcmd[] = { "alacritty", NULL };
static const char *menucmd[] = { "bemenu-run", NULL };
static const char *roficmd[]  = { "wofi", "--show", "drun", NULL };

// Volume control
static const char *volupcmd[]         = { "pamixer", "--increase","5", NULL };
static const char *voldowncmd[]       = { "pamixer", "--decrease","5", NULL };
static const char *voltogglemutecmd[] = { "pamixer", "--toggle-mute", NULL };

// Player control
static const char *playpausecmd[] = { "playerctl", "play-pause", NULL };
static const char *playnextcmd[]  = { "playerctl", "next", NULL };
static const char *playprevcmd[]  = { "playerctl", "previous", NULL };

// Backlight control
static const char *backlightupcmd[]   = { "brightnessctl", "set", "10%+", NULL };
static const char *backlightdowncmd[] = { "brightnessctl", "set", "10%-", NULL };

/* named scratchpads - First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = { "s", "alacritty", "-t", "scratchpad", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */

	/* spawn */
	{ MODKEY,                    XKB_KEY_d,          spawn,          {.v = roficmd} },
	{ MODKEY,                    XKB_KEY_Return,     spawn,          {.v = termcmd} },

	/* scratchpads */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_X,      togglescratch,  {.v = scratchpadcmd } },

	/* wm */
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_m,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_n,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	{ MODKEY,                    XKB_KEY_q,          killclient,     {0} },

	/* layout */
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY, 					 XKB_KEY_f,    		 togglefullscreen, {0} },

	/* tags and monitors */
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_semicolon,  tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_colon,      tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_quotedbl,                   1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_section,                    2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_ampersand,                  5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_slash,                      6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_parenleft,                  7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenright,                 8),
	TAGKEYS(          XKB_KEY_0, XKB_KEY_equal,                      9),
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_E,          quit,           {0} },

	/* multimedia control keys */
	{ 0,                       XKB_KEY_XF86AudioRaiseVolume,  spawn,  {.v = volupcmd } },
	{ 0,                       XKB_KEY_XF86AudioLowerVolume,  spawn,  {.v = voldowncmd } },
	{ 0,                       XKB_KEY_XF86AudioMute,         spawn,  {.v = voltogglemutecmd } },

	{ 0,                       XKB_KEY_XF86AudioPlay,         spawn, {.v = playpausecmd } },
	{ 0,                       XKB_KEY_XF86AudioNext,         spawn, {.v = playnextcmd } },
	{ 0,                       XKB_KEY_XF86AudioPrev,         spawn, {.v = playprevcmd } },

	{ 0,                       XKB_KEY_XF86MonBrightnessUp,   spawn,  {.v = backlightupcmd } },
	{ 0,                       XKB_KEY_XF86MonBrightnessDown, spawn,  {.v = backlightdowncmd } },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
