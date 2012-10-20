; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCountDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "bj.h"

ClassCount=14
Class1=CBjApp
Class2=CBjDlg
Class3=CAboutDlg

ResourceCount=20
Resource1=IDR_ACCELERATOR1
Resource2=IDR_MAINFRAME
Resource3=IDR_MENU_PRACTICE
Resource4=IDD_ABOUTBOX
Resource5=IDD_BJ_DIALOG
Class4=CDlgCasinoRules
Resource6=IDR_MENU_DLG
Resource7=IDD_DIALOG_STANDARD_STRATEGY
Resource8=IDD_DIALOG_CASINO_SETTINGS
Resource9=IDD_DIALOG_PRACTICE
Resource10=IDD_DIALOG_CASINO_RULES (English (U.S.))
Resource11=IDD_ABOUTBOX (English (U.S.))
Class5=CDialogMistakes
Resource12=IDD_DIALOG_COUNT
Class6=CDlgPractice
Resource13=IDD_BJ_DIALOG (English (U.S.))
Class7=CBetMissThread
Resource14=IDD_DIALOG_PLAY_SETTINGS
Class8=CSettings
Resource15=IDD_DIALOG_BID_SETTINGS
Resource16=IDR_MENU_DLG (English (U.S.))
Class9=CPropPlay
Class10=CPropBid
Resource17=IDD_DIALOG_MISTAKES
Class11=CPropCasino
Resource18=IDR_MENU_MISTAKES
Class12=CPropStrategy
Class13=CBJSettings
Resource19=IDD_SETTINGS_DIALOG
Class14=CCountDlg
Resource20=IDR_ACCELERATOR1 (English (U.S.))

[CLS:CBjApp]
Type=0
HeaderFile=bj.h
ImplementationFile=bj.cpp
Filter=N

[CLS:CBjDlg]
Type=0
HeaderFile=bjDlg.h
ImplementationFile=bjDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_MENUITEM_MISTAKES_VIEW_SESSION

[CLS:CAboutDlg]
Type=0
HeaderFile=bjDlg.h
ImplementationFile=bjDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BJ_DIALOG]
Type=1
Class=CBjDlg
ControlCount=81
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT22,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_LIST_REMAINING,SysListView32,1350631425
Control6=IDC_EDIT_WAGER,edit,1350631552
Control7=IDC_EDIT_TOTAL,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CHECK_AUTOPLAY,button,1342242819
Control11=IDC_EDIT_DEALERW,edit,1350631552
Control12=IDC_EDIT_MEW,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_DEALER_CARDS,edit,1350631552
Control16=IDC_EDIT_ME_CARDS,edit,1350631552
Control17=IDC_BUTTON_NEW_HAND,button,1342242816
Control18=IDC_BUTTON_RESHUFFLE,button,1342242816
Control19=IDC_RADIO_DEALER2,button,1342308361
Control20=IDC_RADIO_ME2,button,1342177289
Control21=IDC_EDIT_DDADVANTAGE,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT_SPLITADVANTAGE,edit,1350631552
Control24=IDC_STATIC,static,1342308352
Control25=IDC_EDIT_COMMAND,edit,1350631552
Control26=IDC_STATIC,static,1342308352
Control27=IDC_EDIT_BJ_ADVANTAGE,edit,1350631552
Control28=IDC_STATIC,static,1342308352
Control29=IDC_EDIT_HANDS_PLAYED,edit,1350631552
Control30=IDC_STATIC,static,1342308352
Control31=IDC_LIST_DECISION,SysListView32,1350631425
Control32=IDC_STATIC,static,1342308352
Control33=IDC_RADIO_HIT,button,1342308361
Control34=IDC_RADIO_DOUBLE,button,1342177289
Control35=IDC_RADIO_SPLIT,button,1342177289
Control36=IDC_RADIO_ACE,button,1342177289
Control37=IDC_STATIC,button,1342177287
Control38=IDC_STATIC,button,1342177287
Control39=IDC_EDIT_WON,edit,1350631552
Control40=IDC_EDIT_LOST,edit,1350631552
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,button,1342177287
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352
Control46=IDC_EDIT_WHIT,edit,1350631552
Control47=IDC_EDIT_WOHIT,edit,1350631552
Control48=IDC_SPIN_WAGER,msctls_updown32,1342177318
Control49=IDC_BUTTON_D1,button,1342242816
Control50=IDC_STATIC,button,1342177287
Control51=IDC_BUTTON_D2,button,1342242816
Control52=IDC_BUTTON_D3,button,1342242816
Control53=IDC_BUTTON_D4,button,1342242816
Control54=IDC_BUTTON_D5,button,1342242816
Control55=IDC_BUTTON_D6,button,1342242816
Control56=IDC_BUTTON_D7,button,1342242816
Control57=IDC_BUTTON_D8,button,1342242816
Control58=IDC_BUTTON_D9,button,1342242816
Control59=IDC_BUTTON_D10,button,1342242816
Control60=IDC_BUTTON_M1,button,1342242816
Control61=IDC_STATIC,button,1342177287
Control62=IDC_BUTTON_M2,button,1342242816
Control63=IDC_BUTTON_M3,button,1342242816
Control64=IDC_BUTTON_M4,button,1342242816
Control65=IDC_BUTTON_M5,button,1342242816
Control66=IDC_BUTTON_M6,button,1342242816
Control67=IDC_BUTTON_M7,button,1342242816
Control68=IDC_BUTTON_M8,button,1342242816
Control69=IDC_BUTTON_M9,button,1342242816
Control70=IDC_BUTTON_M10,button,1342242816
Control71=IDC_BUTTON_O1,button,1342242816
Control72=IDC_STATIC,button,1342177287
Control73=IDC_BUTTON_O2,button,1342242816
Control74=IDC_BUTTON_O3,button,1342242816
Control75=IDC_BUTTON_O4,button,1342242816
Control76=IDC_BUTTON_O5,button,1342242816
Control77=IDC_BUTTON_O6,button,1342242816
Control78=IDC_BUTTON_O7,button,1342242816
Control79=IDC_BUTTON_O8,button,1342242816
Control80=IDC_BUTTON_O9,button,1342242816
Control81=IDC_BUTTON_O10,button,1342242816

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=ID_10
Command2=ID_1
Command3=ID_2
Command4=ID_3
Command5=ID_4
Command6=ID_5
Command7=ID_6
Command8=ID_7
Command9=ID_8
Command10=ID_9
Command11=ID_CALCULATE
Command12=ID_DEALERFOCUS
Command13=ID_LOST
Command14=ID_MEFOCUS
Command15=ID_HANDOVER
Command16=ID_NOBODY
Command17=ID_WON
CommandCount=17

