/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 12;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const char *fonts[]          = { "JetBrainsMono NFM SemiBold:size=12" };
static const char dmenufont[]       = "JetBrainsMono NFM SemiBold:size=12";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

#if __has_include("colors-wal-dwm.h")
#include "colors-wal-dwm.h"
#else
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
#endif

static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
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
	/* class      instance    title       tags mask     isfloating   isterminal     noswallow   monitor */
	{ "st-256color",NULL,     NULL,       0,            0,           1,             0,          -1 },
	{ "Tor Browser",NULL,     NULL,       0,            1,           0,             0,          -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           0,             0,          -1 },
	{ "qv4l2",    NULL,       NULL,       0,            1,           0,             0,          -1 },
	{ "qjackctl", NULL,       NULL,       0,            1,           0,             0,          -1 },
	{ "QjackCtl", NULL,       NULL,       0,            1,           0,             0,          -1 },
	{ "arandr",   NULL,       NULL,       0,            1,           0,             0,          -1 },
	{ "Arandr",   NULL,       NULL,       0,            1,           0,             0,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

static const int dmenudesktop = 1; /* 1 means dmenu will use only desktop files from [/usr/share/applications/] */

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-i", NULL };
static const char *termcmd[]  = { "setsid", "-f", "st", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {1} },
    { MODKEY,                       XK_o,      spawn,          SHCMD("setsid -f firefox") },
    { MODKEY,                       XK_F10,    spawn,          SHCMD("mounter.sh") },
    { MODKEY,                       XK_F11,    spawn,          SHCMD("unmounter.sh") },
    { MODKEY,                       XK_q,      spawn,          SHCMD("shutdown.sh") },
	{ MODKEY,                       XK_b,      spawn,          SHCMD("passmenu") },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("passmenu-otp") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("emoji.sh") },
	{ MODKEY,                       XK_Insert, spawn,          SHCMD("bookmark.sh") },
	{ MODKEY|ShiftMask,             XK_Insert, spawn,          SHCMD("bookmark.sh -c") },
    { MODKEY,                       XK_Print,  spawn,          SHCMD("screenshot.sh") },
    { MODKEY|ShiftMask,             XK_Print,  spawn,          SHCMD("screenshot.sh -c ") },
    { MODKEY|ShiftMask|ControlMask, XK_Print,  spawn,          SHCMD("record-screen.sh") },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,   SHCMD("brightness.sh +") },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,   SHCMD("brightness.sh -") },
    { 0,                            XF86XK_AudioPlay,  spawn,          SHCMD("playerctl play-pause") },
	{ 0,                            XF86XK_AudioNext,  spawn,          SHCMD("playerctl next") },
	{ 0,                            XF86XK_AudioPrev,  spawn,          SHCMD("playerctl previous") },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,   SHCMD("volume.sh +") },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,   SHCMD("volume.sh -") },
	{ 0,                            XF86XK_AudioMute,  spawn,          SHCMD("volume.sh m") },
	{ 0,                            XF86XK_AudioMicMute,  spawn,       SHCMD("toggle_mic.sh") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigstatusbar,   {.i = 6} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

