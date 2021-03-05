/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 36;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int rmaster            = 1;        /* 1 means master-area is initially on the right */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int vertpad            = 15;       /* vertical padding of bar */
static const int sidepad            = 15;       /* horizontal padding of bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const char font[]            = "JetBrains Mono NL 11";
static const char dmenufont[]       = "JetBrains Mono-11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#555555";
static const char col_gray3[]       = "#d7d7d7";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#61a0ff";
static const unsigned int baralpha = 150;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#444444", col_gray3, col_gray2  },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title            tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Chromium", NULL,       "Google Docs",   0,         1,          0,           0,        -1 },
	{ "discord",  NULL,       NULL,            1 << 2,    0,          0,           0,        -1 },
	{ "TelegramDesktop",NULL, NULL,            1 << 2,    0,          0,           0,        -1 },
	{ "jetbrains-idea", NULL, "win0",	   0,         1,          0,           0,        -1 }, 
	{ "st-256color", NULL,    NULL,            0,         0,          1,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray4, "-nf", col_gray1, "-sb", col_cyan, "-sf", col_gray4, "-c", "-bw", "4", "-l", "10", "-hp", "google-chrome-stable,discord,nvidia-settings,spotify,telegram-desktop,intellij-idea-ultimate-edition", NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_r,      togglermaster,  {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,		XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,		XK_k,      pushup,         {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY, 			XK_comma,  spawn, 	   SHCMD("amixer set Master 5%- && pkill -RTMIN+2 goblocks") },
        { MODKEY, 			XK_period, spawn,  	   SHCMD("amixer set Master 5%+ && pkill -RTMIN+2 goblocks") },
        { MODKEY, 			XK_m, 	   spawn, 	   SHCMD("amixer set Master toggle && pkill -RTMIN+2 goblocks") },
	{ ALTKEY, 			XK_comma,  spawn, 	   SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous") },
        { ALTKEY, 			XK_period, spawn,  	   SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next") },
        { ALTKEY, 			XK_m, 	   spawn, 	   SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause") },
        { 0, XF86XK_AudioLowerVolume,   	   spawn, 	   SHCMD("amixer set Master 5%- && pkill -RTMIN+2 goblocks" ) },
        { 0, XF86XK_AudioRaiseVolume,   	   spawn, 	   SHCMD("amixer set Master 5%+ && pkill -RTMIN+2 goblocks") }, 
        { 0, XF86XK_AudioMute, 			   spawn,          SHCMD("amixer set Master toggle && pkill -RTMIN+2 goblocks" ) },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("~/.config/scripts/dmenuExit") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("~/.config/scripts/screenshot") },
	{ MODKEY,	                XK_s,      spawn,          SHCMD("~/.config/scripts/screenshot2") },
	{ MODKEY,	                XK_e,      spawn,          SHCMD("st -e lf") },
};

#include "shiftview.c"

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} }, 
	{ ClkStatusText,        0,              Button5,        spawn,          SHCMD("amixer set Master 5%- && pkill -RTMIN+2 goblocks") },
	{ ClkStatusText,        0,              Button4,        spawn,          SHCMD("amixer set Master 5%+ && pkill -RTMIN+2 goblocks") },
	{ ClkStatusText,        0,              Button1,        spawn,          SHCMD("if (pgrep spotify); then : ; else spotify; fi") },
	{ ClkStatusText,        0,              Button3,        spawn,          SHCMD("amixer set Master toggle && pkill -RTMIN+2 goblocks") },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkWinTitle,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkWinTitle,		0,		Button5,	shiftview,	{.i = 1} },
};