[MNU:IDR_MENU_DLG]
Type=1
Class=CBjDlg
Command1=ID_HAND_DEALER
Command2=ID_HAND_ME
Command3=ID_HAND_OTHER
Command4=ID_SETTINGS_CASINORULES
CommandCount=4

[CLS:CDlgCasinoRules]
Type=0
HeaderFile=DlgCasinoRules.h
ImplementationFile=DlgCasinoRules.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgCasinoRules

[MNU:IDR_MENU_DLG (English (U.S.))]
Type=1
Class=CBjDlg
Command1=ID_MENUITEM_VIEW_SETTINGS
Command2=ID_MENUITEM_VIEW_MISTAKES
Command3=ID_MENUITEM_VIEW_PRACTICE
Command4=ID_MENU_HELP_ABOUT
CommandCount=4

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC1,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC2,static,1342308352

[DLG:IDD_BJ_DIALOG (English (U.S.))]
Type=1
Class=CBjDlg
ControlCount=81
Control1=IDC_EDIT22,edit,1082196096
Control2=IDC_STATIC,static,1073872896
Control3=IDC_LIST_REMAINING,SysListView32,1350631425
Control4=IDC_EDIT_WAGER,edit,1082196096
Control5=IDC_EDIT_TOTAL,edit,1082196096
Control6=IDC_STATIC,static,1073872896
Control7=IDC_STATIC,static,1073872896
Control8=IDC_CHECK_AUTOPLAY,button,1073807363
Control9=IDC_EDIT_DEALERW,edit,1350631552
Control10=IDC_EDIT_MEW,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_DEALER_CARDS,edit,1350631552
Control14=IDC_EDIT_ME_CARDS,edit,1350631552
Control15=IDC_BUTTON_NEW_HAND,button,1073807360
Control16=IDC_BUTTON_RESHUFFLE,button,1073807360
Control17=IDC_RADIO_DEALER2,button,1476526089
Control18=IDC_RADIO_ME2,button,1476395017
Control19=IDC_EDIT_DDADVANTAGE,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT_SPLITADVANTAGE,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT_COMMAND,edit,1350631552
Control24=IDC_STATIC,static,1342308352
Control25=IDC_EDIT_BJ_ADVANTAGE,edit,1350631552
Control26=IDC_STATIC,static,1342308352
Control27=IDC_EDIT_HANDS_PLAYED,edit,1350631552
Control28=IDC_STATIC,static,1342308352
Control29=IDC_LIST_DECISION,SysListView32,1350631425
Control30=IDC_STATIC,static,1342308352
Control31=IDC_RADIO_HIT,button,1342308361
Control32=IDC_RADIO_DOUBLE,button,1342177289
Control33=IDC_RADIO_SPLIT,button,1342177289
Control34=IDC_RADIO_ACE,button,1342177289
Control35=IDC_STATIC,button,1342177287
Control36=IDC_STATIC,button,1342177287
Control37=IDC_EDIT_WON,edit,1350631552
Control38=IDC_EDIT_LOST,edit,1350631552
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,button,1342177287
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_EDIT_WHIT,edit,1350631552
Control45=IDC_EDIT_WOHIT,edit,1350631552
Control46=IDC_SPIN_WAGER,msctls_updown32,1073741862
Control47=IDC_BUTTON_D1,button,1073807360
Control48=IDC_STATICPRO2,button,1073741831
Control49=IDC_BUTTON_D2,button,1073807360
Control50=IDC_BUTTON_D3,button,1073807360
Control51=IDC_BUTTON_D4,button,1073807360
Control52=IDC_BUTTON_D5,button,1073807360
Control53=IDC_BUTTON_D6,button,1073807360
Control54=IDC_BUTTON_D7,button,1073807360
Control55=IDC_BUTTON_D8,button,1073807360
Control56=IDC_BUTTON_D9,button,1073807360
Control57=IDC_BUTTON_D10,button,1073807360
Control58=IDC_BUTTON_M1,button,1073807360
Control59=IDC_STATICPRO,button,1073741831
Control60=IDC_BUTTON_M2,button,1073807360
Control61=IDC_BUTTON_M3,button,1073807360
Control62=IDC_BUTTON_M4,button,1073807360
Control63=IDC_BUTTON_M5,button,1073807360
Control64=IDC_BUTTON_M6,button,1073807360
Control65=IDC_BUTTON_M7,button,1073807360
Control66=IDC_BUTTON_M8,button,1073807360
Control67=IDC_BUTTON_M9,button,1073807360
Control68=IDC_BUTTON_M10,button,1073807360
Control69=IDC_BUTTON_O1,button,1073807360
Control70=IDC_STATICPRO3,button,1073741831
Control71=IDC_BUTTON_O2,button,1073807360
Control72=IDC_BUTTON_O3,button,1073807360
Control73=IDC_BUTTON_O4,button,1073807360
Control74=IDC_BUTTON_O5,button,1073807360
Control75=IDC_BUTTON_O6,button,1073807360
Control76=IDC_BUTTON_O7,button,1073807360
Control77=IDC_BUTTON_O8,button,1073807360
Control78=IDC_BUTTON_O9,button,1073807360
Control79=IDC_BUTTON_O10,button,1073807360
Control80=IDC_STATIC,static,1342308352
Control81=IDC_CHECK_ALLMANUAL,button,1073807363

