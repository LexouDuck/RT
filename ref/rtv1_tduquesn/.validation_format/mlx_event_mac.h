/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event_mac.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:19:28 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/05 07:52:43 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_EVENT_MAC_H
# define MLX_EVENT_MAC_H

# define L_CLICK		0x1
# define R_CLICK		0x2
# define SCROLL_UP		0x4
# define SCROLL_DOWN	0x5

# define KEY_ESC		0x35
# define KEY_SPACE		0x31
# define KEY_LCTRL		0x100
# define KEY_RCTRL		0x10D

# define KEY_LEFT		0x7B
# define KEY_RIGHT		0x7C
# define KEY_DOWN		0x7D
# define KEY_UP			0x7E
# define KEY_PAGE_UP	0x74
# define KEY_PAGE_DN	0x79

# define KEY_HOME		0x73
# define KEY_END		0x77
# define KEY_HELP		0x72
# define KEY_DELETE		0x75

# define KEY_S			0x01
# define KEY_D			0x02
# define KEY_I			0x22
# define KEY_P			0x23
# define KEY_L			0x25
# define KEY_J			0x26
# define KEY_K			0x28

# define KEY_NUMPAD_0			0x52
# define KEY_NUMPAD_1			0x53
# define KEY_NUMPAD_2			0x54
# define KEY_NUMPAD_3			0x55
# define KEY_NUMPAD_4			0x56
# define KEY_NUMPAD_5			0x57
# define KEY_NUMPAD_6			0x58
# define KEY_NUMPAD_7			0x59
# define KEY_NUMPAD_8			0x5B
# define KEY_NUMPAD_9			0x5C
# define KEY_NUMPAD_PERIOD		0x41
# define KEY_NUMPAD_ENTER		0x4C
# define KEY_NUMPAD_ADD			0x45
# define KEY_NUMPAD_SUB			0x4E
# define KEY_NUMPAD_MUL			0x43
# define KEY_NUMPAD_DIV			0x4B
# define KEY_NUMPAD_CLEAR		0x47
# define KEY_NUMPAD_EQUALS		0x51

/*
** https://tronche.com/gui/x/xlib/events/processing-overview.html
**
**	=== EVENT DEFINES ===
*/
# define EVENT_KEYPRESS				2
# define EVENT_KEYRELEASE			3
# define EVENT_BUTTONPRESS			4
# define EVENT_BUTTONRELEASE		5
# define EVENT_MOTIONNOTIFY			6
# define EVENT_ENTERNOTIFY			7
# define EVENT_LEAVENOTIFY			8
# define EVENT_FOCUSIN				9
# define EVENT_FOCUSOUT				10
# define EVENT_KEYMAPNOTIFY			11
# define EVENT_EXPOSE				12
# define EVENT_GRAPHICSEXPOSE		13
# define EVENT_NOEXPOSE				14
# define EVENT_VISIBILITYNOTIFY		15
# define EVENT_CREATENOTIFY			16
# define EVENT_DESTROYNOTIFY		17
# define EVENT_UNMAPNOTIFY			18
# define EVENT_MAPNOTIFY			19
# define EVENT_MAPREQUEST			20
# define EVENT_REPARENTNOTIFY		21
# define EVENT_CONFIGURENOTIFY		22
# define EVENT_CONFIGUREREQUEST		23
# define EVENT_GRAVITYNOTIFY		24
# define EVENT_RESIZEREQUEST		25
# define EVENT_CIRCULATENOTIFY		26
# define EVENT_CIRCULATEREQUEST		27
# define EVENT_PROPERTYNOTIFY		28
# define EVENT_SELECTIONCLEAR		29
# define EVENT_SELECTIONREQUEST		30
# define EVENT_SELECTIONNOTIFY		31
# define EVENT_COLORMAPNOTIFY		32
# define EVENT_CLIENTMESSAGE		33
# define EVENT_MAPPINGNOTIFY		34
# define EVENT_GENERICEVENT			35
# define EVENT_LASTEVENT			36

/*
**	=== EVENT MASK DEFINES ===
**	These are the different X event bit-masks for the X-Server.
**	These are not to be confused with event names.
*/

/*
** NoEventMask				"No events" wanted (activate when no other
**								events happened)
** KeyPressMask				Keyboard down events wanted
** KeyReleaseMask			Keyboard up events wanted
** ButtonPressMask			Pointer button down events wanted
** ButtonReleaseMask		Pointer button up events wanted
** EnterWindowMask			Pointer window entry events wanted
** LeaveWindowMask			Pointer window leave events wanted
** PointerMotionMask		Pointer motion events wanted
** PointerMotionHintMask	Pointer motion hints wanted
** Button1MotionMask		Pointer motion while button 1 down
** Button2MotionMask		Pointer motion while button 2 down
** Button3MotionMask		Pointer motion while button 3 down
** Button4MotionMask		Pointer motion while button 4 down
** Button5MotionMask		Pointer motion while button 5 down
** ButtonMotionMask			Pointer motion while any button down
** KeymapStateMask			Keyboard state wanted at window entry and focus in
** ExposureMask				Any exposure wanted
** VisibilityChangeMask		Any change in visibility wanted
** StructureNotifyMask		Any change in window structure wanted
** ResizeRedirectMask		Redirect resize of this window
** SubstructureNotifyMask	Substructure notification wanted
** SubstructureRedirectMask	Redirect structure requests on children
** FocusChangeMask			Any change in input focus wanted
** PropertyChangeMask		Any change in property wanted
** ColormapChangeMask		Any change in colormap wanted
** OwnerGrabButtonMask		Automatic grabs should activate with
**								owner_events set to True
*/
# define MASK_NOEVENT				0x0L
# define MASK_KEYPRESS				0x1L
# define MASK_KEYRELEASE			0x2L
# define MASK_BUTTONPRESS			0x4L
# define MASK_BUTTONRELEASE			0x8L
# define MASK_ENTERWINDOW			0x10L
# define MASK_LEAVEWINDOW			0x20L
# define MASK_POINTERMOTION			0x40L
# define MASK_POINTERMOTIONHINT		0x80L
# define MASK_BUTTON1MOTION			0x100L
# define MASK_BUTTON2MOTION			0x200L
# define MASK_BUTTON3MOTION			0x400L
# define MASK_BUTTON4MOTION			0x800L
# define MASK_BUTTON5MOTION			0x1000L
# define MASK_BUTTONMOTION			0x2000L
# define MASK_KEYMAPSTATE			0x4000L
# define MASK_EXPOSURE				0x8000L
# define MASK_VISIBILITYCHANGE		0x10000L
# define MASK_STRUCTURENOTIFY		0x20000L
# define MASK_RESIZEREDIRECT		0x40000L
# define MASK_SUBSTRUCTURENOTIFY	0x80000L
# define MASK_SUBSTRUCTUREREDIRECT	0x100000L
# define MASK_FOCUSCHANGE			0x200000L
# define MASK_PROPERTYCHANGE		0x400000L
# define MASK_COLORMAPCHANGE		0x800000L
# define MASK_OWNERGRABBUTTON		0x1000000L

#endif
