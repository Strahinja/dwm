/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "xos4 Terminus:size=10" };
//static const char *fonts[]          = { "Cozette Vector:size=9" };
//static const char *fonts[]          = { "PxPlus_IBM_VGA8 Nerd Font:size=12" };
static const char dmenufont[]       = "xos4 Terminus:size=10";
//static const char dmenufont[]       = "Cozette Vector:size=9";
//static const char dmenufont[]       = "PxPlus_IBM_VGA8 Nerd Font:size=12";
static const char col_gray1[]       = "#121212";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_white[]       = "#ffffff";
static const char col_black[]       = "#000000";
static const char col_green1[]      = "#344334";
static const char col_green2[]      = "#272927";
static const char col_cyan[]        = "#005577";
static const char col_accent[]      = "#bdcc49";
static const char *colors[][3]      = {
    /*                   fg         bg         border   */
    [SchemeNorm]     = { col_white, col_gray1, col_gray1 },
    [SchemeSel]      = { col_white, col_green1, col_green1  },
    [SchemeUrg]      = { col_black, col_accent, col_accent },
    [SchemeStatus]   = { col_white, col_gray1, "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
    [SchemeTagsSel]  = { col_white, col_green1, "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm] = { col_white, col_gray1, "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_white, col_green1, "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm] = { col_white, col_gray1, "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const char *const autostart[] = {
    "st", "-e", "tmux", "-u", NULL,
    "setxkbmap", "-layout", "us,rs", "-option", "grp:alt_shift_toggle", NULL,
    "picom", "--experimental-backends", NULL,
    "bash", "-c", "~/.fehbg", NULL,
    "slstatus", NULL,
    "twmnd", NULL,
    NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.75; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

#include "layouts.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "TTT",      bstack },
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    //{ "===",      bstackhoriz },
    { "HHH",      grid },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
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

/* commands */
static char dmenumon[2]              = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]        = { "dmenu_run", "-m", dmenumon,
                                         "-fn", dmenufont, "-nb", col_gray1,
                                         "-nf", col_white, "-sb", col_green1,
                                         "-sf", col_white, NULL };
static const char *termcmd[]         = { "st", "-e", "tmux", "-u", NULL };
static const char *sdmenucmd[]       = { "sdmenu", NULL };
static const char *pickcharcmd[]     = { "pickchar", NULL };
static const char *slockcmd[]        = { "slock", NULL };
static const char *surfcmd[]         = { "tsurf", NULL };
static const char *fmcmd[]           = { "st", "-e", "ranger", NULL };
static const char *mailcmd[]         = { "st", "-e", "neomutt", NULL };
static const char *ctrlhcmd[]        = { "xdotool", "keyup", "XF86Back", "key", "ctrl+h", NULL };
static const char *ctrllcmd[]        = { "xdotool", "keyup", "XF86Forward", "key", "ctrl+l", NULL };
static const char *helpcmd[]         = { "st", "-e", "sh", "-c", "markdown "
                                         "< /usr/local/share/dwm/shortcuts.md "
                                         "| w3m -T text/html", NULL };
static const char *scrotcmd[]        = { "screenshot", NULL };
static const char *mixervolupcmd[]   = { "amixer", "set", "Master", "10%+", NULL };
static const char *mixervoldowncmd[] = { "amixer", "set", "Master", "10%-", NULL };
static const char *mixermutecmd[]    = { "amixer", "set", "Master", "toggle", NULL };
static const char *calccmd[]         = { "st", "-e", "calc", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_F1,     spawn,          {.v = helpcmd } },
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_e,      spawn,          {.v = pickcharcmd } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_semicolon,      
                                               spawn,          {.v = slockcmd } },
    { MODKEY,                       XK_Print,  spawn,          {.v = scrotcmd } },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
    { MODKEY|ControlMask,           XK_u,      setlayout,      {.v = &layouts[5]} },
    { MODKEY|ControlMask,           XK_o,      setlayout,      {.v = &layouts[6]} },
    { MODKEY,                       XK_g,      spawn,          {.v = sdmenucmd } },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { 0,                            XF86XK_AudioLowerVolume,
                                               spawn,          {.v = mixervoldowncmd } },
    { 0,                            XF86XK_AudioRaiseVolume,
                                               spawn,          {.v = mixervolupcmd } },
    { 0,                            XF86XK_AudioMute,
                                               spawn,          {.v = mixermutecmd } },
    { MODKEY,                       XK_F11,    spawn,          {.v = mixervoldowncmd } },
    { MODKEY,                       XK_F12,    spawn,          {.v = mixervolupcmd } },
    { MODKEY,                       XK_F10,    spawn,          {.v = mixermutecmd } },
    { 0,                            XF86XK_Calculator,
                                               spawn,          {.v = calccmd } },
    { 0,                            XF86XK_HomePage,
                                               spawn,          {.v = surfcmd } },
    { 0,                            XF86XK_Explorer,
                                               spawn,          {.v = fmcmd } },
    { 0,                            XF86XK_Mail,
                                               spawn,          {.v = mailcmd } },
    { 0,                            XF86XK_Forward,
                                               spawn,          {.v = ctrllcmd } },
    { 0,                            XF86XK_Back,
                                               spawn,          {.v = ctrlhcmd } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