[ACL:IDR_ACCELERATOR1 (English (U.S.))]
Type=1
Class=?
Command1=ID_10
Command2=ID_1
Command3=ID_2
Command4=ID_3
Command5=ID_4
Command6=ID_5
Command7=ID_6
Command8=ID_7
Command9=ID_8
Command10=ID_9
Command11=ID_CALCULATE
Command12=ID_DEALERFOCUS
Command13=ID_LOST
Command14=ID_MEFOCUS
Command15=ID_HANDOVER
Command16=ID_NOBODY
Command17=ID_WON
Command18=ID_MENU_SHOW_COUNT
CommandCount=18

[CLS:CDialogMistakes]
Type=0
HeaderFile=DialogMistakes.h
ImplementationFile=DialogMistakes.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDialogMistakes

[CLS:CDlgPractice]
Type=0
HeaderFile=DlgPractice.h
ImplementationFile=DlgPractice.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_MENU_VIEWMISTAKES
VirtualFilter=dWC

[MNU:IDR_MENU_PRACTICE]
Type=1
Class=CDlgPractice
Command1=ID_MENU_DECK_SETTINGS
Command2=ID_MENU_DECK_RESHUFFLE
Command3=ID_MENU_VIEWMISTAKES
Command4=ID_MENU_SHOW_COUNT
CommandCount=4

[CLS:CBetMissThread]
Type=0
HeaderFile=BetMissThread.h
ImplementationFile=BetMissThread.cpp
BaseClass=CWinThread
Filter=N

[DLG:IDD_SETTINGS_DIALOG]
Type=1
Class=CSettings
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CSettings]
Type=0
HeaderFile=Settings.h
ImplementationFile=Settings.cpp
BaseClass=CDialog
Filter=D
LastObject=CSettings

[DLG:IDD_DIALOG_BID_SETTINGS]
Type=1
Class=CPropBid
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_HIGH_BID,edit,1350631552
Control4=IDC_EDIT_LOW_BID,edit,1350631552

[DLG:IDD_DIALOG_PLAY_SETTINGS]
Type=1
Class=CPropPlay
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_PLAY_SPEED,edit,1350631552
Control4=IDC_EDIT_NUM_PLAYERS,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_PENETRATION,edit,1350631552

