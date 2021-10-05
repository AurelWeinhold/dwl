/* appearance */
static const int sloppyfocus        = 0;  /* focus follows mouse */
static const unsigned int borderpx  = 2;  /* border pixel of windows */
static const unsigned int gappih    = 4;  /* horiz inner gap between windows */
static const unsigned int gappiv    = 4;  /* vert inner gap between windows */
static const unsigned int gappoh    = 4;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 4;  /* vert outer gap between windows and screen edge */
static const float rootcolor[]      = {0.81, 0.574, 0.125, 1.0};
static const float bordercolor[]    = {0.0, 0.0, 0.0, 0.0};
static const float focuscolor[]     = {0.77, 0.136, 0.11, 1.0};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   monitor */
	/* examples:
	{ "Gimp",     NULL,       0,            1,           -1 },
	{ "firefox",  NULL,       1 << 8,       0,           -1 },
	*/
	{ "Rofi",     "rofi",     0,            1,            -1 },
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
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0 },
	*/
	/* defaults */
	{ NULL,       0.5,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0 },
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
static const int natural_scrolling = 0;

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
static const char *roficmd[]  = { "rofi", "-show", "drun", "-config", XDG_CONFIG_PATH("rofi/starter.rasi"), NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ MODKEY,                    XKB_KEY_d,          spawn,          {.v = roficmd} },
	{ MODKEY,                    XKB_KEY_Return,     spawn,          {.v = termcmd} },
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_m,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_n,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	{ MODKEY,                    XKB_KEY_q,          killclient,     {0} },
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY, 					 XKB_KEY_f,    		 togglefullscreen, {0} },
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
