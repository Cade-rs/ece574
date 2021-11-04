# File saved with Nlview 7.0r6  2020-01-29 bk=1.5227 VDI=41 GEI=36 GUI=JA:10.0 non-TLS-threadsafe
# 
# non-default properties - (restore without -noprops)
property attrcolor #000000
property attrfontsize 8
property autobundle 1
property backgroundcolor #ffffff
property boxcolor0 #000000
property boxcolor1 #000000
property boxcolor2 #000000
property boxinstcolor #000000
property boxpincolor #000000
property buscolor #008000
property closeenough 5
property createnetattrdsp 2048
property decorate 1
property elidetext 40
property fillcolor1 #ffffcc
property fillcolor2 #dfebf8
property fillcolor3 #f0f0f0
property gatecellname 2
property instattrmax 30
property instdrag 15
property instorder 1
property marksize 12
property maxfontsize 15
property maxzoom 6.25
property netcolor #19b400
property objecthighlight0 #ff00ff
property objecthighlight1 #ffff00
property objecthighlight2 #00ff00
property objecthighlight3 #0095ff
property objecthighlight4 #8000ff
property objecthighlight5 #ffc800
property objecthighlight7 #00ffff
property objecthighlight8 #ff00ff
property objecthighlight9 #ccccff
property objecthighlight10 #0ead00
property objecthighlight11 #cefc00
property objecthighlight12 #9e2dbe
property objecthighlight13 #ba6a29
property objecthighlight14 #fc0188
property objecthighlight15 #02f990
property objecthighlight16 #f1b0fb
property objecthighlight17 #fec004
property objecthighlight18 #149bff
property objecthighlight19 #eb591b
property overlapcolor #19b400
property pbuscolor #000000
property pbusnamecolor #000000
property pinattrmax 20
property pinorder 2
property pinpermute 0
property portcolor #000000
property portnamecolor #000000
property ripindexfontsize 8
property rippercolor #000000
property rubberbandcolor #000000
property rubberbandfontsize 15
property selectattr 0
property selectionappearance 2
property selectioncolor #0000ff
property sheetheight 44
property sheetwidth 68
property showmarks 1
property shownetname 0
property showpagenumbers 1
property showripindex 4
property timelimit 1
#
module new circuit1 work:circuit1:NOFILE -nosplit
load symbol ADD work:ADD:NOFILE HIERBOX pinBus CO input.left [0:0] pinBus DI output.right [3:0] pinBus O output.right [3:0] pinBus S output.right [3:0] pinBus a[6] output.right [3:0] pinBus a_IBUF input.left [7:0] pinBus b_IBUF input.left [7:0] pinBus z[3] input.left [3:0] pinBus z[7] input.left [3:0] pinBus z_OBUF output.right [7:0] boxcolor 1 fillcolor 2 minwidth 13%
load symbol ADD_0 work:ADD_0:NOFILE HIERBOX pinBus a[3] output.right [3:0] pinBus a[6] output.right [3:0] pinBus a_IBUF input.left [7:0] pinBus c_IBUF input.left [7:0] boxcolor 1 fillcolor 2 minwidth 13%
load symbol COMP work:COMP:NOFILE HIERBOX pinBus CO output.right [0:0] pinBus DI input.left [3:0] pinBus S input.left [3:0] boxcolor 1 fillcolor 2 minwidth 13%
load symbol BUFG hdi_primitives BUF pin O output pin I input fillcolor 1
load symbol IBUF hdi_primitives BUF pin O output pin I input fillcolor 1
load symbol MUL work:MUL:NOFILE HIERBOX pinBus O input.left [3:0] pinBus S output.right [3:0] pinBus a_IBUF input.left [7:0] pinBus c_IBUF input.left [7:0] pinBus prod0__60_carry__1_0 output.right [3:0] pinBus prod0__60_carry__1_i_8_0 output.right [14:0] pinBus q_reg[7] input.left [3:0] pinBus sum0_carry output.right [3:0] pinBus sum0_carry__0 output.right [3:0] boxcolor 1 fillcolor 2 minwidth 13%
load symbol REG work:REG:NOFILE HIERBOX pin Clk_IBUF_BUFG input.left pinBus D input.left [15:0] pinBus Q output.right [15:0] pinBus SR input.left [0:0] boxcolor 1 fillcolor 2 minwidth 13%
load symbol SUB work:SUB:NOFILE HIERBOX pinBus D output.right [15:0] pinBus S input.left [3:0] pinBus q_reg[11] input.left [3:0] pinBus q_reg[15] input.left [14:0] pinBus q_reg[3] input.left [3:0] pinBus q_reg[7] input.left [3:0] boxcolor 1 fillcolor 2 minwidth 13%
load symbol OBUF hdi_primitives BUF pin O output pin I input fillcolor 1
load port Clk input -pg 1 -lvl 0 -x 0 -y 670
load port Rst input -pg 1 -lvl 0 -x 0 -y 820
load portBus a input [7:0] -attr @name a[7:0] -pg 1 -lvl 0 -x 0 -y 850
load portBus b input [7:0] -attr @name b[7:0] -pg 1 -lvl 0 -x 0 -y 280
load portBus c input [7:0] -attr @name c[7:0] -pg 1 -lvl 0 -x 0 -y 1280
load portBus x output [15:0] -attr @name x[15:0] -pg 1 -lvl 8 -x 1990 -y 40
load portBus z output [7:0] -attr @name z[7:0] -pg 1 -lvl 8 -x 1990 -y 1160
load inst ADD1 ADD work:ADD:NOFILE -autohide -attr @cell(#000000) ADD -pinBusAttr CO @name CO -pinBusAttr DI @name DI[3:0] -pinBusAttr O @name O[3:0] -pinBusAttr S @name S[3:0] -pinBusAttr a[6] @name a[6][3:0] -pinBusAttr a_IBUF @name a_IBUF[7:0] -pinBusAttr b_IBUF @name b_IBUF[7:0] -pinBusAttr z[3] @name z[3][3:0] -pinBusAttr z[7] @name z[7][3:0] -pinBusAttr z_OBUF @name z_OBUF[7:0] -pg 1 -lvl 3 -x 610 -y 1010
load inst ADD2 ADD_0 work:ADD_0:NOFILE -autohide -attr @cell(#000000) ADD_0 -pinBusAttr a[3] @name a[3][3:0] -pinBusAttr a[6] @name a[6][3:0] -pinBusAttr a_IBUF @name a_IBUF[7:0] -pinBusAttr c_IBUF @name c_IBUF[7:0] -pg 1 -lvl 2 -x 330 -y 1070
load inst COMP1 COMP work:COMP:NOFILE -autohide -attr @cell(#000000) COMP -pinBusAttr CO @name CO -pinBusAttr DI @name DI[3:0] -pinBusAttr S @name S[3:0] -pg 1 -lvl 2 -x 330 -y 870
load inst Clk_IBUF_BUFG_inst BUFG hdi_primitives -attr @cell(#000000) BUFG -pg 1 -lvl 5 -x 1370 -y 670
load inst Clk_IBUF_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 4 -x 930 -y 670
load inst MUL1 MUL work:MUL:NOFILE -autohide -attr @cell(#000000) MUL -pinBusAttr O @name O[3:0] -pinBusAttr S @name S[3:0] -pinBusAttr a_IBUF @name a_IBUF[7:0] -pinBusAttr c_IBUF @name c_IBUF[7:0] -pinBusAttr prod0__60_carry__1_0 @name prod0__60_carry__1_0[3:0] -pinBusAttr prod0__60_carry__1_i_8_0 @name prod0__60_carry__1_i_8_0[14:0] -pinBusAttr q_reg[7] @name q_reg[7][3:0] -pinBusAttr sum0_carry @name sum0_carry[3:0] -pinBusAttr sum0_carry__0 @name sum0_carry__0[3:0] -pg 1 -lvl 4 -x 930 -y 1030
load inst REG1 REG work:REG:NOFILE -autohide -attr @cell(#000000) REG -pinBusAttr D @name D[15:0] -pinBusAttr Q @name Q[15:0] -pinBusAttr SR @name SR -pg 1 -lvl 6 -x 1650 -y 770
load inst Rst_IBUF_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 5 -x 1370 -y 820
load inst SUB1 SUB work:SUB:NOFILE -autohide -attr @cell(#000000) SUB -pinBusAttr D @name D[15:0] -pinBusAttr S @name S[3:0] -pinBusAttr q_reg[11] @name q_reg[11][3:0] -pinBusAttr q_reg[15] @name q_reg[15][14:0] -pinBusAttr q_reg[3] @name q_reg[3][3:0] -pinBusAttr q_reg[7] @name q_reg[7][3:0] -pg 1 -lvl 5 -x 1370 -y 1030
load inst a_IBUF[0]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 710
load inst a_IBUF[1]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 780
load inst a_IBUF[2]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 860
load inst a_IBUF[3]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 930
load inst a_IBUF[4]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1000
load inst a_IBUF[5]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1070
load inst a_IBUF[6]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1140
load inst a_IBUF[7]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1210
load inst b_IBUF[0]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 2 -x 330 -y 280
load inst b_IBUF[1]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 2 -x 330 -y 350
load inst b_IBUF[2]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 2 -x 330 -y 420
load inst b_IBUF[3]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 2 -x 330 -y 490
load inst b_IBUF[4]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 2 -x 330 -y 560
load inst b_IBUF[5]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 2 -x 330 -y 630
load inst b_IBUF[6]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 2 -x 330 -y 710
load inst b_IBUF[7]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 2 -x 330 -y 780
load inst c_IBUF[0]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1280
load inst c_IBUF[1]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1350
load inst c_IBUF[2]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1420
load inst c_IBUF[3]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1490
load inst c_IBUF[4]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1560
load inst c_IBUF[5]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1630
load inst c_IBUF[6]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1700
load inst c_IBUF[7]_inst IBUF hdi_primitives -attr @cell(#000000) IBUF -pg 1 -lvl 1 -x 60 -y 1770
load inst x_OBUF[0]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 40
load inst x_OBUF[10]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 740
load inst x_OBUF[11]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 810
load inst x_OBUF[12]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 880
load inst x_OBUF[13]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 950
load inst x_OBUF[14]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 1020
load inst x_OBUF[15]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 1090
load inst x_OBUF[1]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 110
load inst x_OBUF[2]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 180
load inst x_OBUF[3]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 250
load inst x_OBUF[4]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 320
load inst x_OBUF[5]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 390
load inst x_OBUF[6]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 460
load inst x_OBUF[7]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 530
load inst x_OBUF[8]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 600
load inst x_OBUF[9]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 670
load inst z_OBUF[0]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 1160
load inst z_OBUF[1]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 1230
load inst z_OBUF[2]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 1300
load inst z_OBUF[3]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 1370
load inst z_OBUF[4]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 1440
load inst z_OBUF[5]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 1510
load inst z_OBUF[6]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 1580
load inst z_OBUF[7]_inst OBUF hdi_primitives -attr @cell(#000000) OBUF -pg 1 -lvl 7 -x 1830 -y 1650
load net ADD1_n_0 -attr @rip(#000000) O[3] -pin ADD1 O[3] -pin MUL1 O[3]
load net ADD1_n_1 -attr @rip(#000000) O[2] -pin ADD1 O[2] -pin MUL1 O[2]
load net ADD1_n_10 -attr @rip(#000000) S[1] -pin ADD1 S[1] -pin COMP1 S[1]
load net ADD1_n_11 -attr @rip(#000000) S[0] -pin ADD1 S[0] -pin COMP1 S[0]
load net ADD1_n_12 -attr @rip(#000000) DI[3] -pin ADD1 DI[3] -pin COMP1 DI[3]
load net ADD1_n_13 -attr @rip(#000000) DI[2] -pin ADD1 DI[2] -pin COMP1 DI[2]
load net ADD1_n_14 -attr @rip(#000000) DI[1] -pin ADD1 DI[1] -pin COMP1 DI[1]
load net ADD1_n_15 -attr @rip(#000000) DI[0] -pin ADD1 DI[0] -pin COMP1 DI[0]
load net ADD1_n_2 -attr @rip(#000000) O[1] -pin ADD1 O[1] -pin MUL1 O[1]
load net ADD1_n_3 -attr @rip(#000000) O[0] -pin ADD1 O[0] -pin MUL1 O[0]
load net ADD1_n_4 -attr @rip(#000000) a[6][3] -pin ADD1 a[6][3] -pin MUL1 q_reg[7][3]
load net ADD1_n_5 -attr @rip(#000000) a[6][2] -pin ADD1 a[6][2] -pin MUL1 q_reg[7][2]
load net ADD1_n_6 -attr @rip(#000000) a[6][1] -pin ADD1 a[6][1] -pin MUL1 q_reg[7][1]
load net ADD1_n_7 -attr @rip(#000000) a[6][0] -pin ADD1 a[6][0] -pin MUL1 q_reg[7][0]
load net ADD1_n_8 -attr @rip(#000000) S[3] -pin ADD1 S[3] -pin COMP1 S[3]
load net ADD1_n_9 -attr @rip(#000000) S[2] -pin ADD1 S[2] -pin COMP1 S[2]
load net ADD2_n_0 -attr @rip(#000000) a[3][3] -pin ADD1 z[3][3] -pin ADD2 a[3][3]
load net ADD2_n_1 -attr @rip(#000000) a[3][2] -pin ADD1 z[3][2] -pin ADD2 a[3][2]
load net ADD2_n_2 -attr @rip(#000000) a[3][1] -pin ADD1 z[3][1] -pin ADD2 a[3][1]
load net ADD2_n_3 -attr @rip(#000000) a[3][0] -pin ADD1 z[3][0] -pin ADD2 a[3][0]
load net ADD2_n_4 -attr @rip(#000000) a[6][3] -pin ADD1 z[7][3] -pin ADD2 a[6][3]
load net ADD2_n_5 -attr @rip(#000000) a[6][2] -pin ADD1 z[7][2] -pin ADD2 a[6][2]
load net ADD2_n_6 -attr @rip(#000000) a[6][1] -pin ADD1 z[7][1] -pin ADD2 a[6][1]
load net ADD2_n_7 -attr @rip(#000000) a[6][0] -pin ADD1 z[7][0] -pin ADD2 a[6][0]
load net Clk -port Clk -pin Clk_IBUF_inst I
netloc Clk 1 0 4 NJ 670 NJ 670 NJ 670 NJ
load net Clk_IBUF -pin Clk_IBUF_BUFG_inst I -pin Clk_IBUF_inst O
netloc Clk_IBUF 1 4 1 NJ 670
load net Clk_IBUF_BUFG -pin Clk_IBUF_BUFG_inst O -pin REG1 Clk_IBUF_BUFG
netloc Clk_IBUF_BUFG 1 5 1 1530J 670n
load net MUL1_n_15 -attr @rip(#000000) S[3] -pin MUL1 S[3] -pin SUB1 S[3]
load net MUL1_n_16 -attr @rip(#000000) S[2] -pin MUL1 S[2] -pin SUB1 S[2]
load net MUL1_n_17 -attr @rip(#000000) S[1] -pin MUL1 S[1] -pin SUB1 S[1]
load net MUL1_n_18 -attr @rip(#000000) S[0] -pin MUL1 S[0] -pin SUB1 S[0]
load net MUL1_n_19 -attr @rip(#000000) prod0__60_carry__1_0[3] -pin MUL1 prod0__60_carry__1_0[3] -pin SUB1 q_reg[11][3]
load net MUL1_n_20 -attr @rip(#000000) prod0__60_carry__1_0[2] -pin MUL1 prod0__60_carry__1_0[2] -pin SUB1 q_reg[11][2]
load net MUL1_n_21 -attr @rip(#000000) prod0__60_carry__1_0[1] -pin MUL1 prod0__60_carry__1_0[1] -pin SUB1 q_reg[11][1]
load net MUL1_n_22 -attr @rip(#000000) prod0__60_carry__1_0[0] -pin MUL1 prod0__60_carry__1_0[0] -pin SUB1 q_reg[11][0]
load net MUL1_n_23 -attr @rip(#000000) sum0_carry[3] -pin MUL1 sum0_carry[3] -pin SUB1 q_reg[3][3]
load net MUL1_n_24 -attr @rip(#000000) sum0_carry[2] -pin MUL1 sum0_carry[2] -pin SUB1 q_reg[3][2]
load net MUL1_n_25 -attr @rip(#000000) sum0_carry[1] -pin MUL1 sum0_carry[1] -pin SUB1 q_reg[3][1]
load net MUL1_n_26 -attr @rip(#000000) sum0_carry[0] -pin MUL1 sum0_carry[0] -pin SUB1 q_reg[3][0]
load net MUL1_n_27 -attr @rip(#000000) sum0_carry__0[3] -pin MUL1 sum0_carry__0[3] -pin SUB1 q_reg[7][3]
load net MUL1_n_28 -attr @rip(#000000) sum0_carry__0[2] -pin MUL1 sum0_carry__0[2] -pin SUB1 q_reg[7][2]
load net MUL1_n_29 -attr @rip(#000000) sum0_carry__0[1] -pin MUL1 sum0_carry__0[1] -pin SUB1 q_reg[7][1]
load net MUL1_n_30 -attr @rip(#000000) sum0_carry__0[0] -pin MUL1 sum0_carry__0[0] -pin SUB1 q_reg[7][0]
load net Rst -port Rst -pin Rst_IBUF_inst I
netloc Rst 1 0 5 NJ 820 NJ 820 NJ 820 NJ 820 NJ
load net Rst_IBUF -attr @rip(#000000) 0 -pin REG1 SR[0] -pin Rst_IBUF_inst O
netloc Rst_IBUF 1 5 1 NJ 820
load net a[0] -attr @rip(#000000) a[0] -port a[0] -pin a_IBUF[0]_inst I
load net a[1] -attr @rip(#000000) a[1] -port a[1] -pin a_IBUF[1]_inst I
load net a[2] -attr @rip(#000000) a[2] -port a[2] -pin a_IBUF[2]_inst I
load net a[3] -attr @rip(#000000) a[3] -port a[3] -pin a_IBUF[3]_inst I
load net a[4] -attr @rip(#000000) a[4] -port a[4] -pin a_IBUF[4]_inst I
load net a[5] -attr @rip(#000000) a[5] -port a[5] -pin a_IBUF[5]_inst I
load net a[6] -attr @rip(#000000) a[6] -port a[6] -pin a_IBUF[6]_inst I
load net a[7] -attr @rip(#000000) a[7] -port a[7] -pin a_IBUF[7]_inst I
load net a_IBUF[0] -attr @rip(#000000) 0 -pin ADD1 a_IBUF[0] -pin ADD2 a_IBUF[0] -pin MUL1 a_IBUF[0] -pin a_IBUF[0]_inst O
load net a_IBUF[1] -attr @rip(#000000) 1 -pin ADD1 a_IBUF[1] -pin ADD2 a_IBUF[1] -pin MUL1 a_IBUF[1] -pin a_IBUF[1]_inst O
load net a_IBUF[2] -attr @rip(#000000) 2 -pin ADD1 a_IBUF[2] -pin ADD2 a_IBUF[2] -pin MUL1 a_IBUF[2] -pin a_IBUF[2]_inst O
load net a_IBUF[3] -attr @rip(#000000) 3 -pin ADD1 a_IBUF[3] -pin ADD2 a_IBUF[3] -pin MUL1 a_IBUF[3] -pin a_IBUF[3]_inst O
load net a_IBUF[4] -attr @rip(#000000) 4 -pin ADD1 a_IBUF[4] -pin ADD2 a_IBUF[4] -pin MUL1 a_IBUF[4] -pin a_IBUF[4]_inst O
load net a_IBUF[5] -attr @rip(#000000) 5 -pin ADD1 a_IBUF[5] -pin ADD2 a_IBUF[5] -pin MUL1 a_IBUF[5] -pin a_IBUF[5]_inst O
load net a_IBUF[6] -attr @rip(#000000) 6 -pin ADD1 a_IBUF[6] -pin ADD2 a_IBUF[6] -pin MUL1 a_IBUF[6] -pin a_IBUF[6]_inst O
load net a_IBUF[7] -attr @rip(#000000) 7 -pin ADD1 a_IBUF[7] -pin ADD2 a_IBUF[7] -pin MUL1 a_IBUF[7] -pin a_IBUF[7]_inst O
load net b[0] -attr @rip(#000000) b[0] -port b[0] -pin b_IBUF[0]_inst I
load net b[1] -attr @rip(#000000) b[1] -port b[1] -pin b_IBUF[1]_inst I
load net b[2] -attr @rip(#000000) b[2] -port b[2] -pin b_IBUF[2]_inst I
load net b[3] -attr @rip(#000000) b[3] -port b[3] -pin b_IBUF[3]_inst I
load net b[4] -attr @rip(#000000) b[4] -port b[4] -pin b_IBUF[4]_inst I
load net b[5] -attr @rip(#000000) b[5] -port b[5] -pin b_IBUF[5]_inst I
load net b[6] -attr @rip(#000000) b[6] -port b[6] -pin b_IBUF[6]_inst I
load net b[7] -attr @rip(#000000) b[7] -port b[7] -pin b_IBUF[7]_inst I
load net b_IBUF[0] -attr @rip(#000000) 0 -pin ADD1 b_IBUF[0] -pin b_IBUF[0]_inst O
load net b_IBUF[1] -attr @rip(#000000) 1 -pin ADD1 b_IBUF[1] -pin b_IBUF[1]_inst O
load net b_IBUF[2] -attr @rip(#000000) 2 -pin ADD1 b_IBUF[2] -pin b_IBUF[2]_inst O
load net b_IBUF[3] -attr @rip(#000000) 3 -pin ADD1 b_IBUF[3] -pin b_IBUF[3]_inst O
load net b_IBUF[4] -attr @rip(#000000) 4 -pin ADD1 b_IBUF[4] -pin b_IBUF[4]_inst O
load net b_IBUF[5] -attr @rip(#000000) 5 -pin ADD1 b_IBUF[5] -pin b_IBUF[5]_inst O
load net b_IBUF[6] -attr @rip(#000000) 6 -pin ADD1 b_IBUF[6] -pin b_IBUF[6]_inst O
load net b_IBUF[7] -attr @rip(#000000) 7 -pin ADD1 b_IBUF[7] -pin b_IBUF[7]_inst O
load net c[0] -attr @rip(#000000) c[0] -port c[0] -pin c_IBUF[0]_inst I
load net c[1] -attr @rip(#000000) c[1] -port c[1] -pin c_IBUF[1]_inst I
load net c[2] -attr @rip(#000000) c[2] -port c[2] -pin c_IBUF[2]_inst I
load net c[3] -attr @rip(#000000) c[3] -port c[3] -pin c_IBUF[3]_inst I
load net c[4] -attr @rip(#000000) c[4] -port c[4] -pin c_IBUF[4]_inst I
load net c[5] -attr @rip(#000000) c[5] -port c[5] -pin c_IBUF[5]_inst I
load net c[6] -attr @rip(#000000) c[6] -port c[6] -pin c_IBUF[6]_inst I
load net c[7] -attr @rip(#000000) c[7] -port c[7] -pin c_IBUF[7]_inst I
load net c_IBUF[0] -attr @rip(#000000) 0 -pin ADD2 c_IBUF[0] -pin MUL1 c_IBUF[0] -pin c_IBUF[0]_inst O
load net c_IBUF[1] -attr @rip(#000000) 1 -pin ADD2 c_IBUF[1] -pin MUL1 c_IBUF[1] -pin c_IBUF[1]_inst O
load net c_IBUF[2] -attr @rip(#000000) 2 -pin ADD2 c_IBUF[2] -pin MUL1 c_IBUF[2] -pin c_IBUF[2]_inst O
load net c_IBUF[3] -attr @rip(#000000) 3 -pin ADD2 c_IBUF[3] -pin MUL1 c_IBUF[3] -pin c_IBUF[3]_inst O
load net c_IBUF[4] -attr @rip(#000000) 4 -pin ADD2 c_IBUF[4] -pin MUL1 c_IBUF[4] -pin c_IBUF[4]_inst O
load net c_IBUF[5] -attr @rip(#000000) 5 -pin ADD2 c_IBUF[5] -pin MUL1 c_IBUF[5] -pin c_IBUF[5]_inst O
load net c_IBUF[6] -attr @rip(#000000) 6 -pin ADD2 c_IBUF[6] -pin MUL1 c_IBUF[6] -pin c_IBUF[6]_inst O
load net c_IBUF[7] -attr @rip(#000000) 7 -pin ADD2 c_IBUF[7] -pin MUL1 c_IBUF[7] -pin c_IBUF[7]_inst O
load net d[0] -attr @rip(#000000) D[0] -pin REG1 D[0] -pin SUB1 D[0]
load net d[10] -attr @rip(#000000) D[10] -pin REG1 D[10] -pin SUB1 D[10]
load net d[11] -attr @rip(#000000) D[11] -pin REG1 D[11] -pin SUB1 D[11]
load net d[12] -attr @rip(#000000) D[12] -pin REG1 D[12] -pin SUB1 D[12]
load net d[13] -attr @rip(#000000) D[13] -pin REG1 D[13] -pin SUB1 D[13]
load net d[14] -attr @rip(#000000) D[14] -pin REG1 D[14] -pin SUB1 D[14]
load net d[15] -attr @rip(#000000) D[15] -pin REG1 D[15] -pin SUB1 D[15]
load net d[1] -attr @rip(#000000) D[1] -pin REG1 D[1] -pin SUB1 D[1]
load net d[2] -attr @rip(#000000) D[2] -pin REG1 D[2] -pin SUB1 D[2]
load net d[3] -attr @rip(#000000) D[3] -pin REG1 D[3] -pin SUB1 D[3]
load net d[4] -attr @rip(#000000) D[4] -pin REG1 D[4] -pin SUB1 D[4]
load net d[5] -attr @rip(#000000) D[5] -pin REG1 D[5] -pin SUB1 D[5]
load net d[6] -attr @rip(#000000) D[6] -pin REG1 D[6] -pin SUB1 D[6]
load net d[7] -attr @rip(#000000) D[7] -pin REG1 D[7] -pin SUB1 D[7]
load net d[8] -attr @rip(#000000) D[8] -pin REG1 D[8] -pin SUB1 D[8]
load net d[9] -attr @rip(#000000) D[9] -pin REG1 D[9] -pin SUB1 D[9]
load net prod[0] -attr @rip(#000000) prod0__60_carry__1_i_8_0[0] -pin MUL1 prod0__60_carry__1_i_8_0[0] -pin SUB1 q_reg[15][0]
load net prod[10] -attr @rip(#000000) prod0__60_carry__1_i_8_0[10] -pin MUL1 prod0__60_carry__1_i_8_0[10] -pin SUB1 q_reg[15][10]
load net prod[11] -attr @rip(#000000) prod0__60_carry__1_i_8_0[11] -pin MUL1 prod0__60_carry__1_i_8_0[11] -pin SUB1 q_reg[15][11]
load net prod[12] -attr @rip(#000000) prod0__60_carry__1_i_8_0[12] -pin MUL1 prod0__60_carry__1_i_8_0[12] -pin SUB1 q_reg[15][12]
load net prod[13] -attr @rip(#000000) prod0__60_carry__1_i_8_0[13] -pin MUL1 prod0__60_carry__1_i_8_0[13] -pin SUB1 q_reg[15][13]
load net prod[14] -attr @rip(#000000) prod0__60_carry__1_i_8_0[14] -pin MUL1 prod0__60_carry__1_i_8_0[14] -pin SUB1 q_reg[15][14]
load net prod[1] -attr @rip(#000000) prod0__60_carry__1_i_8_0[1] -pin MUL1 prod0__60_carry__1_i_8_0[1] -pin SUB1 q_reg[15][1]
load net prod[2] -attr @rip(#000000) prod0__60_carry__1_i_8_0[2] -pin MUL1 prod0__60_carry__1_i_8_0[2] -pin SUB1 q_reg[15][2]
load net prod[3] -attr @rip(#000000) prod0__60_carry__1_i_8_0[3] -pin MUL1 prod0__60_carry__1_i_8_0[3] -pin SUB1 q_reg[15][3]
load net prod[4] -attr @rip(#000000) prod0__60_carry__1_i_8_0[4] -pin MUL1 prod0__60_carry__1_i_8_0[4] -pin SUB1 q_reg[15][4]
load net prod[5] -attr @rip(#000000) prod0__60_carry__1_i_8_0[5] -pin MUL1 prod0__60_carry__1_i_8_0[5] -pin SUB1 q_reg[15][5]
load net prod[6] -attr @rip(#000000) prod0__60_carry__1_i_8_0[6] -pin MUL1 prod0__60_carry__1_i_8_0[6] -pin SUB1 q_reg[15][6]
load net prod[7] -attr @rip(#000000) prod0__60_carry__1_i_8_0[7] -pin MUL1 prod0__60_carry__1_i_8_0[7] -pin SUB1 q_reg[15][7]
load net prod[8] -attr @rip(#000000) prod0__60_carry__1_i_8_0[8] -pin MUL1 prod0__60_carry__1_i_8_0[8] -pin SUB1 q_reg[15][8]
load net prod[9] -attr @rip(#000000) prod0__60_carry__1_i_8_0[9] -pin MUL1 prod0__60_carry__1_i_8_0[9] -pin SUB1 q_reg[15][9]
load net sel -attr @rip(#000000) CO[0] -pin ADD1 CO[0] -pin COMP1 CO[0]
netloc sel 1 2 1 490 880n
load net x[0] -attr @rip(#000000) 0 -port x[0] -pin x_OBUF[0]_inst O
load net x[10] -attr @rip(#000000) 10 -port x[10] -pin x_OBUF[10]_inst O
load net x[11] -attr @rip(#000000) 11 -port x[11] -pin x_OBUF[11]_inst O
load net x[12] -attr @rip(#000000) 12 -port x[12] -pin x_OBUF[12]_inst O
load net x[13] -attr @rip(#000000) 13 -port x[13] -pin x_OBUF[13]_inst O
load net x[14] -attr @rip(#000000) 14 -port x[14] -pin x_OBUF[14]_inst O
load net x[15] -attr @rip(#000000) 15 -port x[15] -pin x_OBUF[15]_inst O
load net x[1] -attr @rip(#000000) 1 -port x[1] -pin x_OBUF[1]_inst O
load net x[2] -attr @rip(#000000) 2 -port x[2] -pin x_OBUF[2]_inst O
load net x[3] -attr @rip(#000000) 3 -port x[3] -pin x_OBUF[3]_inst O
load net x[4] -attr @rip(#000000) 4 -port x[4] -pin x_OBUF[4]_inst O
load net x[5] -attr @rip(#000000) 5 -port x[5] -pin x_OBUF[5]_inst O
load net x[6] -attr @rip(#000000) 6 -port x[6] -pin x_OBUF[6]_inst O
load net x[7] -attr @rip(#000000) 7 -port x[7] -pin x_OBUF[7]_inst O
load net x[8] -attr @rip(#000000) 8 -port x[8] -pin x_OBUF[8]_inst O
load net x[9] -attr @rip(#000000) 9 -port x[9] -pin x_OBUF[9]_inst O
load net x_OBUF[0] -attr @rip(#000000) Q[0] -pin REG1 Q[0] -pin x_OBUF[0]_inst I
load net x_OBUF[10] -attr @rip(#000000) Q[10] -pin REG1 Q[10] -pin x_OBUF[10]_inst I
load net x_OBUF[11] -attr @rip(#000000) Q[11] -pin REG1 Q[11] -pin x_OBUF[11]_inst I
load net x_OBUF[12] -attr @rip(#000000) Q[12] -pin REG1 Q[12] -pin x_OBUF[12]_inst I
load net x_OBUF[13] -attr @rip(#000000) Q[13] -pin REG1 Q[13] -pin x_OBUF[13]_inst I
load net x_OBUF[14] -attr @rip(#000000) Q[14] -pin REG1 Q[14] -pin x_OBUF[14]_inst I
load net x_OBUF[15] -attr @rip(#000000) Q[15] -pin REG1 Q[15] -pin x_OBUF[15]_inst I
load net x_OBUF[1] -attr @rip(#000000) Q[1] -pin REG1 Q[1] -pin x_OBUF[1]_inst I
load net x_OBUF[2] -attr @rip(#000000) Q[2] -pin REG1 Q[2] -pin x_OBUF[2]_inst I
load net x_OBUF[3] -attr @rip(#000000) Q[3] -pin REG1 Q[3] -pin x_OBUF[3]_inst I
load net x_OBUF[4] -attr @rip(#000000) Q[4] -pin REG1 Q[4] -pin x_OBUF[4]_inst I
load net x_OBUF[5] -attr @rip(#000000) Q[5] -pin REG1 Q[5] -pin x_OBUF[5]_inst I
load net x_OBUF[6] -attr @rip(#000000) Q[6] -pin REG1 Q[6] -pin x_OBUF[6]_inst I
load net x_OBUF[7] -attr @rip(#000000) Q[7] -pin REG1 Q[7] -pin x_OBUF[7]_inst I
load net x_OBUF[8] -attr @rip(#000000) Q[8] -pin REG1 Q[8] -pin x_OBUF[8]_inst I
load net x_OBUF[9] -attr @rip(#000000) Q[9] -pin REG1 Q[9] -pin x_OBUF[9]_inst I
load net z[0] -attr @rip(#000000) 0 -port z[0] -pin z_OBUF[0]_inst O
load net z[1] -attr @rip(#000000) 1 -port z[1] -pin z_OBUF[1]_inst O
load net z[2] -attr @rip(#000000) 2 -port z[2] -pin z_OBUF[2]_inst O
load net z[3] -attr @rip(#000000) 3 -port z[3] -pin z_OBUF[3]_inst O
load net z[4] -attr @rip(#000000) 4 -port z[4] -pin z_OBUF[4]_inst O
load net z[5] -attr @rip(#000000) 5 -port z[5] -pin z_OBUF[5]_inst O
load net z[6] -attr @rip(#000000) 6 -port z[6] -pin z_OBUF[6]_inst O
load net z[7] -attr @rip(#000000) 7 -port z[7] -pin z_OBUF[7]_inst O
load net z_OBUF[0] -attr @rip(#000000) z_OBUF[0] -pin ADD1 z_OBUF[0] -pin z_OBUF[0]_inst I
load net z_OBUF[1] -attr @rip(#000000) z_OBUF[1] -pin ADD1 z_OBUF[1] -pin z_OBUF[1]_inst I
load net z_OBUF[2] -attr @rip(#000000) z_OBUF[2] -pin ADD1 z_OBUF[2] -pin z_OBUF[2]_inst I
load net z_OBUF[3] -attr @rip(#000000) z_OBUF[3] -pin ADD1 z_OBUF[3] -pin z_OBUF[3]_inst I
load net z_OBUF[4] -attr @rip(#000000) z_OBUF[4] -pin ADD1 z_OBUF[4] -pin z_OBUF[4]_inst I
load net z_OBUF[5] -attr @rip(#000000) z_OBUF[5] -pin ADD1 z_OBUF[5] -pin z_OBUF[5]_inst I
load net z_OBUF[6] -attr @rip(#000000) z_OBUF[6] -pin ADD1 z_OBUF[6] -pin z_OBUF[6]_inst I
load net z_OBUF[7] -attr @rip(#000000) z_OBUF[7] -pin ADD1 z_OBUF[7] -pin z_OBUF[7]_inst I
load netBundle @a 8 a[7] a[6] a[5] a[4] a[3] a[2] a[1] a[0] -autobundled
netbloc @a 1 0 1 20 710n
load netBundle @b 8 b[7] b[6] b[5] b[4] b[3] b[2] b[1] b[0] -autobundled
netbloc @b 1 0 2 NJ 280 230
load netBundle @c 8 c[7] c[6] c[5] c[4] c[3] c[2] c[1] c[0] -autobundled
netbloc @c 1 0 1 20 1280n
load netBundle @x 16 x[15] x[14] x[13] x[12] x[11] x[10] x[9] x[8] x[7] x[6] x[5] x[4] x[3] x[2] x[1] x[0] -autobundled
netbloc @x 1 7 1 1970 40n
load netBundle @z 8 z[7] z[6] z[5] z[4] z[3] z[2] z[1] z[0] -autobundled
netbloc @z 1 7 1 1970 1160n
load netBundle @ADD1_n_ 4 ADD1_n_12 ADD1_n_13 ADD1_n_14 ADD1_n_15 -autobundled
netbloc @ADD1_n_ 1 1 3 210 940 NJ 940 790
load netBundle @ADD1_n__1 4 ADD1_n_0 ADD1_n_1 ADD1_n_2 ADD1_n_3 -autobundled
netbloc @ADD1_n__1 1 3 1 N 1040
load netBundle @ADD1_n__2 4 ADD1_n_8 ADD1_n_9 ADD1_n_10 ADD1_n_11 -autobundled
netbloc @ADD1_n__2 1 1 3 230 960 NJ 960 770
load netBundle @ADD1_n__3 4 ADD1_n_4 ADD1_n_5 ADD1_n_6 ADD1_n_7 -autobundled
netbloc @ADD1_n__3 1 3 1 810 1080n
load netBundle @z_OBUF 8 z_OBUF[7] z_OBUF[6] z_OBUF[5] z_OBUF[4] z_OBUF[3] z_OBUF[2] z_OBUF[1] z_OBUF[0] -autobundled
netbloc @z_OBUF 1 3 4 770 1160 NJ 1160 NJ 1160 1790
load netBundle @ADD2_n_ 4 ADD2_n_0 ADD2_n_1 ADD2_n_2 ADD2_n_3 -autobundled
netbloc @ADD2_n_ 1 2 1 N 1080
load netBundle @ADD2_n__1 4 ADD2_n_4 ADD2_n_5 ADD2_n_6 ADD2_n_7 -autobundled
netbloc @ADD2_n__1 1 2 1 N 1100
load netBundle @MUL1_n_ 4 MUL1_n_15 MUL1_n_16 MUL1_n_17 MUL1_n_18 -autobundled
netbloc @MUL1_n_ 1 4 1 N 1040
load netBundle @MUL1_n__1 4 MUL1_n_19 MUL1_n_20 MUL1_n_21 MUL1_n_22 -autobundled
netbloc @MUL1_n__1 1 4 1 1230 1080n
load netBundle @prod 15 prod[14] prod[13] prod[12] prod[11] prod[10] prod[9] prod[8] prod[7] prod[6] prod[5] prod[4] prod[3] prod[2] prod[1] prod[0] -autobundled
netbloc @prod 1 4 1 1190 1060n
load netBundle @MUL1_n__2 4 MUL1_n_23 MUL1_n_24 MUL1_n_25 MUL1_n_26 -autobundled
netbloc @MUL1_n__2 1 4 1 1210 1060n
load netBundle @MUL1_n__3 4 MUL1_n_27 MUL1_n_28 MUL1_n_29 MUL1_n_30 -autobundled
netbloc @MUL1_n__3 1 4 1 1250 1080n
load netBundle @x_OBUF 16 x_OBUF[15] x_OBUF[14] x_OBUF[13] x_OBUF[12] x_OBUF[11] x_OBUF[10] x_OBUF[9] x_OBUF[8] x_OBUF[7] x_OBUF[6] x_OBUF[5] x_OBUF[4] x_OBUF[3] x_OBUF[2] x_OBUF[1] x_OBUF[0] -autobundled
netbloc @x_OBUF 1 6 1 1790 40n
load netBundle @d 16 d[15] d[14] d[13] d[12] d[11] d[10] d[9] d[8] d[7] d[6] d[5] d[4] d[3] d[2] d[1] d[0] -autobundled
netbloc @d 1 5 1 1530 800n
load netBundle @a_IBUF 8 a_IBUF[7] a_IBUF[6] a_IBUF[5] a_IBUF[4] a_IBUF[3] a_IBUF[2] a_IBUF[1] a_IBUF[0] -autobundled
netbloc @a_IBUF 1 1 3 190 1020 470 1140 790J
load netBundle @b_IBUF 8 b_IBUF[7] b_IBUF[6] b_IBUF[5] b_IBUF[4] b_IBUF[3] b_IBUF[2] b_IBUF[1] b_IBUF[0] -autobundled
netbloc @b_IBUF 1 2 1 510 280n
load netBundle @c_IBUF 8 c_IBUF[7] c_IBUF[6] c_IBUF[5] c_IBUF[4] c_IBUF[3] c_IBUF[2] c_IBUF[1] c_IBUF[0] -autobundled
netbloc @c_IBUF 1 1 3 230 1160 NJ 1160 830
levelinfo -pg 1 0 60 330 610 930 1370 1650 1830 1990
pagesize -pg 1 -db -bbox -sgen -90 0 2080 1810
show
fullfit
#
# initialize ictrl to current module circuit1 work:circuit1:NOFILE
ictrl init topinfo |