[CLS:CPropPlay]
Type=0
HeaderFile=PropPlay.h
ImplementationFile=PropPlay.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPropPlay
VirtualFilter=idWC

[CLS:CPropBid]
Type=0
HeaderFile=PropBid.h
ImplementationFile=PropBid.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPropBid
VirtualFilter=idWC

[DLG:IDD_DIALOG_CASINO_RULES (English (U.S.))]
Type=1
Class=CDlgCasinoRules
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK_HIT_SOFT17,button,1342242819
Control4=IDC_COMBO_DOUBLING,combobox,1344340226
Control5=IDC_COMBO_SPLITTING,combobox,1344340226
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_NUM_DECKS,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CHECK_DAS_ALLOWED,button,1342242819

[DLG:IDD_DIALOG_CASINO_SETTINGS]
Type=1
Class=CPropCasino
ControlCount=14
Control1=IDC_CHECK_HIT_SOFT17,button,1342242819
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_NUM_DECKS,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CHECK_DAS_ALLOWED,button,1342242819
Control7=IDC_CHECK_CAN_DOUBLE_ACES,button,1342242819
Control8=IDC_CHECK_CAN_DOUBLE_1011,button,1342242819
Control9=IDC_CHECK_CAN_DOUBLE_9,button,1342242819
Control10=IDC_CHECK_CAN_DOUBLE_ACES4,button,1342242819
Control11=IDC_CHECK_CAN_SPLIT_ACES,button,1342242819
Control12=IDC_EDIT_NUM_SPLITS,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[CLS:CPropCasino]
Type=0
HeaderFile=PropCasino.h
ImplementationFile=PropCasino.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPropCasino
VirtualFilter=idWC

[DLG:IDD_DIALOG_STANDARD_STRATEGY]
Type=1
Class=CPropStrategy
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO_STANDARD_STRATEGY,combobox,1344340226

[CLS:CPropStrategy]
Type=0
HeaderFile=PropStrategy.h
ImplementationFile=PropStrategy.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:CBJSettings]
Type=0
HeaderFile=BJSettings.h
ImplementationFile=BJSettings.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CBJSettings

[MNU:IDR_MENU_MISTAKES]
Type=1
Class=CDialogMistakes
Command1=ID_MENUITEM_MISTAKES_VIEW_SESSION
Command2=ID_MENUITEM_MISTAKES_VIEW_DAY
Command3=ID_MENUITEM_MISTAKES_VIEW_WEEK
Command4=ID_MENUITEM_MISTAKES_VIEW_MONTH
CommandCount=4

[DLG:IDD_DIALOG_PRACTICE]
Type=1
Class=CDlgPractice
ControlCount=9
Control1=IDC_BUTTON_STAND,button,1342242816
Control2=IDC_BUTTON_HIT,button,1342242816
Control3=IDC_BUTTON_DOUBLE,button,1342242816
Control4=IDC_BUTTON_SPLIT,button,1342242816
Control5=IDC_EDIT_WAGER,edit,1350631552
Control6=IDC_BUTTON_BET,button,1342242816
Control7=IDC_EDIT_MONEY,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_MISTAKES]
Type=1
Class=CDialogMistakes
ControlCount=32
Control1=IDC_LIST_MISTAKES,SysListView32,1350631425
Control2=IDC_EDIT_TOTAL_MISTAKES,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_BET_MISTAKES,edit,1350631552
Control7=IDC_EDIT_PLAY_MISTAKES,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_TOTAL_POSSIBLE,edit,1350631552
Control11=IDC_EDIT_TOTAL_ACTUAL,edit,1350631552
Control12=IDC_EDIT_TOTAL_MISTAKES2,edit,1350631552
Control13=IDC_EDIT_BET_MISTAKES2,edit,1350631552
Control14=IDC_EDIT_PLAY_MISTAKES2,edit,1350631552
Control15=IDC_EDIT_TOTAL_POSSIBLE2,edit,1350631552
Control16=IDC_EDIT_TOTAL_ACTUAL2,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_BUTTON_CHANGE_STRATEGY,button,1208033280
Control20=IDC_LIST_MISTAKES_STANDARD,SysListView32,1350631425
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EDIT_HANDS_PLAYED,edit,1484849280
Control25=IDC_EDIT_WIN_HAND,edit,1484849280
Control26=IDC_EDIT_AVG_STANDARD_COUNT,edit,1484849280
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EDIT_TIME_PLAYED,edit,1484849280
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_EDIT_ACTUAL_WIN,edit,1484849280
Control32=IDC_EDIT_THEORETICAL_WIN,edit,1484849280

[DLG:IDD_DIALOG_COUNT]
Type=1
Class=CCountDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_COUNT,edit,1350631552

[CLS:CCountDlg]
Type=0
HeaderFile=CountDlg.h
ImplementationFile=CountDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_COUNT
VirtualFilter=dWC
